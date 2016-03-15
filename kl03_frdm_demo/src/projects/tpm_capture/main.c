/*
 * File:		platinum.c
 * Purpose:		Main process
 *
 */

#include "common.h"

uint16_t capture = 0;
void TPM_capture_init(void)
{
		SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);	  																/*48MHz ��ΪTPMʱ��Դ*/
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK| SIM_SCGC6_TPM1_MASK;   						/*��TPMʱ����*/
	
		TPM0_CNT = 0;
		TPM0_MOD = 0xFFFF;
		TPM0_SC |= TPM_SC_PS(0);																						/*���÷�Ƶϵ�� 128��Ƶ*/
		TPM0_SC |= TPM_SC_CMOD(1);																					/*ѡ��ģʽ1, ÿ��������ʱ�Ӽ�1*/
	
		TPM0_SC &= ~TPM_SC_CPWMS_MASK;
		TPM0_C0SC &= ~(TPM_CnSC_MSB_MASK | TPM_CnSC_MSB_MASK);							/*���벶׽ģʽ, CPWMS = 0, MSnB:MSnA = 0:0, ELSnB:ELSnA != 0:0*/
		TPM0_C0SC &= ~TPM_CnSC_ELSA_MASK;
		TPM0_C0SC |= TPM_CnSC_ELSB_MASK;
	
		TPM0_C0SC |= TPM_CnSC_CHIE_MASK;																		/*��CH0ͨ���ж�*/
		enable_irq(INT_TPM0 - 16);																					/*ʹ���ж�*/
}

/********************************************************************/
int main (void)
{
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK				/*��PORTA PORTBʱ����*/
							 | SIM_SCGC5_PORTB_MASK;
	
		PORTA_PCR6 |= PORT_PCR_MUX(2);					/*PTA6����ΪTPM_CH0����*/
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
			TPM0_C0SC |= TPM_CnSC_CHF_MASK;																			/*���жϱ�־*/
			capture = TPM0_C0V;																									/*��ȡ����ֵ*/
		}
}
/********************************************************************/
