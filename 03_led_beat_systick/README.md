# 03 - LED beat systick (Bare Metal STM32F103)

## Overview

This project demonstrates how to use the Cortex-M3 SysTick timer to generate periodic interrupts and control an onboard LED (PC13) on STM32F103C8T6.

Compared to a software delay loop, SysTick provides a **hardware-driven timing*, allowing the CPU to execute other tasks while waiting for interrupts.

Key concepts explored:

- Cortex-M SysTick timer
- Interrupt-driven programming (ISR)
- Vector table configuration
- Bare-metal register programming
- Startup code and linker behavior

---

## Hardware

- MCU: STM32F103C8T6 (Blue Pill)
- LED: On-board LED (PC13)
- Programmer: ST-Link V2

---

## Problem Summary & Debug Process

### 1. Incorrect SysTick configuration

- Misunderstood SysTick reload register limitation (24-bit counter)
- Use values beyond hardware capacity

✔ Fix:
- Corrected reload value within 24-bit range

---

### 2. SysTick interrupt not triggered

Symptom:
- LED stayed ON but did not blink

Root cause:
- SysTick_Handler was not correctly linked in the vector table

✔ Fix:
- Correct placement of `SysTick_Handler` in startup vector table (vector[15])

---

### 3. Interrupt not executing (silent failure)

Root cause:
- Vector table misalignment in startup.s
- Incorrect handler mapping caused CPU to fall into Default_Handler or invalid address

✔ Fix:
- Verified vector table order and handler names

---

### 4. Unexpected hardware recovery behavior

Observation:
- After reconnecting ST-Link, system started working

Root cause:
- MCU state corruption due to incorrect flashing/reset sequence

✔ Fix:
- Full power reset (disconnect/reconnect) ensured clean state

---

## What I Learned

### 1. Register-level programming
- Direct manipulation of SysTick, RCC, GPIO registers
- Understanding memory-mapped peripherals

---

### 2. Interrupt system fundamentals
- SysTick generates hardware interrupts
- CPU automatically enters ISR via vector table
- Execution returns to main loop after ISR

---

### 3. Toolchain understanding
- Startup.s defines vector table and reset behavior
- Linker script defines memory layout
- Makefile controls build pipeline

---

### 4. System-level thinking
- Interrupts are hardware-driven events, not software polling
- CPU is event-driven, not loop-driven

---

## SysTick Execution Flow
- counts down
- ↓
- Reload value reached
- ↓
- SysTick interrupt triggered
- ↓
- CPU enters SysTick_Handler
- ↓
- Toggle LED
- ↓
- Return to main loop

---

## Next Step

- NVIC interrupt controller
- External interrupt (EXTI)
- Event-driven input handling (button debounce)
