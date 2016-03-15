/*
 * File:		platinum.c
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
		TPM0_SC |= TPM_SC_CMOD(1);																					/*选择模式1, 每个计数器时钟加1*/
		
		TPM0_C0SC = TPM_CnSC_MSB_MASK| TPM_CnSC_ELSB_MASK;									/*边沿对齐模式*/
		TPM0_C0V = 24000;																										/*CH0,PWM占空比 = TPM0_C0V / TPM0_MOD = 50%*/
		
		enable_irq(INT_TPM0 - 16);																					/*使能中断*/
}
/********************************************************************/
int main (void)
{
		char ch;

		
		PORTB_PCR11 |= PORT_PCR_MUX(2);																			/*PTB11配置为TPM_CH0输出*/
		TPM_init();
		while(1)
		{
			ch = in_char();
			out_char(ch);
		} 
}
/********************************************************************/
