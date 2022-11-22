;/******************************************************************************
; * Copyright (C) 2021, Xiaohua Semiconductor Co., Ltd. All rights reserved.
; *
; * This software component is licensed by XHSC under BSD 3-Clause license
; * (the "License"); You may not use this file except in compliance with the
; * License. You may obtain a copy of the License at:
; *                    opensource.org/licenses/BSD-3-Clause
; *
; ******************************************************************************/

;/*****************************************************************************/
;/*  Startup for ARM                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2021-12-02                                                   */
;/*  Target-mcu  M0+ Device                                                   */
;/*****************************************************************************/

; Stack Configuration
; Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00000100

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

Heap_Size       EQU     0x00000100

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors                       
                DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset        
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

                DCD     PORT0_IRQHandler
                DCD     PORT1_IRQHandler
                DCD     PORT2_IRQHandler
                DCD     PORT3_IRQHandler
                DCD     Dummy_Handler
                DCD     Dummy_Handler
                DCD     UART0_IRQHandler
                DCD     UART1_IRQHandler
                DCD     LPUART_IRQHandler
                DCD     Dummy_Handler
                DCD     SPI_IRQHandler
                DCD     Dummy_Handler
                DCD     I2C_IRQHandler
                DCD     Dummy_Handler
                DCD     TIM0_IRQHandler
                DCD     TIM1_IRQHandler
                DCD     TIM2_IRQHandler
                DCD     LPTIM_IRQHandler
                DCD     TIM4_IRQHandler
                DCD     TIM5_IRQHandler
                DCD     TIM6_IRQHandler
                DCD     PCA_IRQHandler
                DCD     WDT_IRQHandler
                DCD     RTC_IRQHandler
                DCD     ADC_IRQHandler
                DCD     Dummy_Handler
                DCD     VC0_IRQHandler
                DCD     VC1_IRQHandler
                DCD     LVD_IRQHandler
                DCD     Dummy_Handler
                DCD     EF_RAM_IRQHandler
                DCD     CLKTRIM_IRQHandler

                

__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

               ;reset NVIC if in rom debug
                LDR     R0, =0x20000000
                LDR     R2, =0x0
                MOVS    R1, #0                 ; for warning, 
                ADD     R1, PC,#0              ; for A1609W, 
                CMP     R1, R0
                BLS     RAMCODE

              ; ram code base address. 
                ADD     R2, R0,R2
RAMCODE
              ; reset Vector table address.
                LDR     R0, =0xE000ED08 
                STR     R2, [R0]

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
                
                
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  PORT0_IRQHandler                [WEAK]
                EXPORT  PORT1_IRQHandler                [WEAK]
                EXPORT  PORT2_IRQHandler                [WEAK]
                EXPORT  PORT3_IRQHandler                [WEAK]
                EXPORT  Dummy_Handler                   [WEAK]
                EXPORT  UART0_IRQHandler                [WEAK]
                EXPORT  UART1_IRQHandler                [WEAK]
                EXPORT  LPUART_IRQHandler               [WEAK]
                EXPORT  SPI_IRQHandler                  [WEAK]
                EXPORT  I2C_IRQHandler                  [WEAK]
                EXPORT  TIM0_IRQHandler                 [WEAK]
                EXPORT  TIM1_IRQHandler                 [WEAK]
                EXPORT  TIM2_IRQHandler                 [WEAK]
                EXPORT  LPTIM_IRQHandler                [WEAK]
                EXPORT  TIM4_IRQHandler                 [WEAK]
                EXPORT  TIM5_IRQHandler                 [WEAK]
                EXPORT  TIM6_IRQHandler                 [WEAK]
                EXPORT  PCA_IRQHandler                  [WEAK]
                EXPORT  WDT_IRQHandler                  [WEAK]
                EXPORT  RTC_IRQHandler                  [WEAK]
                EXPORT  ADC_IRQHandler                  [WEAK]
                EXPORT  VC0_IRQHandler                  [WEAK]
                EXPORT  VC1_IRQHandler                  [WEAK]
                EXPORT  LVD_IRQHandler                  [WEAK]
                EXPORT  EF_RAM_IRQHandler               [WEAK]
                EXPORT  CLKTRIM_IRQHandler              [WEAK]
PORT0_IRQHandler
PORT1_IRQHandler
PORT2_IRQHandler
PORT3_IRQHandler
Dummy_Handler
UART0_IRQHandler
UART1_IRQHandler
LPUART_IRQHandler
SPI_IRQHandler
I2C_IRQHandler
TIM0_IRQHandler
TIM1_IRQHandler
TIM2_IRQHandler
LPTIM_IRQHandler
TIM4_IRQHandler
TIM5_IRQHandler
TIM6_IRQHandler
PCA_IRQHandler
WDT_IRQHandler
RTC_IRQHandler
ADC_IRQHandler
VC0_IRQHandler
VC1_IRQHandler
LVD_IRQHandler
EF_RAM_IRQHandler
CLKTRIM_IRQHandler

                
               B .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
