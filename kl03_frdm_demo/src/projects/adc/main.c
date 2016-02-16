/*
 * File:		main.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "adc.h"

#define Temp_Sensor	0x1A

/********************************************************************/
int main (void)
{       
		uint16 ADCresult;
		InitADC();
		while(1)
		{
				TriggerADC(Temp_Sensor);									/*дͨ���Ŵ���ת��*/
				ADCresult	= ReadADCPoll();								/*�ȴ�ת����ɲ���ȡת�����*/
				printf("ADCresult = %d\r\n", ADCresult);
		} 
}
/********************************************************************/
