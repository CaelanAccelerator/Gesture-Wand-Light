# Gesture Wand Light — Project README

An STM32-based gesture-controlled light. Wave the wand, the light reacts (color /
brightness / effects). Built as a learning project that also maps onto embedded
firmware co-op job requirements.

---

## 1. Project Vision

- **Core idea:** an IMU inside a wand detects motion → firmware recognizes a
  gesture → a light responds (color, brightness, animation).
- **End goal (stretch):** a *remote* version where the wand and the light are
  separate nodes, connected over a wireless/wired link.
- **Current stage:** building a **bare-metal mock framework** on the dev board,
  using on-board button/LED as stand-ins for the real IMU/light.

### Hardware
- **MCU board:** STM32 Nucleo-F446RE (ARM Cortex-M4 @ 180 MHz)
- **On hand:** W5500 Ethernet controller (for the future remote version)
- **To buy:** MPU6050 IMU (6-axis), WS2812B LEDs (ring + strip), breadboard,
  jumper wires, data-capable Micro-USB cable

---

## 2. Architecture (the design we settled on)

A decoupled **pipeline** so that swapping mock parts for real hardware requires
minimal code changes.

```
[Input Source] -> [Gesture Detector] -> (transport seam) -> [Light Controller] -> [Light Output]
```

| Layer | Responsibility | Mock version (now) | Real version (later) |
|---|---|---|---|
| Input Source | Produce motion data | Button generates a preset `MotionData` array | MPU6050 over I2C |
| Gesture Detector | Turn motion data into a gesture | Dumb threshold check | Threshold → DTW / lightweight ML |
| Transport seam | Hand the gesture to the controller | Local function call / queue | Network packet (W5500 or BLE) |
| Light Controller | Map gesture → light effect, drive state machine | Maps to LED blink pattern | Maps to WS2812 effects |
| Light Output | Physically render | On-board LED (LD2) faking colors via blink | WS2812B via DMA |

### Key design decisions
- **Data contract = `MotionData`** (6 values: `ax, ay, az, gx, gy, gz`). Defined
  to match the *richest* source (the IMU), so the button just fakes this format.
  Switching to a real IMU should not change the detector's interface.
- **Output contract = `ILight` interface** (`setColor`, `setBrightness`,
  `update`). Controller talks only to this interface, so swapping on-board LED
  for WS2812B leaves upper logic untouched.
- **Mock the INPUT, not the OUTPUT** of the detector. The button fabricates fake
  motion data fed into the detector; the detector's input interface gets
  exercised now so it is proven before the IMU arrives.
- **Animations must be non-blocking.** No `HAL_Delay` inside effects. Use an
  `update()` method that advances one frame per call.
- **State machine for the light** (State Pattern). Keep *mechanism* (how states
  transition) separate from *policy* (which gesture maps to which effect — a
  lookup table, not hard-coded).
- **RTOS comes later, not now.** Get the bare-metal pipeline working first, hit
  the pain point of coordinating continuous tasks, *then* migrate to FreeRTOS so
  the "why" is justified.

### Data flow vs. priority (for the future RTOS split)
| Node | Data flow (who feeds whom) | Priority (who is most time-critical) |
|---|---|---|
| Wand end | sample -> detect -> transmit | sample > detect > transmit |
| Light end | receive -> control -> render | render, receive > control |

---

## 2b. Project File Structure

The project separates **CubeMX-generated code** from **my application code**, and
within the app, separates **pure logic** from **hardware drivers**. This is the
file-level expression of the decoupling described above.

```
My_Project_2/
├── Core/                  # CubeMX-generated. Don't hand-edit except USER CODE regions.
│   └── Src/main.cpp       # Only: init peripherals + wire modules together + main loop
├── Drivers/               # CubeMX-generated HAL library. Do not edit.
│
├── App/                   # All my own code (CubeMX never touches this)
│   ├── core/              # Pure logic layer — NO HAL includes, PC-testable
│   │   ├── MotionData.hpp     # Data contract: struct { int16_t ax,ay,az,gx,gy,gz }
│   │   ├── Gesture.hpp        # enum class Gesture { None, Swing, Circle, ... }
│   │   ├── ISensor.hpp        # Abstract input interface (produces MotionData)
│   │   ├── ILight.hpp         # Abstract output interface (setColor/setBrightness/update)
│   │   ├── GestureDetector.hpp/.cpp   # Recognition logic (pure algorithm)
│   │   └── LightController.hpp/.cpp   # State machine + gesture->effect mapping
│   │
│   ├── driver/            # Hardware adapter layer — HAL is included HERE only
│   │   ├── ButtonInput.hpp/.cpp       # Mock input: button -> fabricated MotionData
│   │   ├── BoardLed.hpp/.cpp          # Mock output: on-board LED implements ILight
│   │   ├── Mpu6050Sensor.hpp/.cpp     # (later) real IMU implements ISensor
│   │   └── Ws2812Light.hpp/.cpp       # (later) real strip implements ILight
│   │
│   └── app/
│       └── App.cpp        # Assembles all layers; main() just calls into this
│
├── tools/
│   └── uart_logger.py     # PC-side serial logger (not flashed to the board)
├── docs/design.md
├── README.md
└── DEBUGGING_STORIES.md
```

### Design intent
- **`core/` vs `driver/` is the heart of the structure.** `core/` is pure logic
  and includes no HAL — it talks to hardware only through the `ISensor` /
  `ILight` interfaces. `driver/` is where HAL calls live; each driver implements
  an interface. **Swapping hardware = add a new class in `driver/`; `core/` is
  untouched.** (e.g. on-board LED -> WS2812 = new `Ws2812Light : ILight`.)
