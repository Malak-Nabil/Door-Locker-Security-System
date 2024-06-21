
/*
 * Module: UART
 *
 * Description: Source file for the UART driver
 */
#include"UART.h"
#include <avr/io.h>
#include"gpio.h"
#include"common_macros.h"
void UART_init(const UART_ConfigType *Config_Ptr)
{

	uint16 UBRR_VALUE = 0;

	UCSRA=(1<<U2X); //double transmission speed
	/*enable receiver and transmitter*/
	UCSRB=(1<<RXEN) | (1<<TXEN);

	UCSRC=(UCSRC & 0XC1) | ((Config_Ptr->parity)<<4) | ((Config_Ptr->stop_bit)<<3) | ((Config_Ptr->bit_data)<<1) | (1<<URSEL);

	UCSRB =(UCSRB & 0XFB) | ((Config_Ptr->bit_data));

	UBRR_VALUE= (uint16)(((F_CPU / ( (Config_Ptr->baud_rate)* 8UL))) - 1);


	UBRRH=(UBRR_VALUE>>8);
	UBRRL=UBRR_VALUE;
}

void UART_SendByte(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

   UDR=data;

}

uint8 UART_RecieveByte()
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}


   return UDR;

}
void UART_SendString(uint8 *str)
{
	uint8 i=0;
	while(str[i]!='\0')
	{
		 UART_SendByte(str[i]);
		 i++;
	}
}
void UART_RecieveString(uint8 *str)
{
	uint8 i=0;
	str[i] = UART_RecieveByte();
	while(str[i]!='#')
	{
		 i++;
		 str[i]=UART_RecieveByte();

	}
	str[i]='\0';
}
