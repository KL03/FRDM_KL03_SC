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
	
	for(i=0;i<10;i++)																												/*KL03Z32 扇区大小为1KB, 擦除10个扇区*/										
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
	for(i=0;i<64;i++)																												/*附初值*/
	{
			Databuffer[i] = i;
	}
	temp = Flash_ByteProgram(0x2800,(uint32_t*)Databuffer,64);							/*从0x2800开始写入64个字节*/
	if(temp == 0)																														/*返回值为0说明写入成功,开始校验*/
	{
		for(i=0;i<64;i++)
		{
			Readbuffer[i] = ((uint8_t*)0x2800)[i];															/*校验*/
			if(Readbuffer[i] != Databuffer[i])
			{
				printf("write flash error,Databuffer[%d] = %d, Readbuffer[%d] = %d\r\n",i,Databuffer[i],i,Readbuffer[i]);
				while(1);
			}
		}
		printf("write flash ok\r\n");
	}
	else																																		/*写入错误,则打印返回值*/
		printf("temp = %d", temp);
	while(1)
	{
		u = in_char();
		out_char(u);
	} 
}
/********************************************************************/
