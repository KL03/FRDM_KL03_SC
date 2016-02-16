/*
 * File:		main.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "lptmr.h"


/********************************************************************/
#define MCGIRCLK		0
#define LPO					1
#define ERCLK32K		2
#define OSCERCLK		3
/********************************************************************/


uint8 data;
uint8 flag_500ms;

void SPI0_init(void)
{
    SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;   //open SPI0 gate clock
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;  //open PORTA gate clock
    
    PORTA_PCR9 |= PORT_PCR_MUX(3);      //set PTA9 as the SPI0_SCK
    PORTA_PCR8 |= PORT_PCR_MUX(3);      //set PTA8 as the SPI0_MOSI
    PORTA_PCR7 |= PORT_PCR_MUX(2);      //set PTA7 as the SPI0_MISO
    
    
    PORTA_PCR6 |= PORT_PCR_MUX(1);      //set PTA6 as GPIO
    GPIOA_PDDR |= (1u<<6);
    GPIOA_PDOR &= ~(1u<<6);
    SPI0_C1 = 0x04;
    
    SPI0_C1 |= SPI_C1_MSTR_MASK         //select SPI0 master mode
            |  SPI_C1_SPE_MASK          //enable SPI0
            |  SPI_C1_SSOE_MASK        // auto slave select
            |  SPI_C1_CPHA_MASK;
            
    //SPI0_C1 |= SPI_C1_SPTIE_MASK;       //enable SPI0 send int        
            
    SPI0_C2 = 0x00;
    
    SPI0_BR = 0x00;
    SPI0_BR |= SPI_BR_SPPR(0) | SPI_BR_SPR(0);  //band = 12m
    
    SPI0_S = 0x00;
    
    //enable_irq(SPI0_irq_no);   
}

/********************************************************************/
int main (void)
{
		lptmr_init(500,LPO);												/*初始化LPTMR, 使用LPO 1kHz  定时周期500ms*/
		SPI0_init();																/*初始化SPI模块*/
		while(1)
		{
			if(flag_500ms == 1)
			{
				while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);			/*发送缓冲区为空时写SPI0_D发送数据*/
				SPI0_D = 0x0A;																							/*输出跟输入串起来测试*/
				
				while((SPI0_S & SPI_S_SPRF_MASK) != SPI_S_SPRF_MASK);
				data = SPI0_D;

				flag_500ms = 0;
			}
	
		} 
}
/********************************************************************/

void LPTMR0_IRQHandler(void)
{
	//write 1 to TCF to clear the LPT timer compare flag
	LPTMR_CSR |=  LPTMR_CSR_TCF_MASK;
	flag_500ms = 1;
}

