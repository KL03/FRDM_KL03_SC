/*
 * File:		main.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "uart.h"

/* Actual system clock frequency */
extern int mcg_clk_hz;
extern int uart0_clk_khz;

uint8 data;

void lpuart0deinit(void)
{
		LPUART0_CTRL = 0;
		LPUART0_BAUD = 0;
}

void lpuart0init(void)
{
		if((MCG_S&MCG_S_CLKST_MASK) == 0)			/*查询系统工作频率*/		
				mcg_clk_hz = MCG_IRC48M;		
		else
		{
				if((MCG_C2&MCG_C2_IRCS_MASK) == 0)					
						mcg_clk_hz = MCG_IRC2M;				
				else				
						mcg_clk_hz = MCG_IRC8M;								
		}
		if(mcg_clk_hz == MCG_IRC48M)
		{
				SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); // select the 48MHz IRC as UART0 clock source
		}
		else
		{
				SIM_SOPT2 |= SIM_SOPT2_UART0SRC(3); // select the 8MHz IRC as UART0 clock source
		}
		uart0_clk_khz = mcg_clk_hz;		 
                
    /* configure LPUART pin mux to PTB1,PTB2 */   // wenxue
		PORTB_PCR1 = PORT_PCR_MUX(0x2); 
		PORTB_PCR2 = PORT_PCR_MUX(0x2);    
		uart0_init (TERM_PORT,uart0_clk_khz,TERMINAL_BAUD);   
}
/********************************************************************/
int main (void)
{  
		lpuart0deinit();			/*sysinit中已经初始化过了lpuart, 反初始化*/
		lpuart0init();				/*初始化lpuart*/
		enable_irq(INT_UART0 - 16);	
		while(1)
		{

		} 
}
/********************************************************************/


void LPUART0_IRQHandler(void)
{
	if(LPUART0_STAT & LPUART_STAT_OR_MASK)
	{
		LPUART0_STAT |= LPUART_STAT_OR_MASK;			/*写1清过载中断*/
	}
	
	if(LPUART0_STAT & LPUART_STAT_RDRF_MASK)		/*读接收数据*/
	{
		data = LPUART0_DATA;											/*回显*/
		out_char(data);
	}
}

