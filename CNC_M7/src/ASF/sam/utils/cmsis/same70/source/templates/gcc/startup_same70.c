/**
 * \file
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifdef __cplusplus
extern "C" {
#endif


#include "same70.h"

#if __FPU_USED /* CMSIS defined value to indicate usage of FPU */
#include "fpu.h"
#endif

/* Initialize segments */
extern volatile uint32_t _s_fast_code_from;
extern volatile uint32_t _e_fast_code_from;
extern volatile uint32_t _s_fast_code;
extern volatile uint32_t _e_fast_code;

extern volatile uint32_t _s_data;
extern volatile uint32_t _e_data;
extern volatile uint32_t _s_data_from;
extern volatile uint32_t _e_data_from;

extern volatile uint32_t _s_fast_data;
extern volatile uint32_t _e_fast_data;
extern volatile uint32_t _s_fast_data_from;
extern volatile uint32_t _e_fast_data_from;

extern volatile uint32_t _s_bss;
extern volatile uint32_t _e_bss;

extern volatile uint32_t _s_fast_bss;
extern volatile uint32_t _e_fast_bss;

extern volatile uint32_t _s_stack;
extern volatile uint32_t _e_stack;

extern volatile uint32_t _e_runtime_stack;

/** \cond DOXYGEN_SHOULD_SKIP_THIS */
int main(void);
/** \endcond */

void __libc_init_array(void);

/* Default empty handler */
void Dummy_Handler(void);

/* Cortex-M7 core handlers */
void NMI_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void HardFault_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MemManage_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void BusFault_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UsageFault_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SVC_Handler        ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void DebugMon_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PendSV_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void SysTick_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));

/* Peripherals handlers */
void SUPC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RSTC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void RTT_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void WDT_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PMC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void EFC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART0_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART1_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOA_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PIOB_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_PIOC_INSTANCE_
void PIOC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_PIOC_INSTANCE_ */
#ifdef _SAME70_USART0_INSTANCE_
void USART0_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_USART0_INSTANCE_ */
#ifdef _SAME70_USART1_INSTANCE_
void USART1_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_USART1_INSTANCE_ */
#ifdef _SAME70_USART2_INSTANCE_
void USART2_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_USART2_INSTANCE_ */
void PIOD_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_PIOE_INSTANCE_
void PIOE_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_PIOE_INSTANCE_ */
#ifdef _SAME70_HSMCI_INSTANCE_
void HSMCI_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_HSMCI_INSTANCE_ */
void TWIHS0_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TWIHS1_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_SPI0_INSTANCE_
void SPI0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_SPI0_INSTANCE_ */
void SSC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC0_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC1_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC2_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_TC1_INSTANCE_
void TC3_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_TC1_INSTANCE_ */
#ifdef _SAME70_TC1_INSTANCE_
void TC4_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_TC1_INSTANCE_ */
#ifdef _SAME70_TC1_INSTANCE_
void TC5_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_TC1_INSTANCE_ */
void AFEC0_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_DACC_INSTANCE_
void DACC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_DACC_INSTANCE_ */
void PWM0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ICM_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ACC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void USBHS_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MCAN0_INT0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MCAN0_INT1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_MCAN1_INSTANCE_
void MCAN1_INT0_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void MCAN1_INT1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_MCAN1_INSTANCE_ */
void GMAC_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void AFEC1_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_TWIHS2_INSTANCE_
void TWIHS2_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_TWIHS2_INSTANCE_ */
#ifdef _SAME70_SPI1_INSTANCE_
void SPI1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_SPI1_INSTANCE_ */
void QSPI_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void UART2_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_UART3_INSTANCE_
void UART3_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_UART3_INSTANCE_ */
#ifdef _SAME70_UART4_INSTANCE_
void UART4_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_UART4_INSTANCE_ */
#ifdef _SAME70_TC2_INSTANCE_
void TC6_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_TC2_INSTANCE_ */
#ifdef _SAME70_TC2_INSTANCE_
void TC7_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_TC2_INSTANCE_ */
#ifdef _SAME70_TC2_INSTANCE_
void TC8_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_TC2_INSTANCE_ */
void TC9_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC10_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TC11_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void AES_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void TRNG_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void XDMAC_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void ISI_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void PWM1_Handler   ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void FPU_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_SDRAMC_INSTANCE_
void SDRAMC_Handler ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_SDRAMC_INSTANCE_ */
void RSWDT_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CCW_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void CCF_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void GMAC_Q1_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void GMAC_Q2_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void IXC_Handler    ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#ifdef _SAME70_I2SC0_INSTANCE_
void I2SC0_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_I2SC0_INSTANCE_ */
#ifdef _SAME70_I2SC1_INSTANCE_
void I2SC1_Handler  ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif /* _SAME70_I2SC1_INSTANCE_ */
#if (__SAM_M7_REVB == 1)
void GMAC_Q3_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void GMAC_Q4_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
void GMAC_Q5_Handler     ( void ) __attribute__ ((weak, alias("Dummy_Handler")));
#endif

