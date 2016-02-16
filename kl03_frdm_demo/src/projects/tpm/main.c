/*
 * File:		main.c
 * Purpose:		Main process
 *
 */

#include "common.h"

void TPM_init(void)
{
		SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);	  																/*48MHz ��ΪTPMʱ��Դ*/
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK| SIM_SCGC6_TPM1_MASK;   						/*��TPMʱ����*/

		TPM0_CNT = 0;
		TPM0_MOD = 48000;
	
		TPM0_SC |= TPM_SC_PS(7);																						/*���÷�Ƶϵ�� 128��Ƶ*/
		TPM0_SC |= TPM_SC_TOIE_MASK|TPM_SC_CMOD(1);													/*ʹ���ж�, ѡ��ģʽ1, ÿ��������ʱ�Ӽ�1*/
		
		TPM0_C0SC = TPM_CnSC_MSB_MASK| TPM_CnSC_ELSB_MASK;									/*���ض���ģʽ*/
		TPM0_C0V = 0;
		
		enable_irq(INT_TPM0 - 16);																					/*ʹ���ж�*/
}
/********************************************************************/
int main (void)
{  
	
		SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK				/*��PORTA PORTBʱ����*/
							| SIM_SCGC5_PORTB_MASK;
					
		PORTB_PCR11 |= PORT_PCR_MUX(1);						/*PTB11����Ϊ����11 GPIO����*/
		GPIOB_PDDR |= (1<<11);										/*PTB11����Ϊ���*/
		GPIOB_PSOR |= (1<<11);										/*PTB11��1,�ر��̵�*/  	
	
		TPM_init();																/*TPM��ʼ��*/
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
		GPIOB_PTOR |= (1<<11);										/*�̵Ʒ�ת*/
	}
}
