# 04 - External Interrupt (EXTI) LED control (Bare Metal STM32F103)

## Overview

This project demonstrates how to use the Cortex-M3 external interrupt (EXTI) to generate interrupts and control an onboard LED (PC13) on STM32F103C8T6.

Key concepts explored:

- EXTI (External Interrupt/Event Controller)
- NVIC (Nested Vectored Interrupt Controller)
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

### 1. Missing Pull-up Configuration

symptom:
- EXTI interrupt was not triggered reliably.

Root Cause:
- PA0 was configured as an input but the internal pull-up resister was not enabled. 
- The input pin remained floating, causing unstable behavior.

✔ Fix:
- Configure PA0 as input pull-up mode. 
- Enable the external pull-up resistor through GPIOA_ODR. 
- Configure EXTI to trigger on the falling edge using EXTI_FTSR

---

### 2. Missing NVIC configuration

Symptom:

- EXTI pending flag was set,but the CPU never entered the interrupt handler.

Root cause:

- EXTI line was configured correctly, but the interrupt was not enabled in NVIC.  

✔ Fix:
- Read the Cortex-M3 and STM32 reference manuals. 
- Enable EXTI0 interrup through NVIC_ISER)
- Use IRQ number 6(EXTI0_IRQHandler)


### 3. Interrupt Flag not clear. 

Symptom:

- Interrupt behavior became unstable after the first trigger. 

Root cause:

- EXTI pending flag remained set after the interrupt.

✔ Fix:
- Clear the pending flag by writing to EXTI_PR inside the ISR. 

---

### 4. Interrupt Handler not executing.

Sympthon:
- LED on and never changed state after triggering PA0. 

Root cause:
- Incorrct Vector table configuration
- Interrupt handler was placed at the wrong vector position.

✔ Fix:
- Verified vector table layout. 
- Ensure EXTI0_IRQHandler is located at the correct vector index. 

---

### 4. LED unexpectedly turn off after flashing.

Sympthon:
- LED off after programming the MCU.
- NOK after disconnecting the ST-link and insert back.


Root cause:
- Previous faulty startup code or vector table configuration left the MCU  in an unexpected state. 

✔ Fix:
- Reflash a known-good project. 
- Reflash the EXTI project. 
- Perform a full hardware reset if necessary. 

---

## What I Learned

### 1. Register-level programming
- Configured AFIO,EXTI,NVIC directly through registers
- Built a deeper understanding of how hardware interrputs work. 

---

### 2. Interrupt system fundamentals
- External signal can generate hadware interrups.
- NVIC manages interrupt requests and priorities. 
- CPU automatically enters the ISR through the vector table. 
- After ISR execution, CPU returns to the interrupted code. 
- Execution returns to main loop after ISR

---

### 3. Toolchain understanding
- Startup.s defines vector table and reset behavior
- Linker.ld determines memory layout. 
- Correct startup configuration is essential for interrupt execution. 

---

### 4. System-level thinking
- Interrupts are hardware-driven events, not software polling
- CPU is event-driven, not loop-driven
- Interrupts provide an efficient mechanism for communication between external hardware and software. 

---

## EXTI Execution Flow
- PA0 input signal. 
- ↓
- AFIO maps PA0 to EXTI0
- ↓
- EXTI detects falling edge. 
- ↓
- EXTI sets pending flag. 
-  ↓
- NVIC recieve the interrupts request. 
- ↓
- CPU enters EXTI0_IRQHandler
- ↓
- Trigger LED state
- ↓
- Clear EXTI pending flag. 
-  ↓
- Return to main loop

---

## Next Step


- Button debounce using SysTick
- Combining EXTI and timer interrupts
- Event-driven embedded software design
