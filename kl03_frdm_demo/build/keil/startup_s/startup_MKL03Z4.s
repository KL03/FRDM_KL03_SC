; * ---------------------------------------------------------------------------------------
; * @file:    startup_MKL03Z4.s
; * @purpose: CMSIS Cortex-M0P Core Device Startup File
; *           MKL03Z4
; * @version: 1.2
; * @date:    2014-4-30
; * ---------------------------------------------------------------------------------------
; *
; * Copyright: 1997 - 2014 Freescale Semiconductor, Inc.
; * All Rights Reserved.
; *
; * Redistribution and use in source and binary forms, with or without modification,
; * are permitted provided that the following conditions are met:
; *
; * o Redistributions of source code must retain the above copyright notice, this list
; *   of conditions and the following disclaimer.
; *
; * o Redistributions in binary form must reproduce the above copyright notice, this
; *   list of conditions and the following disclaimer in the documentation and/or
; *   other materials provided with the distribution.
; *
; * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
; *   contributors may be used to endorse or promote products derived from this
; *   software without specific prior written permission.
; *
; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
; * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
; * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
; * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
; * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
; * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
; * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
; * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
; * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; *
; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------
; *
; *****************************************************************************/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000100

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

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

__Vectors       DCD     __initial_sp  ; Top of Stack
                DCD     Reset_Handler  ; Reset Handler
                DCD     NMI_Handler  ; NMI Handler
                DCD     HardFault_Handler  ; Hard Fault Handler
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     SVC_Handler  ; SVCall Handler
                DCD     0  ; Reserved
                DCD     0  ; Reserved
                DCD     PendSV_Handler  ; PendSV Handler
                DCD     SysTick_Handler  ; SysTick Handler

                ; External Interrupts
                DCD     Reserved16_IRQHandler  ; Reserved interrupt
                DCD     Reserved17_IRQHandler  ; Reserved interrupt
                DCD     Reserved18_IRQHandler  ; Reserved interrupt
                DCD     Reserved19_IRQHandler  ; Reserved interrupt
                DCD     Reserved20_IRQHandler  ; Reserved interrupt
                DCD     FTFA_IRQHandler  ; Command complete and read collision
                DCD     PMC_IRQHandler  ; Low-voltage detect, low-voltage warning
                DCD     LLWU_IRQHandler  ; Low leakage wakeup
                DCD     I2C0_IRQHandler  ; I2C0 interrupt
                DCD     Reserved25_IRQHandler  ; Reserved interrupt
                DCD     SPI0_IRQHandler  ; SPI0 single interrupt vector for all sources
                DCD     Reserved27_IRQHandler  ; Reserved interrupt
                DCD     LPUART0_IRQHandler  ; LPUART0 status and error
                DCD     Reserved29_IRQHandler  ; Reserved interrupt
                DCD     Reserved30_IRQHandler  ; Reserved interrupt
                DCD     ADC0_IRQHandler  ; ADC0 interrupt
                DCD     CMP0_IRQHandler  ; CMP0 interrupt
                DCD     TPM0_IRQHandler  ; TPM0 single interrupt vector for all sources
                DCD     TPM1_IRQHandler  ; TPM1 single interrupt vector for all sources
                DCD     Reserved35_IRQHandler  ; Reserved interrupt
                DCD     RTC_IRQHandler  ; RTC alarm
                DCD     RTC_Seconds_IRQHandler  ; RTC seconds
                DCD     Reserved38_IRQHandler  ; Reserved interrupt
                DCD     Reserved39_IRQHandler  ; Reserved interrupt
                DCD     Reserved40_IRQHandler  ; Reserved interrupt
                DCD     Reserved41_IRQHandler  ; Reserved interrupt
                DCD     Reserved42_IRQHandler  ; Reserved interrupt
                DCD     Reserved43_IRQHandler  ; Reserved interrupt
                DCD     LPTMR0_IRQHandler  ; LPTMR0 interrupt
                DCD     Reserved45_IRQHandler  ; Reserved interrupt
                DCD     PORTA_IRQHandler  ; PORTA Pin detect
                DCD     PORTB_IRQHandler  ; PORTB Pin detect
__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

