/*
 * File:		platinum.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "flash_FTFL.h"

uint32_t add = 0x2800;
uint8_t Databuffer[64];
uint8_t Readbuffer[64];

/********************************************************************/
int main (void)
{
	char u,i;
	uint8_t temp = 1;
	DisableInterrupts;
	Flash_Init(0);
	
	for(i=0;i<10;i++)																												/*KL03Z32 ������СΪ1KB, ����10������*/										
	{
		temp = Flash_SectorErase(add);
		if(temp != 0)
		{
				printf("erase sector error,add = 0x%x\r\n",add);
				while(1);
		}
		printf("erase sector ok,add = 0x%x\r\n",add);
		add += 1024;
	}
	for(i=0;i<64;i++)																												/*����ֵ*/
	{
			Databuffer[i] = i;
	}
	temp = Flash_ByteProgram(0x2800,(uint32_t*)Databuffer,64);							/*��0x2800��ʼд��64���ֽ�*/
	if(temp == 0)																														/*����ֵΪ0˵��д��ɹ�,��ʼУ��*/
	{
		for(i=0;i<64;i++)
		{
			Readbuffer[i] = ((uint8_t*)0x2800)[i];															/*У��*/
			if(Readbuffer[i] != Databuffer[i])
			{
				printf("write flash error,Databuffer[%d] = %d, Readbuffer[%d] = %d\r\n",i,Databuffer[i],i,Readbuffer[i]);
				while(1);
			}
		}
		printf("write flash ok\r\n");
	}
	else																																		/*д�����,���ӡ����ֵ*/
		printf("temp = %d", temp);
	while(1)
	{
		u = in_char();
		out_char(u);
	} 
}
/********************************************************************/
