/*
 * File:		platinum.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "MKL_gpio.h"
#include "uart.h"
#include "lptmr.h"
#include "smc.h"

uint8 data;
uint8 i;
extern int uart0_clk_khz;
extern int mcg_clk_hz;

/********************************************************************/
#define MCGIRCLK		0
#define LPO					1
#define ERCLK32K		2
#define OSCERCLK		3
/********************************************************************/

void uart0_lpconfigure(void);

int main (void)
{
	
	uint8 tmp;
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
							| SIM_SCGC5_PORTB_MASK );
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;
	tmp = RTC_TSR;
	RTC_TSR = tmp;
	SIM_SCGC6 &= ~SIM_SCGC6_RTC_MASK;
	
	IO_FUN_SEL(MKL_PORTB,5,1);									/*IO����ѡ��*/    
	GPIO_DDR_INPUT(MKL_PORTB,0); 								/*����Ϊ����ģʽ*/    

	IO_IRQ_CONFIG(MKL_PORTB,5,0x0A);						/*PTB5 SW3 �½��ش����ж�*/
	
	IO_FUN_SEL(MKL_PORTB,0,1);									/*IO����ѡ��*/    
	GPIO_DDR_INPUT(MKL_PORTB,0); 								/*����Ϊ����ģʽ*/    
	
	IO_IRQ_CONFIG(MKL_PORTB,0,0x0A);						/*PTB0 SW2 �½��ش����ж�*/
	
	enable_irq(INT_PORTB - 16);									/*ʹ�ܰ����ж�*/

	enable_irq(INT_UART0 - 16);															/*ʹ��LPUART0�ж�, LPUART0��ʼ����sysinit()��*/
	
//	SYST_CSR = 0x00;
//	SYST_RVR = 48000;														/*ʹ���ں�ʱ��48MHz ÿ1ms��תһ��*/
//	SYST_CVR = 0;
//	SYST_CSR |= SysTick_CSR_ENABLE_MASK
//							| SysTick_CSR_TICKINT_MASK
//							| SysTick_CSR_CLKSOURCE_MASK;	

	while(1)
	{
		if(i == 1)
		{
				i = 0;
				uart0_lpconfigure();
				enter_vlps();
		}
	} 	
}


void uart0_lpconfigure(void)
{
		MCG_C1 |= MCG_C1_IRCLKEN_MASK | MCG_C1_IREFSTEN_MASK;
		//MCG_C2 &= ~MCG_C2_IRCS_MASK;													//when use IRC8M this should be commented
		SIM_SOPT2 |= SIM_SOPT2_UART0SRC(3); 										// select the MCGIRCLK as UART0 clock source
		//uart0_clk_khz = MCG_IRC2M;														//test up to 14400
		uart0_clk_khz = MCG_IRC8M;															//test up to 38400
		uart0_init (TERM_PORT,uart0_clk_khz,TERMINAL_BAUD);  
}
void PORTB_IRQHandler(void)
{
	if(PORTB_ISFR & (1<<5))
	{
		PORTB_ISFR |= PORT_ISFR_ISF(1<<5);
	}
	if(PORTB_ISFR & (1<<0))
	{
		PORTB_ISFR |= PORT_ISFR_ISF(1<<0);
		i = 1;
	}
}

void LPUART0_IRQHandler(void)
{
	if(LPUART0_STAT & LPUART_STAT_OR_MASK)
	{
		LPUART0_STAT |= LPUART_STAT_OR_MASK;			/*д1������ж�*/
	}
	
	if(LPUART0_STAT & LPUART_STAT_RDRF_MASK)		/*����������*/
	{
		data = LPUART0_DATA;
		out_char(data);
		i = 0;
	}
}


//void SysTick_Handler(void)
//{
//	uint8 i; 
//	GPIO_TOGGLE(MKL_PORTB,11);
//	i = SYST_CSR;																/*��SYST_CSR,��COUNTFLAG*/
//}