; <h> Flash Configuration
;   <i> 16-byte flash configuration field that stores default protection settings (loaded on reset)
;   <i> and security information that allows the MCU to restrict acces to the FTFL module.
;   <h> Backdoor Comparison Key
;     <o0>  Backdoor Key 0  <0x0-0xFF:2>
;     <o1>  Backdoor Key 1  <0x0-0xFF:2>
;     <o2>  Backdoor Key 2  <0x0-0xFF:2>
;     <o3>  Backdoor Key 3  <0x0-0xFF:2>
;     <o4>  Backdoor Key 4  <0x0-0xFF:2>
;     <o5>  Backdoor Key 5  <0x0-0xFF:2>
;     <o6>  Backdoor Key 6  <0x0-0xFF:2>
;     <o7>  Backdoor Key 7  <0x0-0xFF:2>
BackDoorK0      EQU     0xFF
BackDoorK1      EQU     0xFF
BackDoorK2      EQU     0xFF
BackDoorK3      EQU     0xFF
BackDoorK4      EQU     0xFF
BackDoorK5      EQU     0xFF
BackDoorK6      EQU     0xFF
BackDoorK7      EQU     0xFF
;   </h>
;   <h> Program flash protection bytes (FPROT)
;     <i> Each program flash region can be protected from program and erase operation by setting the associated PROT bit.
;     <i> Each bit protects a 1/32 region of the program flash memory.
;     <h> FPROT0
;       <i> Program flash protection bytes
;       <i> 1/32 - 8/32 region
;       <o.0>   FPROT0.0
;       <o.1>   FPROT0.1
;       <o.2>   FPROT0.2
;       <o.3>   FPROT0.3
;       <o.4>   FPROT0.4
;       <o.5>   FPROT0.5
;       <o.6>   FPROT0.6
;       <o.7>   FPROT0.7
nFPROT0         EQU     0x00
FPROT0          EQU     nFPROT0:EOR:0xFF
;     </h>
;     <h> FPROT1
;       <i> Program Flash Region Protect Register 1
;       <i> 9/32 - 16/32 region
;       <o.0>   FPROT1.0
;       <o.1>   FPROT1.1
;       <o.2>   FPROT1.2
;       <o.3>   FPROT1.3
;       <o.4>   FPROT1.4
;       <o.5>   FPROT1.5
;       <o.6>   FPROT1.6
;       <o.7>   FPROT1.7
nFPROT1         EQU     0x00
FPROT1          EQU     nFPROT1:EOR:0xFF
;     </h>
;     <h> FPROT2
;       <i> Program Flash Region Protect Register 2
;       <i> 17/32 - 24/32 region
;       <o.0>   FPROT2.0
;       <o.1>   FPROT2.1
;       <o.2>   FPROT2.2
;       <o.3>   FPROT2.3
;       <o.4>   FPROT2.4
;       <o.5>   FPROT2.5
;       <o.6>   FPROT2.6
;       <o.7>   FPROT2.7
nFPROT2         EQU     0x00
FPROT2          EQU     nFPROT2:EOR:0xFF
;     </h>
;     <h> FPROT3
;       <i> Program Flash Region Protect Register 3
;       <i> 25/32 - 32/32 region
;       <o.0>   FPROT3.0
;       <o.1>   FPROT3.1
;       <o.2>   FPROT3.2
;       <o.3>   FPROT3.3
;       <o.4>   FPROT3.4
;       <o.5>   FPROT3.5
;       <o.6>   FPROT3.6
;       <o.7>   FPROT3.7
nFPROT3         EQU     0x00
FPROT3          EQU     nFPROT3:EOR:0xFF
;     </h>
;   </h>
;   </h>
;   <h> Flash nonvolatile option byte (FOPT)
;     <i> Allows the user to customize the operation of the MCU at boot time.
;     <o.0>  LPBOOT0
;       <0=> Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) or 0x3 (divide by 4)
;       <1=> Core and system clock divider (OUTDIV1) is 0x1 (divide by 2) or 0x0 (divide by 1)
;     <o.4>  LPBOOT1
;       <0=> Core and system clock divider (OUTDIV1) is 0x7 (divide by 8) or 0x1 (divide by 2)
;       <1=> Core and system clock divider (OUTDIV1) is 0x3 (divide by 4) or 0x0 (divide by 1)
;     <o.1>  BOOTPIN_OPT
;       <0=> Force Boot from ROM if BOOTCFG0 asserted, where BOOTCFG0 is the boot config function which is muxed with NMI pin
;       <1=> Boot source configured by FOPT[BOOTSRC_SEL] bits
;     <o.2>  NMI_DIS
;       <0=> NMI interrupts are always blocked
;       <1=> NMI pin/interrupts reset default to enabled
;     <o.3>  RESET_PIN_CFG
;       <0=> RESET pin is disabled following a POR and cannot be enabled as RESET function
;       <1=> RESET pin is dedicated
;     <o.5>  FAST_INIT
;       <0=> Slower initialization
;       <1=> Fast Initialization
;     <o.6..7> BOOTSRC_SEL
;       <0=> Boot from Flash
;       <2=> Boot from ROM
;       <3=> Boot from ROM
FOPT            EQU     0x39
;   </h>
;   <h> Flash security byte (FSEC)
;     <i> WARNING: If SEC field is configured as "MCU security status is secure" and MEEN field is configured as "Mass erase is disabled",
;     <i> MCU's security status cannot be set back to unsecure state since Mass erase via the debugger is blocked !!!
;     <o.0..1> SEC
;       <2=> MCU security status is unsecure
;       <3=> MCU security status is secure
;         <i> Flash Security
;         <i> This bits define the security state of the MCU.
;     <o.2..3> FSLACC
;       <2=> Freescale factory access denied
;       <3=> Freescale factory access granted
;         <i> Freescale Failure Analysis Access Code
;         <i> This bits define the security state of the MCU.
;     <o.4..5> MEEN
;       <2=> Mass erase is disabled
;       <3=> Mass erase is enabled
;         <i> Mass Erase Enable Bits
;         <i> Enables and disables mass erase capability of the FTFL module
;     <o.6..7> KEYEN
;       <2=> Backdoor key access enabled
;       <3=> Backdoor key access disabled
;         <i> Backdoor key Security Enable
;         <i> These bits enable and disable backdoor key access to the FTFL module.
FSEC            EQU     0xFE
;   </h>

                IF      :LNOT::DEF:RAM_TARGET
                AREA    |.ARM.__at_0x400|, CODE, READONLY
                DCB     BackDoorK0, BackDoorK1, BackDoorK2, BackDoorK3
                DCB     BackDoorK4, BackDoorK5, BackDoorK6, BackDoorK7
                DCB     FPROT0,     FPROT1,     FPROT2,     FPROT3
                DCB     FSEC,       FOPT,       0xFF,     0xFF
                ENDIF

                AREA    |.text|, CODE, READONLY

