/*
 * File:		platinum.c
 * Purpose:		Main process
 *
 */

#include "common.h"

uint16_t capture = 0;
void TPM_capture_init(void)
{
		SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);	  																/*48MHz 作为TPM时钟源*/
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK| SIM_SCGC6_TPM1_MASK;   						/*打开TPM时钟门*/
	
		TPM0_CNT = 0;
		TPM0_MOD = 0xFFFF;
		TPM0_SC |= TPM_SC_PS(0);																						/*设置分频系数 128分频*/
		TPM0_SC |= TPM_SC_CMOD(1);																					/*选择模式1, 每个计数器时钟加1*/
	
		TPM0_SC &= ~TPM_SC_CPWMS_MASK;
		TPM0_C0SC &= ~(TPM_CnSC_MSB_MASK | TPM_CnSC_MSB_MASK);							/*输入捕捉模式, CPWMS = 0, MSnB:MSnA = 0:0, ELSnB:ELSnA != 0:0*/
		TPM0_C0SC &= ~TPM_CnSC_ELSA_MASK;
		TPM0_C0SC |= TPM_CnSC_ELSB_MASK;
	
		TPM0_C0SC |= TPM_CnSC_CHIE_MASK;																		/*打开CH0通道中断*/
		enable_irq(INT_TPM0 - 16);																					/*使能中断*/
}

/********************************************************************/
int main (void)
{
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK				/*打开PORTA PORTB时钟门*/
							 | SIM_SCGC5_PORTB_MASK;
	
		PORTA_PCR6 |= PORT_PCR_MUX(2);					/*PTA6复用为TPM_CH0功能*/
		TPM_capture_init();
		while(1)
		{
			if(capture != 0)
			{
					printf("capture = %d", capture);	
					capture = 0;
			}			
		} 
}

void TPM0_IRQHandler(void)
{
		if(TPM0_C0SC & TPM_CnSC_CHF_MASK)
		{
			TPM0_C0SC |= TPM_CnSC_CHF_MASK;																			/*清中断标志*/
			capture = TPM0_C0V;																									/*读取捕获值*/
		}
}
/********************************************************************/
