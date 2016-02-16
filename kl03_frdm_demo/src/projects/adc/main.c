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
				TriggerADC(Temp_Sensor);									/*写通道号触发转换*/
				ADCresult	= ReadADCPoll();								/*等待转换完成并读取转换结果*/
				printf("ADCresult = %d\r\n", ADCresult);
		} 
}
/********************************************************************/
