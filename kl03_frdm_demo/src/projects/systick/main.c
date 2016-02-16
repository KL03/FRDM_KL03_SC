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
		SYST_RVR = 48000;														/*ʹ���ں�ʱ��48MHz ÿ1ms��תһ��*/
		SYST_CVR = 0;
		SYST_CSR |= SysTick_CSR_ENABLE_MASK					/*ʹ��systick*/
								| SysTick_CSR_TICKINT_MASK			/*��systick�ж�*/
								| SysTick_CSR_CLKSOURCE_MASK;		/*ʹ���ں�ʱ��*/
	
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK				/*��PORTA PORTBʱ����*/
							| SIM_SCGC5_PORTB_MASK;
					
		PORTB_PCR11 |= PORT_PCR_MUX(1);						/*PTB11����Ϊ����11 GPIO����*/
		GPIOB_PDDR |= (1<<11);										/*PTB11����Ϊ���*/
		GPIOB_PSOR |= (1<<11);										/*PTB11��1,�ر��̵�*/  
	
		while(1)
		{

		} 
}
/********************************************************************/
void SysTick_Handler(void)
{
		GPIOB_PTOR |= (1<<11);
}
