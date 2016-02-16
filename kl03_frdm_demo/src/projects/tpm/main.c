/*
 * File:		main.c
 * Purpose:		Main process
 *
 */

#include "common.h"

void TPM_init(void)
{
		SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);	  																/*48MHz 作为TPM时钟源*/
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK| SIM_SCGC6_TPM1_MASK;   						/*打开TPM时钟门*/

		TPM0_CNT = 0;
		TPM0_MOD = 48000;
	
		TPM0_SC |= TPM_SC_PS(7);																						/*设置分频系数 128分频*/
		TPM0_SC |= TPM_SC_TOIE_MASK|TPM_SC_CMOD(1);													/*使能中断, 选择模式1, 每个计数器时钟加1*/
		
		TPM0_C0SC = TPM_CnSC_MSB_MASK| TPM_CnSC_ELSB_MASK;									/*边沿对齐模式*/
		TPM0_C0V = 0;
		
		enable_irq(INT_TPM0 - 16);																					/*使能中断*/
}
/********************************************************************/
int main (void)
{  
	
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK				/*打开PORTA PORTB时钟门*/
							| SIM_SCGC5_PORTB_MASK;
					
		PORTB_PCR11 |= PORT_PCR_MUX(1);						/*PTB11复用为功能11 GPIO功能*/
		GPIOB_PDDR |= (1<<11);										/*PTB11设置为输出*/
		GPIOB_PSOR |= (1<<11);										/*PTB11置1,关闭绿灯*/  	
	
		TPM_init();																/*TPM初始化*/
		while(1)
		{

		} 
}
/********************************************************************/


void TPM0_IRQHandler(void)
{
	if(TPM0_SC & TPM_SC_TOF_MASK)
	{
		TPM0_SC |= TPM_SC_TOF_MASK;
		GPIOB_PTOR |= (1<<11);										/*绿灯翻转*/
	}
}
