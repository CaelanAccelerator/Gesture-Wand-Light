# Gesture-Controlled Smart Light

An STM32 firmware project: wave a wand, and a light responds — changing color,
brightness, or turning on/off. Built in C++ with a clean separation between
portable logic and hardware drivers, designed so the current mock setup swaps
out for a real motion sensor, addressable LEDs, and a wireless (BLE) link.

**Hardware:** STM32 Nucleo-F446RE (ARM Cortex-M4)
**Embedded topics used:** GPIO, UART, external + UART interrupts (EXTI / NVIC),
timers, bare-metal C++ with the STM32 HAL, Git

---

## What it does today

- A gesture travels through a real **UART round-trip** (board → PC → board) and
  drives the light — proving the full send → transport → receive → render path.
- The light supports **on/off, brightness, and color-palette switching**, each
  triggered by a gesture.
- A **gradient rendering engine** paints smooth color transitions across the LEDs.
- Gesture transport is **interrupt-driven**, with serialization over UART so it
  can later become a Bluetooth link with no change to the rest of the code.

## How it's built

```
Wand: motion → detect gesture → send  ──UART/BLE──►  Light: receive → control → render
```

The code is split into two layers:

- **Logic layer** (`App/core/`) — gesture detection, light state, rendering.
  Pure C++, no hardware dependencies, so it ports to another chip unchanged.
- **Driver layer** (`App/driver/`) — the hardware-specific code (UART, LEDs,
  button). Swapping hardware means rewriting only this layer.

This separation is the main design idea: the light controller and renderer never
touch hardware directly — they talk to interfaces (`ISender` / `IReceiver` /
`ILight`), so a mock LED becomes a real LED strip, and UART becomes Bluetooth,
without rewriting the logic.

## What's next

Real IMU motion sensor over **I2C**, WS2812 LED strip via **PWM + DMA**,
gyro-based gestures, an RTOS for animation, and migrating the wand end to an
**nRF52840** with **BLE**.

---

## Notes

- Built and debugged on STM32CubeIDE; a Python script on the PC acts as the
  transport bridge.
- Debugging stories (the tricky bugs and how I tracked them down) are in
  **`DEBUGGING_STORIES.md`** — mostly _silent failures_ with no error message,
  found by tracing the signal step by step rather than guessing.

**Repo:** https://github.com/CaelanAccelerator/Gesture-Wand-Light
