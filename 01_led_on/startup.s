.syntax unified
.cpu cortex-m3
.thumb

.global g_pfnVectors
.global Reset_Handler

.extern main
.extern _estack

.section .isr_vector,"a",%progbits

g_pfnVectors:
.word _estack
.word Reset_Handler

.section .text
.type Reset_Handler, %function

Reset_Handler:
    bl main

LoopForever:
    b LoopForever
