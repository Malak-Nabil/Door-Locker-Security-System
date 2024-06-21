/*
 * Module: LCD
 *
 * Description:Header file for the LCD driver
 */

#include"common_macros.h"
#include"LCD.h"
#include"gpio.h"
#include <util/delay.h>
#include <stdlib.h>


void LCD_init(void){
	//Configure RS and E pin as output pins
	GPIO_setupPinDirection(RS_PORT_ID,RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(E_PORT_ID ,E_PIN_ID , PIN_OUTPUT);

#if(DATA_BITS_MODE == 8)
	GPIO_setupPortDirection(DATA_PORT_ID, PIN_OUTPUT );
    send_command(TWO_LINES_EIGHT_BITS_MODE);
#elif(DATA_BITS_MODE == 4)
	GPIO_setupPinDirection(DATA_PORT_ID,DB4_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(DATA_PORT_ID,DB5_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(DATA_PORT_ID,DB6_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(DATA_PORT_ID,DB7_PIN_ID , PIN_OUTPUT);

	senddata(TWO_LINES_FOUR_BITS_MODE_INIT1 );
	senddata(TWO_LINES_FOUR_BITS_MODE_INIT2 );

	senddata(TWO_LINES_FOUR_BITS_MODE );
#endif
	send_command(CURSOR_OFF);
	send_command(CLEAR_COMMAND);
}

void send_command(uint8 command){
	GPIO_writePin(RS_PORT_ID,RS_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

#if(DATA_BITS_MODE == 8)
	GPIO_writePort(DATA_PORT_ID ,command);
	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#elif(DATA_BITS_MODE == 4)

	GPIO_writePin(DATA_PORT_ID,DB4_PIN_ID ,GET_BIT(command,4));
	GPIO_writePin(DATA_PORT_ID,DB5_PIN_ID ,GET_BIT(command,5));
	GPIO_writePin(DATA_PORT_ID,DB6_PIN_ID ,GET_BIT(command,6));
	GPIO_writePin(DATA_PORT_ID,DB7_PIN_ID ,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(DATA_PORT_ID,DB4_PIN_ID ,GET_BIT(command,0));
	GPIO_writePin(DATA_PORT_ID,DB5_PIN_ID ,GET_BIT(command,1));
	GPIO_writePin(DATA_PORT_ID,DB6_PIN_ID ,GET_BIT(command,2));
	GPIO_writePin(DATA_PORT_ID,DB7_PIN_ID ,GET_BIT(command,3));


	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif
}

void display_character(uint8 data)
{
	GPIO_writePin(RS_PORT_ID,RS_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

#if(DATA_BITS_MODE == 8)
	GPIO_writePort(DATA_PORT_ID ,data);
	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
#elif(DATA_BITS_MODE == 4)

	GPIO_writePin(DATA_PORT_ID,DB4_PIN_ID ,GET_BIT(data,4));
	GPIO_writePin(DATA_PORT_ID,DB5_PIN_ID ,GET_BIT(data,5));
	GPIO_writePin(DATA_PORT_ID,DB6_PIN_ID ,GET_BIT(data,6));
	GPIO_writePin(DATA_PORT_ID,DB7_PIN_ID ,GET_BIT(data,7));

	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(DATA_PORT_ID,DB4_PIN_ID ,GET_BIT(data,0));
	GPIO_writePin(DATA_PORT_ID,DB5_PIN_ID ,GET_BIT(data,1));
	GPIO_writePin(DATA_PORT_ID,DB6_PIN_ID ,GET_BIT(data,2));
	GPIO_writePin(DATA_PORT_ID,DB7_PIN_ID ,GET_BIT(data,3));


	_delay_ms(1);
	GPIO_writePin(E_PORT_ID,E_PIN_ID,LOGIC_LOW);
	_delay_ms(1);

#endif
}

void display_string(const char *str)
{
	uint8 i=0;
	while(str[i]!='\0'){
		display_character(str[i]);
		i++;
	}
}

void move_cursor(uint8 row,uint8 col)
{
	uint8 memory_address;

	switch(row)
	{
			case 0:
				memory_address=col;
					break;
			case 1:
				memory_address=col+0x40;
					break;
			case 2:
				memory_address=col+0x10;
					break;
			case 3:
				memory_address=col+0x50;
					break;
	}
	send_command(memory_address | SET_CURSOR_LOCATION);
}

void display_stringRowColumn(uint8 row,uint8 col,const uint8 *Str)
{
	move_cursor(row,col); /* go to to the required LCD position */
	display_string(Str); /* display the string */
}

void  integer_To_String(uint8 data)
{
	char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   display_string(buff);	 /* Display the string */
}

void clear_screen(void)
{
	send_command(CLEAR_COMMAND);
}