/* Exception Table */

__attribute__ ((section(".vectors")))__attribute__((aligned(64)))__attribute__((optimize("O0")))
const DeviceVectors exception_table = {

        /* Configure Initial Stack Pointer, using linker-generated symbols */
        .pvStack = (void*) (&_e_stack),

        .pfnReset_Handler      = (void*) Reset_Handler,
        .pfnNMI_Handler        = (void*) NMI_Handler,
        .pfnHardFault_Handler  = (void*) HardFault_Handler,
        .pfnMemManage_Handler  = (void*) MemManage_Handler,
        .pfnBusFault_Handler   = (void*) BusFault_Handler,
        .pfnUsageFault_Handler = (void*) UsageFault_Handler,
        .pfnReserved1_Handler  = (void*) (0UL),          /* Reserved */
        .pfnReserved2_Handler  = (void*) (0UL),          /* Reserved */
        .pfnReserved3_Handler  = (void*) (0UL),          /* Reserved */
        .pfnReserved4_Handler  = (void*) (0UL),          /* Reserved */
        .pfnSVC_Handler        = (void*) SVC_Handler,
        .pfnDebugMon_Handler   = (void*) DebugMon_Handler,
        .pfnReserved5_Handler  = (void*) (0UL),          /* Reserved */
        .pfnPendSV_Handler     = (void*) PendSV_Handler,
        .pfnSysTick_Handler    = (void*) SysTick_Handler,

        /* Configurable interrupts */
        .pfnSUPC_Handler   = (void*) SUPC_Handler,   /* 0  Supply Controller */
        .pfnRSTC_Handler   = (void*) RSTC_Handler,   /* 1  Reset Controller */
        .pfnRTC_Handler    = (void*) RTC_Handler,    /* 2  Real Time Clock */
        .pfnRTT_Handler    = (void*) RTT_Handler,    /* 3  Real Time Timer */
        .pfnWDT_Handler    = (void*) WDT_Handler,    /* 4  Watchdog Timer */
        .pfnPMC_Handler    = (void*) PMC_Handler,    /* 5  Power Management Controller */
        .pfnEFC_Handler    = (void*) EFC_Handler,    /* 6  Enhanced Embedded Flash Controller */
        .pfnUART0_Handler  = (void*) UART0_Handler,  /* 7  UART 0 */
        .pfnUART1_Handler  = (void*) UART1_Handler,  /* 8  UART 1 */
        .pvReserved9       = (void*) (0UL),          /* 9  Reserved */
        .pfnPIOA_Handler   = (void*) PIOA_Handler,   /* 10 Parallel I/O Controller A */
        .pfnPIOB_Handler   = (void*) PIOB_Handler,   /* 11 Parallel I/O Controller B */
#ifdef _SAME70_PIOC_INSTANCE_
        .pfnPIOC_Handler   = (void*) PIOC_Handler,   /* 12 Parallel I/O Controller C */
#else
        .pvReserved12      = (void*) (0UL),          /* 12 Reserved */
#endif /* _SAME70_PIOC_INSTANCE_ */
#ifdef _SAME70_USART0_INSTANCE_
        .pfnUSART0_Handler = (void*) USART0_Handler, /* 13 USART 0 */
#else
        .pvReserved13      = (void*) (0UL),          /* 13 Reserved */
#endif /* _SAME70_USART0_INSTANCE_ */
#ifdef _SAME70_USART1_INSTANCE_
        .pfnUSART1_Handler = (void*) USART1_Handler, /* 14 USART 1 */
#else
        .pvReserved14      = (void*) (0UL),          /* 14 Reserved */
#endif /* _SAME70_USART1_INSTANCE_ */
#ifdef _SAME70_USART2_INSTANCE_
        .pfnUSART2_Handler = (void*) USART2_Handler, /* 15 USART 2 */
#else
        .pvReserved15      = (void*) (0UL),          /* 15 Reserved */
#endif /* _SAME70_USART2_INSTANCE_ */
        .pfnPIOD_Handler   = (void*) PIOD_Handler,   /* 16 Parallel I/O Controller D */
#ifdef _SAME70_PIOE_INSTANCE_
        .pfnPIOE_Handler   = (void*) PIOE_Handler,   /* 17 Parallel I/O Controller E */
#else
        .pvReserved17      = (void*) (0UL),          /* 17 Reserved */
#endif /* _SAME70_PIOE_INSTANCE_ */
#ifdef _SAME70_HSMCI_INSTANCE_
        .pfnHSMCI_Handler  = (void*) HSMCI_Handler,  /* 18 Multimedia Card Interface */
#else
        .pvReserved18      = (void*) (0UL),          /* 18 Reserved */
#endif /* _SAME70_HSMCI_INSTANCE_ */
        .pfnTWIHS0_Handler = (void*) TWIHS0_Handler, /* 19 Two Wire Interface 0 HS */
        .pfnTWIHS1_Handler = (void*) TWIHS1_Handler, /* 20 Two Wire Interface 1 HS */
#ifdef _SAME70_SPI0_INSTANCE_
        .pfnSPI0_Handler   = (void*) SPI0_Handler,   /* 21 Serial Peripheral Interface 0 */
#else
        .pvReserved21      = (void*) (0UL),          /* 21 Reserved */
#endif /* _SAME70_SPI0_INSTANCE_ */
        .pfnSSC_Handler    = (void*) SSC_Handler,    /* 22 Synchronous Serial Controller */
        .pfnTC0_Handler    = (void*) TC0_Handler,    /* 23 Timer/Counter 0 */
        .pfnTC1_Handler    = (void*) TC1_Handler,    /* 24 Timer/Counter 1 */
        .pfnTC2_Handler    = (void*) TC2_Handler,    /* 25 Timer/Counter 2 */
#ifdef _SAME70_TC1_INSTANCE_
        .pfnTC3_Handler    = (void*) TC3_Handler,    /* 26 Timer/Counter 3 */
#else
        .pvReserved26      = (void*) (0UL),          /* 26 Reserved */
#endif /* _SAME70_TC1_INSTANCE_ */
#ifdef _SAME70_TC1_INSTANCE_
        .pfnTC4_Handler    = (void*) TC4_Handler,    /* 27 Timer/Counter 4 */
#else
        .pvReserved27      = (void*) (0UL),          /* 27 Reserved */
#endif /* _SAME70_TC1_INSTANCE_ */
#ifdef _SAME70_TC1_INSTANCE_
        .pfnTC5_Handler    = (void*) TC5_Handler,    /* 28 Timer/Counter 5 */
#else
        .pvReserved28      = (void*) (0UL),          /* 28 Reserved */
#endif /* _SAME70_TC1_INSTANCE_ */
        .pfnAFEC0_Handler  = (void*) AFEC0_Handler,  /* 29 Analog Front End 0 */
#ifdef _SAME70_DACC_INSTANCE_
        .pfnDACC_Handler   = (void*) DACC_Handler,   /* 30 Digital To Analog Converter */
#else
        .pvReserved30      = (void*) (0UL),          /* 30 Reserved */
#endif /* _SAME70_DACC_INSTANCE_ */
        .pfnPWM0_Handler   = (void*) PWM0_Handler,   /* 31 Pulse Width Modulation 0 */
        .pfnICM_Handler    = (void*) ICM_Handler,    /* 32 Integrity Check Monitor */
        .pfnACC_Handler    = (void*) ACC_Handler,    /* 33 Analog Comparator */
        .pfnUSBHS_Handler  = (void*) USBHS_Handler,  /* 34 USB Host / Device Controller */
        .pfnMCAN0_INT0_Handler = (void*) MCAN0_INT0_Handler, /* 35 Controller Area Network */
        .pfnMCAN0_INT1_Handler = (void*) MCAN0_INT1_Handler, /* 36 Controller Area Network */
#ifdef _SAME70_MCAN1_INSTANCE_
        .pfnMCAN1_INT0_Handler = (void*) MCAN1_INT0_Handler, /* 37 Controller Area Network */
        .pfnMCAN1_INT1_Handler = (void*) MCAN1_INT1_Handler, /* 38 Controller Area Network */
#else
        .pvReserved37      = (void*) (0UL),          /* 37 Reserved */
        .pvReserved38      = (void*) (0UL),          /* 38 Reserved */
#endif /* _SAME70_MCAN1_INSTANCE_ */
        .pfnGMAC_Handler   = (void*) GMAC_Handler,   /* 39 Ethernet MAC */
        .pfnAFEC1_Handler  = (void*) AFEC1_Handler,  /* 40 Analog Front End 1 */
#ifdef _SAME70_TWIHS2_INSTANCE_
        .pfnTWIHS2_Handler = (void*) TWIHS2_Handler, /* 41 Two Wire Interface 2 HS */
#else
        .pvReserved41      = (void*) (0UL),          /* 41 Reserved */
#endif /* _SAME70_TWIHS2_INSTANCE_ */
#ifdef _SAME70_SPI1_INSTANCE_
        .pfnSPI1_Handler   = (void*) SPI1_Handler,   /* 42 Serial Peripheral Interface 1 */
#else
        .pvReserved42      = (void*) (0UL),          /* 42 Reserved */
#endif /* _SAME70_SPI1_INSTANCE_ */
        .pfnQSPI_Handler   = (void*) QSPI_Handler,   /* 43 Quad I/O Serial Peripheral Interface */
        .pfnUART2_Handler  = (void*) UART2_Handler,  /* 44 UART 2 */
#ifdef _SAME70_UART3_INSTANCE_
        .pfnUART3_Handler  = (void*) UART3_Handler,  /* 45 UART 3 */
#else
        .pvReserved45      = (void*) (0UL),          /* 45 Reserved */
#endif /* _SAME70_UART3_INSTANCE_ */
#ifdef _SAME70_UART4_INSTANCE_
        .pfnUART4_Handler  = (void*) UART4_Handler,  /* 46 UART 4 */
#else
        .pvReserved46      = (void*) (0UL),          /* 46 Reserved */
#endif /* _SAME70_UART4_INSTANCE_ */
#ifdef _SAME70_TC2_INSTANCE_
        .pfnTC6_Handler    = (void*) TC6_Handler,    /* 47 Timer/Counter 6 */
#else
        .pvReserved47      = (void*) (0UL),          /* 47 Reserved */
#endif /* _SAME70_TC2_INSTANCE_ */
#ifdef _SAME70_TC2_INSTANCE_
        .pfnTC7_Handler    = (void*) TC7_Handler,    /* 48 Timer/Counter 7 */
#else
        .pvReserved48      = (void*) (0UL),          /* 48 Reserved */
#endif /* _SAME70_TC2_INSTANCE_ */
#ifdef _SAME70_TC2_INSTANCE_
        .pfnTC8_Handler    = (void*) TC8_Handler,    /* 49 Timer/Counter 8 */
#else
        .pvReserved49      = (void*) (0UL),          /* 49 Reserved */
#endif /* _SAME70_TC2_INSTANCE_ */
        .pfnTC9_Handler    = (void*) TC9_Handler,    /* 50 Timer/Counter 9 */
        .pfnTC10_Handler   = (void*) TC10_Handler,   /* 51 Timer/Counter 10 */
        .pfnTC11_Handler   = (void*) TC11_Handler,   /* 52 Timer/Counter 11 */
        .pvReserved53      = (void*) (0UL),          /* 53 Reserved */
        .pvReserved54      = (void*) (0UL),          /* 54 Reserved */
        .pvReserved55      = (void*) (0UL),          /* 55 Reserved */
        .pfnAES_Handler    = (void*) AES_Handler,    /* 56 AES */
        .pfnTRNG_Handler   = (void*) TRNG_Handler,   /* 57 True Random Generator */
        .pfnXDMAC_Handler  = (void*) XDMAC_Handler,  /* 58 DMA */
        .pfnISI_Handler    = (void*) ISI_Handler,    /* 59 Camera Interface */
        .pfnPWM1_Handler   = (void*) PWM1_Handler,   /* 60 Pulse Width Modulation 1 */
        .pfnFPU_Handler    = (void*) FPU_Handler,    /* 61 Floating Point Unit Registers */
#ifdef _SAME70_SDRAMC_INSTANCE_
        .pfnSDRAMC_Handler = (void*) SDRAMC_Handler, /* 62 SDRAM Controller */
#else
        .pvReserved62      = (void*) (0UL),          /* 62 Reserved */
#endif /* _SAME70_SDRAMC_INSTANCE_ */
        .pfnRSWDT_Handler  = (void*) RSWDT_Handler,  /* 63 Reinforced Secure Watchdog Timer */
        .pfnCCW_Handler    = (void*) CCW_Handler,    /* 64 System Control Registers */
        .pfnCCF_Handler    = (void*) CCF_Handler,    /* 65 System Control Registers */
        .pfnGMAC_Q1_Handler= (void*) GMAC_Q1_Handler,/* 66 Gigabit Ethernet MAC */
        .pfnGMAC_Q2_Handler= (void*) GMAC_Q2_Handler,/* 67 Gigabit Ethernet MAC */
        .pfnIXC_Handler    = (void*) IXC_Handler,    /* 68 Floating Point Unit Registers */
#ifdef _SAME70_I2SC0_INSTANCE_
        .pfnI2SC0_Handler  = (void*) I2SC0_Handler,  /* 69 Inter-IC Sound controller */
#else
        .pvReserved69      = (void*) (0UL),          /* 69 Reserved */
#endif /* _SAME70_I2SC0_INSTANCE_ */
#ifdef _SAME70_I2SC1_INSTANCE_
        .pfnI2SC1_Handler  = (void*) I2SC1_Handler,  /* 70 Inter-IC Sound controller */
#else
        .pvReserved70      = (void*) (0UL),          /* 70 Reserved */
#endif /* _SAME70_I2SC1_INSTANCE_ */
#if (__SAM_M7_REVB == 1)
        .pfnGMAC_Q3_Handler= (void*) GMAC_Q3_Handler,/* 71 Gigabit Ethernet MAC */
        .pfnGMAC_Q4_Handler= (void*) GMAC_Q4_Handler,/* 72 Gigabit Ethernet MAC */
        .pfnGMAC_Q5_Handler= (void*) GMAC_Q5_Handler /* 73 Gigabit Ethernet MAC */
#else
        .pvReserved71      = (void*) (0UL),          /* 71 Reserved */
        .pvReserved72      = (void*) (0UL),          /* 72 Reserved */
        .pvReserved73      = (void*) (0UL)           /* 73 Reserved */
#endif
};

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
 __attribute__ ((optimize("O0")))__attribute__((aligned(64)))
