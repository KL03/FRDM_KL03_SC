/*
 * File:		gpio.c
 * Purpose:		Main process
 *
 */

#include "common.h"

int main (void)
{
	
/******************************************/
//清RTC_TSR的TIF位，若不清除会导致无法正确进入低功耗模式
	uint8 tmp;
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;		
	tmp = RTC_TSR;
	RTC_TSR = tmp;
	SIM_SCGC6 &= ~SIM_SCGC6_RTC_MASK;	
/******************************************/	
	
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK				/*打开PORTA PORTB时钟门*/
						| SIM_SCGC5_PORTB_MASK;
			  
	PORTB_PCR10 |= PORT_PCR_MUX(1);						/*PORTB10复用为功能1 GPIO功能*/
	GPIOB_PDDR |= (1<<10);										/*PORTB10设置为输出*/
	GPIOB_PSOR |= (1<<10);										/*PORTB10置1，关闭红灯，GPIOB_PSOR用于将相应位置1*/
	
//	GPIOB_PCOR |= (1<<10);									/*GPIOB_PCOR用于将相应位清0*/
//	GPIOB_PDOR |= (1<<10);									/*GPIOB_PDOR用于设置相应位的输出电平*/	
//	GPIOB_PTOR |= (1<<10);									/*置位GPIOB_PTOR翻转相应位*/

	PORTB_PCR0 |= PORT_PCR_MUX(1);						/*PORTB0复用为功能1 GPIO功能*/
	GPIOB_PDDR &= ~(1<<0);										/*PORTB0设置为输入*/
	
	while(1)
	{
		uint8 u;
		u = (GPIOB_PDIR&(1<<0)) >> 0;					/*读PTB0电平*/
		if(u == 0)														/*有键按下时，灯亮*/
		{
			GPIOB_PDOR &= ~(1<<10);			
		}
		else
		{
			GPIOB_PDOR |= (1<<10);
		}
	} 	
}


