#include "keypad.h"
#include "LCD.h"
#include "TIMER1.h"
#include "UART.h"
#include <util/delay.h>
#include "string.h"

#define SIZE_PASSWORD    5
#define WRONG_PASSWORD   0
#define RIGHT_PASSWORD   1
#define CONFIRMED        0XF1
#define NOT_CONFIRMED    0XF2

uint8 array1[SIZE_PASSWORD] = {0};
uint8 array2[SIZE_PASSWORD] = {0};
uint8 array3[SIZE_PASSWORD] = {0};
uint8 error=0;

void step_2();
void send_password(uint8 *password);
void check_password();
void open_door();


uint8 key;
uint8 second;

void TIMER1_counter()
{
	second++;
}
void delay(uint16 sec)
{
	second=0;
	Timer1_ConfigType timer1_config={0, 15624, PRESCALER_64, COMPARE};
	Timer1_init(&timer1_config);
	Timer1_setCallBack(TIMER1_counter);
	while(second!=sec);
}
void enter()
{
	while (key != '='){
		key = KEYPAD_getPressedKey();
	}

}
void step_1()
{

	uint8 i;
	uint8 step1_result;
	clear_screen();
	display_stringRowColumn(0, 0, (uint8 *)"plz enter pass:");
	move_cursor(1, 0);
	// First password entry
	for (i = 0; i < SIZE_PASSWORD; i++) {
		key = KEYPAD_getPressedKey();
		if (key >= 0 && key <= 9) {
			array1[i] = key;
			display_character('*');
		}
	}

	enter();
	send_password(array1);
	clear_screen();
	display_stringRowColumn(0, 0, (uint8 *)"plz re-enter ");
	move_cursor(1, 0);
	// Second password entry
	for (i = 0; i < SIZE_PASSWORD; i++){
		key = KEYPAD_getPressedKey();
		if (key >= 0 && key <= 9) {
			array2[i] = key;
			display_character('*');
		}

	}
	enter();
	send_password(array2);
	step1_result = UART_RecieveByte();
	if (step1_result == WRONG_PASSWORD) {
		clear_screen();
		display_stringRowColumn(0, 0, (uint8 *)"Wrong password");
		step_1();
	} else if (step1_result == RIGHT_PASSWORD) {
		step_2();
	}
}

void step_2() {
	clear_screen();
	display_stringRowColumn(0, 0, (uint8 *)"+:open door");
	display_stringRowColumn(1, 0, (uint8 *)"-:change pass");
	while ((key != '+') && (key != '-')) {
		key = KEYPAD_getPressedKey();
	}
	if (key == '+') {
		UART_SendByte('o');
		check_password();
		open_door();
	}
	else if(key=='-')
	{
		UART_SendByte('p');
		check_password();
		step_1();
	}
}
void check_password()
{
	uint8 i;
	clear_screen();
	display_stringRowColumn(0, 0, (uint8 *)"plz enter pass ");
	display_stringRowColumn(1, 0, (uint8 *)"to confirm:");


	// First password entry
	for (i = 0; i < SIZE_PASSWORD; i++) {
		key = KEYPAD_getPressedKey();
		if (key >= 0 && key <= 9) {
			array3[i] = key;
			display_character('*');
		}

	}
	enter();
	send_password(array3);
	uint8 step2_result;

	step2_result= UART_RecieveByte();
	if(step2_result==CONFIRMED)
	{
		error=0;
	}
	else if(step2_result==NOT_CONFIRMED)
	{
		error++;
		if(error==3)
		{
			clear_screen();
			display_stringRowColumn(0, 0, (uint8 *)"ERROR");
			delay(60);
			error=0;
			step_2();
		}
		check_password();
	}

}
void open_door()
{


	clear_screen();
	display_stringRowColumn(0, 0, (uint8 *)"DOOR IS");
	display_stringRowColumn(1, 0, (uint8 *)"UNLOCKING");
	delay(15);
	clear_screen();
	display_string("HOLD");

	delay(3);
	clear_screen();
	display_stringRowColumn(0, 0, (uint8 *)"DOOR IS");
	display_stringRowColumn(1, 0, (uint8 *)"LOCKING");

	delay(15);
	step_2();

}

void send_password(uint8 *password) {
	for (int i = 0; i < SIZE_PASSWORD; i++) {
		UART_SendByte(password[i]);
	}
}

int main()
{
	LCD_init();
	UART_ConfigType uart_config = {BIT_DATA_8, NONE, STOP_BIT_1, 9600};
	UART_init(&uart_config);
	step_1();
	while (1) {
	}
}