;init_data_bss
;     User defined function for data and bs memory segment initialization.
;      Weak definition to be replaced by user code.

init_data_bss   PROC
                EXPORT  init_data_bss             [WEAK]
                BX      R14
                ENDP

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =init_data_bss
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
                EXPORT  Reserved16_IRQHandler     [WEAK]
                EXPORT  Reserved17_IRQHandler     [WEAK]
                EXPORT  Reserved18_IRQHandler     [WEAK]
                EXPORT  Reserved19_IRQHandler     [WEAK]
                EXPORT  Reserved20_IRQHandler     [WEAK]
                EXPORT  FTFA_IRQHandler     [WEAK]
                EXPORT  PMC_IRQHandler     [WEAK]
                EXPORT  LLWU_IRQHandler     [WEAK]
                EXPORT  I2C0_IRQHandler     [WEAK]
                EXPORT  Reserved25_IRQHandler     [WEAK]
                EXPORT  SPI0_IRQHandler     [WEAK]
                EXPORT  Reserved27_IRQHandler     [WEAK]
                EXPORT  LPUART0_IRQHandler     [WEAK]
                EXPORT  Reserved29_IRQHandler     [WEAK]
                EXPORT  Reserved30_IRQHandler     [WEAK]
                EXPORT  ADC0_IRQHandler     [WEAK]
                EXPORT  CMP0_IRQHandler     [WEAK]
                EXPORT  TPM0_IRQHandler     [WEAK]
                EXPORT  TPM1_IRQHandler     [WEAK]
                EXPORT  Reserved35_IRQHandler     [WEAK]
                EXPORT  RTC_IRQHandler     [WEAK]
                EXPORT  RTC_Seconds_IRQHandler     [WEAK]
                EXPORT  Reserved38_IRQHandler     [WEAK]
                EXPORT  Reserved39_IRQHandler     [WEAK]
                EXPORT  Reserved40_IRQHandler     [WEAK]
                EXPORT  Reserved41_IRQHandler     [WEAK]
                EXPORT  Reserved42_IRQHandler     [WEAK]
                EXPORT  Reserved43_IRQHandler     [WEAK]
                EXPORT  LPTMR0_IRQHandler     [WEAK]
                EXPORT  Reserved45_IRQHandler     [WEAK]
                EXPORT  PORTA_IRQHandler     [WEAK]
                EXPORT  PORTB_IRQHandler     [WEAK]
                EXPORT  DefaultISR                      [WEAK]

Reserved16_IRQHandler
Reserved17_IRQHandler
Reserved18_IRQHandler
Reserved19_IRQHandler
Reserved20_IRQHandler
FTFA_IRQHandler
PMC_IRQHandler
LLWU_IRQHandler
I2C0_IRQHandler
Reserved25_IRQHandler
SPI0_IRQHandler
Reserved27_IRQHandler
LPUART0_IRQHandler
Reserved29_IRQHandler
Reserved30_IRQHandler
ADC0_IRQHandler
CMP0_IRQHandler
TPM0_IRQHandler
TPM1_IRQHandler
Reserved35_IRQHandler
RTC_IRQHandler
RTC_Seconds_IRQHandler
Reserved38_IRQHandler
Reserved39_IRQHandler
Reserved40_IRQHandler
Reserved41_IRQHandler
Reserved42_IRQHandler
Reserved43_IRQHandler
LPTMR0_IRQHandler
Reserved45_IRQHandler
PORTA_IRQHandler
PORTB_IRQHandler
DefaultISR

                B       .

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
