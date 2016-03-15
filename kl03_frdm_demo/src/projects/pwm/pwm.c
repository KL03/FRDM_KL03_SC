/*
 * File:		platinum.c
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
		TPM0_SC |= TPM_SC_CMOD(1);																					/*ѡ��ģʽ1, ÿ��������ʱ�Ӽ�1*/
		
		TPM0_C0SC = TPM_CnSC_MSB_MASK| TPM_CnSC_ELSB_MASK;									/*���ض���ģʽ*/
		TPM0_C0V = 24000;																										/*CH0,PWMռ�ձ� = TPM0_C0V / TPM0_MOD = 50%*/
		
		enable_irq(INT_TPM0 - 16);																					/*ʹ���ж�*/
}
/********************************************************************/
int main (void)
{
		char ch;

		
		PORTB_PCR11 |= PORT_PCR_MUX(2);																			/*PTB11����ΪTPM_CH0���*/
		TPM_init();
		while(1)
		{
			ch = in_char();
			out_char(ch);
		} 
}
/********************************************************************/
