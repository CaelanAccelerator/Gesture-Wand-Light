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

### Day 1 — Environment revival + blink
- [x] Confirmed toolchain works, project builds, flashes successfully
- [x] Blinked on-board LED (LD2 / PA5) via `HAL_GPIO_TogglePin` + `HAL_Delay`
- [x] Removed/commented out W5500 test code to get back to a clean blink baseline
- [ ] UART `printf` debug output (next)
- [ ] Blink + serial status print combined (output-layer seed)

### Standard flash procedure
1. Edit code (keep custom code inside `/* USER CODE BEGIN/END */` markers)
2. **Build** (hammer icon) — confirm no red errors
3. **Run** (solid green triangle, NOT the Debug bug icon) — this flashes AND
   auto-resets the board
4. Watch LD2. To restart manually: press **B2 (reset)** or re-plug USB.

---

## 5. Debugging Log (interview-ready stories)

### #1 — Dead on-board LED: a pin multiplexing conflict
- **Situation:** Building the gesture-light framework on STM32; on-board LED used
  as a debug indicator. Had previously edited SPI pin config to wire up a W5500
  Ethernet module.
- **Problem:** After flashing, the green LED (LD2) was completely dark, though
  the power and comms LEDs were normal and the program flashed/verified fine.
- **Action:** Ruled out software first — commented out peripheral init, switched
  from Debug to Run mode to rule out a halt at the entry point. Symptom
  persisted. Suspected the earlier W5500 work, opened the CubeMX pin view, and
  found the LED's pin **PA5** had been reassigned as **SPI1_SCK**.
- **Root cause:** **Pin multiplexing conflict** — PA5 can only serve one role at
  a time; assigned to SPI, it no longer responded to GPIO operations.
- **Fix:** Reassigned PA5 back to `GPIO_Output`, disabled the conflicting SPI1
  config; LED recovered.
- **Takeaway / habit formed:** Before changing pin config, check whether the pin
  is already claimed by an on-board peripheral (LED, button). On Nucleo-F446RE,
  LD2 and SPI1_SCK both default to PA5. For the real W5500 work, remap SPI clock
  to a free pin to avoid this.
- **Signal words to use:** pin multiplexing / alternate function; "one physical
  pin, one function at a time"; elimination-based debugging; "suspect software
  before config."

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