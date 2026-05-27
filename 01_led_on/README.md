# 01 - LED on

## Overview
This is my first STM32 bare-metal project using the STM32F103C8T6 (Blue Pill).

The goal is to understand how MCU peripherals are controlled at register level, including:
- Memory-mapped I/O
- GPIO configuration
- Clock enabling
- Basic data flow inside MCU

---

## Hardware
- MCU: STM32F103C8T6
- LED: On-board LED (PC13)
- Programmer: ST-Link V2

---

## Problems I Encountered

### 1. LED did not work at first
Root cause:
- GPIO clock was not enabled
- Incorrect understanding of register configuration order

Fix:
- Enabled RCC APB2 clock for GPIOC
- Configured GPIOC CRH register correctly

---

### 2. Firmware could not run after flashing
Root cause:
- Missing or incorrect vector table / startup configuration

Fix:
- Verified vector table placement in Flash memory
- Ensured correct reset handler execution flow

---

## What I Learned

### 1. GPIO Control Logic
- LED behavior depends on hardware circuit (active-low on PC13)
- GPIO registers control pin mode and output level

---

### 2. Register-Level Programming
- MCU peripherals are controlled via memory-mapped registers
- Learned how to calculate register addresses manually

---

### 3. Clock System (RCC)
- Peripheral must be enabled via RCC before use
- Without clock, GPIO registers have no effect

---

### 4. Bit Manipulation
- Learned practical usage of bitwise operations:
  - `1 << n`
  - masking and clearing bits

---

### 5. System Thinking
- Built initial mental model of MCU internal data flow:
  - CPU → Bus → Peripheral register → Hardware pin → Physical circuit

---

## Key Insight
A simple LED blink is not just software logic.
It is a full path:

CPU instruction → register write → hardware driver → electrical signal → LED

---

## Next Step
- Led beat
- SysTick timer
- Interrupt system (NVIC + EXTI)
- Event-driven LED control
