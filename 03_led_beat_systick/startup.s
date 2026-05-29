.syntax unified
.cpu cortex-m3
.thumb

.global g_pfnVectors
.global Reset_Handler
.global Default_Handler

.extern main
.extern _estack

@ 声明 C 语言编写的中断服务函数，防止符号物理断联
.global SysTick_Handler

.section .isr_vector,"a",%progbits
.align 2

g_pfnVectors:
    .word _estack                   @ 1: 物理栈顶指针 (MSP)
    .word Reset_Handler              @ 2: 复位入口
    .word Default_Handler            @ 3: NMI
    .word Default_Handler            @ 4: HardFault 硬件死锁陷阱
    .word Default_Handler            @ 5: MemManage
    .word Default_Handler            @ 6: BusFault
    .word Default_Handler            @ 7: UsageFault
    .word 0                          @ 8: 保留
    .word 0                          @ 9: 保留
    .word 0                          @ 10: 保留
    .word 0                          @ 11: 保留
    .word Default_Handler            @ 12: SVCall
    .word 0                          @ 13: 调试保留
    .word 0                          @ 14: 保留
    .word Default_Handler            @ 15: PendSV
    .word SysTick_Handler            @ 16: 精准对齐第16槽位：SysTick大门

.section .text

.thumb_func
Reset_Handler:
    @ 1. 物理显式初始化堆栈指针，让 C 语言运行环境彻底稳固
    ldr r0, =_estack
    mov sp, r0

    @ 2. 啪的一声，以绝对的 Thumb 状态物理跃迁至 C 语言 main 函数
    ldr r0, =main
    bx r0

.thumb_func
Default_Handler:
    @ 一旦芯片在启动阶段发生任何硬件硬伤（如HardFault），会被死死扣在这里
    b Default_Handler
