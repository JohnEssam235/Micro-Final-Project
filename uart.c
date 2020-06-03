

#include "uart.h"


/*******************************************************************************
                   Functions Definitions                                  
 *******************************************************************************/
void UART_init(void)
{
	SYSCTL_RCGCGPIO_R |= 0X0001; // put clock on portA
	SYSCTL_RCGCUART_R |= 0x0001; // h43'l UART0
	UART0_CTL_R &= ~(0X0001); //disable the uart0 at first..
	// using baud rate = 115200
	UART0_IBRD_R = 43;
	UART0_FBRD_R=26;
	// fixing the stop bits and data bits ana enabling the FIFO
	UART0_LCRH_R = 0X70;
	// ENABLE UART0..
	UART0_CTL_R = 0X301;
	// configure UART PINS......make pins act as "UART" not "GPIO"...
	GPIO_PORTA_PCTL_R = 0X03;
	GPIO_PORTA_AFSEL_R |= 0x03;
	GPIO_PORTA_DEN_R |= 0X03;
	
}
	
void UART_sendByte(uint8_t data)
{
	
	while(BIT_IS_SET(UART0_FR_R,5)){}
 
	UART0_DR_R = data;
	
}

uint8_t UART_recieveByte(void)
{
	
	while(BIT_IS_SET(UART0_FR_R,4));
		
    return (uint8_t)UART0_DR_R;		
}




