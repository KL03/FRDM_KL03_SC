/*
 * File:		main.c
 * Purpose:		Main process
 *
 */

#include "common.h"


/********************************************************************/
int main (void)
{

		SYST_CSR = 0x00;
		SYST_RVR = 48000;														/*使用内核时钟48MHz 每1ms翻转一次*/
		SYST_CVR = 0;
		SYST_CSR |= SysTick_CSR_ENABLE_MASK					/*使能systick*/
								| SysTick_CSR_TICKINT_MASK			/*打开systick中断*/
								| SysTick_CSR_CLKSOURCE_MASK;		/*使用内核时钟*/
	
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK				/*打开PORTA PORTB时钟门*/
							| SIM_SCGC5_PORTB_MASK;
					
		PORTB_PCR11 |= PORT_PCR_MUX(1);						/*PTB11复用为功能11 GPIO功能*/
		GPIOB_PDDR |= (1<<11);										/*PTB11设置为输出*/
		GPIOB_PSOR |= (1<<11);										/*PTB11置1,关闭绿灯*/  
	
		while(1)
		{

		} 
}
/********************************************************************/
void SysTick_Handler(void)
{
		GPIOB_PTOR |= (1<<11);
}