void Reset_Handler(void)
{
	volatile uint32_t *pSrc;
	volatile uint32_t *pSrcEnd;
	volatile uint32_t *pDest;
	volatile uint32_t *pDestEnd;
	volatile uint32_t ulEEFC_bits;
	volatile uint32_t dtcm_stack_pointer_addr;

	// Configure TCM with maximum Size
	// 128 KByte Data
	// 128 KByte Program

	__DSB();
	__ISB();
	EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_GGPB);
	__DSB();
	__ISB();

	while (!(EFC->EEFC_FSR & EEFC_FSR_FRDY));      //Wait until the status falls to 0 (EFFC command is complete)

	ulEEFC_bits = EFC->EEFC_FRR;

	if ((ulEEFC_bits & 0x180) != 0x180)
	{
		__DSB();
		__ISB();
		EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_SGPB | EEFC_FCR_FARG(7));  //issue command to clear bit 7
		__DSB();
		__ISB();

		while(!(EFC->EEFC_FSR & EEFC_FSR_FRDY));     //Wait until the status falls to 0 (EFFC command is complete)

		__DSB();
		__ISB();
		EFC->EEFC_FCR = (EEFC_FCR_FKEY_PASSWD | EEFC_FCR_FCMD_SGPB | EEFC_FCR_FARG(8));  //issue command to clear bit 8
		__DSB();
		__ISB();

		while(!(EFC->EEFC_FSR & EEFC_FSR_FRDY));     //Wait until the status falls to 0 (EFFC command is complete)

		__DSB();
		__ISB();

		//Trigger Reset
		RSTC->RSTC_CR = RSTC_CR_KEY_PASSWD | RSTC_CR_PROCRST;

		__DSB();
		__ISB();
	}

	// Enable DTCM and ITCM
	__DSB();
	__ISB();
	SCB->ITCMCR = (SCB_DTCMCR_EN_Msk | SCB_DTCMCR_RMW_Msk | SCB_DTCMCR_RETEN_Msk);
	SCB->DTCMCR = (SCB_DTCMCR_EN_Msk | SCB_DTCMCR_RMW_Msk | SCB_DTCMCR_RETEN_Msk);
	__DSB();
	__ISB();

	// Copy Vector Table to beginning of ITCM (Address 0)
	pSrc  = (uint32_t*)&exception_table;
	pDest  = (uint32_t*)0;
	pDestEnd = (uint32_t*)sizeof (DeviceVectors);

	for (; pDest < pDestEnd;)
	{
		*pDest++ = *pSrc++;
	}

	// Copy fast Code from Flash into ITCM
	pSrc  = &_s_fast_code_from;
	pSrcEnd  = &_e_fast_code_from;
	pDest  = &_s_fast_code;
	pDestEnd = &_e_fast_code;

	for (; pDest < pDestEnd;)
	{
		*pDest++ = *pSrc++;
	}

	// Copy data segments into DTCM and System RAM
	pSrc  = &_s_data_from;
	pSrcEnd  = &_e_data_from;
	pDest  = &_s_data;
	pDestEnd = &_e_data;

	while (pDest < pDestEnd)
	{
		*pDest++ = *pSrc++;
	}

	pSrc  = &_s_fast_data_from;
	pSrcEnd  = &_e_fast_data_from;
	pDest  = &_s_fast_data;
	pDestEnd = &_e_fast_data;

	while (pDest < pDestEnd)
	{
		*pDest++ = *pSrc++;
	}

	// Clear the zero segments in DTCM and System RAM
	pDest  = &_s_bss;
	pDestEnd = &_e_bss;
	while (pDest < pDestEnd)
	{
		*pDest++ = 0;
	}

	pDest  = &_s_fast_bss;
	pDestEnd = &_e_fast_bss;
	while (pDest < pDestEnd)
	{
		*pDest++ = 0;
	}

	// Set the vector table base address
	// to the copied table in ITCM (Address 0)
	pSrc = (uint32_t *) 0;

	SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

	//Now that we're at the point in this routine where we don't need any stack variables,
	//update our stack pointer to the runtime stack pointer that lives in DTCM
	dtcm_stack_pointer_addr = (uint32_t)&_e_runtime_stack;

	//asm(code : output operand list : input operand list : clobber list);
	__ASM volatile ("mov.w r1, %0"::"r" (dtcm_stack_pointer_addr):"r1");    //write r1 with the address of DTCM where the beginning of the stack lives (per the linker)
	__ASM volatile("mov sp, r1");              //update the stack pointer with the stack address that lives in r1

	__DSB();
	__ISB();

	/* Initialize the C library */
	__libc_init_array();

	/* Branch to main function */
	main();

	/* Infinite loop */
	while (1);
}

/**
 * \brief Default interrupt handler for unused IRQs.
 */
void Dummy_Handler(void)
{
    while (1) {
		pmc_enable_periph_clk(ID_PIOC);
		pio_configure(PIOC, (0x6u << 27), PIO_PC8, 0);

	    pio_clear(PIOC, PIO_PC8);
	    uint32_t volatile z = 0xff;
	    while(z--){};
	    pio_set(PIOC, PIO_PC8);
	    z = 0xFFFFF;
	    while(z--){};
    }
}

#ifdef __cplusplus
}
#endif