- **`main.cpp` stays thin:** CubeMX init, construct + wire the objects (inject a
  `BoardLed` into the `LightController`, etc.), run the loop. No business logic.
- **Header-only files** (`MotionData`, `Gesture`, the interfaces) are pure
  declarations and need no `.cpp`. Files with behavior get a matching `.cpp`.
- **`tools/` is host-side** (Python), kept separate from firmware.

### Build note (CubeIDE)
New folders under `App/` must be added to the compiler's **source locations and
include paths** (Properties -> C/C++ General -> Paths and Symbols), or the IDE
won't compile them and headers won't resolve. Verify with a single `#include`
and a Build before writing a lot of code.

---

## 3. Glossary / Naming Conventions (English terms we use)

| Term | Meaning |
|---|---|
| HAL | Hardware Abstraction Layer — ST's library wrapping register access |
| GPIO | General-Purpose Input/Output pin |
| Pin multiplexing / alternate function | One physical pin can serve multiple roles (GPIO, SPI, UART, PWM...) but only one at a time |
| EXTI / NVIC | External Interrupt / Nested Vectored Interrupt Controller |
| UART / USART | Serial communication peripheral (used here for `printf` debug output) |
| SPI | Serial Peripheral Interface bus (used for W5500, later) |
| I2C | Two-wire bus (used for MPU6050 IMU, later) |
| PWM | Pulse-Width Modulation (used for brightness / WS2812 timing) |
| DMA | Direct Memory Access — moves data without CPU, needed for WS2812 timing |
| ISR | Interrupt Service Routine |
| `MotionData` | Our struct: `int16_t ax, ay, az, gx, gy, gz` |
| `ILight` | Abstract output interface: `setColor / setBrightness / update` |
| LD1 | On-board COM LED (ST-Link comms status) — NOT program-controlled |
| LD2 | On-board user **green** LED on **PA5** — this is the one our code drives |
| LD3 | On-board power LED (red, on whenever powered) |
| B1 / PC13 | On-board blue user push button |
| B2 / NRST | On-board black reset button |

---

## 4. Progress Log

### Day 1 — Environment revival + blink + UART + C++ conversion
- [x] Confirmed toolchain works, project builds, flashes successfully
- [x] Blinked on-board LED (LD2 / PA5) via `HAL_GPIO_TogglePin` + `HAL_Delay`
- [x] Removed/commented out W5500 test code to get back to a clean blink baseline
- [x] Diagnosed + fixed dead-LED bug (PA5 pin multiplexing conflict — Story #1)
- [x] Set up Git repo, `.gitignore` (build output excluded), pushed to GitHub
- [x] UART `printf` debug output working via `_write` redirect (115200 baud)
- [x] Converted project to C++ (`main.cpp`)
- [x] Fixed silent printf failure after C++ conversion (`extern "C"` on `_write` — Story #2)
- [ ] Define framework contracts: `MotionData`, `Gesture`, `ILight` (next)

### Standard flash procedure
1. Edit code (keep custom code inside `/* USER CODE BEGIN/END */` markers)
2. **Build** (hammer icon) — confirm no red errors
3. **Run** (solid green triangle, NOT the Debug bug icon) — this flashes AND
   auto-resets the board
4. Watch LD2. To restart manually: press **B2 (reset)** or re-plug USB.

### Git workflow (daily rhythm)
Repo: https://github.com/CaelanAccelerator/Gesture-Wand-Light

After each meaningful chunk of work:
```
git add .
git commit -m "short present-tense message, e.g. Add UART printf output"
git push
```
- Commit small and often; one logical change per commit.
- Each commit should leave the code in a working state.
- `Debug/` build output is git-ignored on purpose (regenerated every build).
- IDE/CubeMX config (`.ioc`, `.cproject`, etc.) IS tracked — versions hardware
  config history (e.g. pin assignments).

---

## 5. Debugging Log

Full interview-ready stories (STAR format) live in **`DEBUGGING_STORIES.md`**.

Quick index:
- **#1 — Dead on-board LED:** PA5 pin multiplexing conflict (LED pin had been
  reassigned as SPI1_SCK).
- **#2 — printf silently dead after C→C++:** name mangling on `_write`; fixed
  with `extern "C"`. Silent functional failure, no compiler error.

---

## 6. Resume Bullets (fill in as milestones complete)

> Write these only once the work is real and demoable. Verb-first, quantified.

- [ ] Designed a layered, decoupled C++ control framework (input / detection /
      control) on STM32 (ARM Cortex-M4), enabling mock-to-hardware swap without
      changing core logic
- [ ] Implemented a State Pattern light controller with a gesture→effect lookup
      table separating mechanism from policy
- [ ] Defined a unified `MotionData` interface allowing seamless switch from
      button mock to MPU6050 IMU input
- [ ] Bare-metal STM32/HAL: GPIO, EXTI interrupts, UART, PWM, timers
- [ ] I2C driver for MPU6050 6-axis IMU (low-level driver)
- [ ] EMA low-pass filtering of motion data
- [ ] Gesture recognition (threshold → template matching / DTW)
- [ ] Migrated to FreeRTOS multi-tasking (sample / detect / light-control)
- [ ] WS2812B driver via DMA for precise timing
- [ ] Remote wand-to-light control (distributed / IoT) over network link