#include "buzzer.h"
#include "DC_MOTOR.h"
#include "TIMER1.h"
#include "UART.h"
#include "EEPROM.h"
#include "I2C.h"

#include <util/delay.h>

#define THIRD_ARRAY      0xFFFF
#define SIZE_PASSWORD    5
#define WRONG_PASSWORD   0
#define RIGHT_PASSWORD   1
#define CONFIRMED        0XF1
#define NOT_CONFIRMED    0XF2

uint8 receivedArray1[SIZE_PASSWORD] = {};
uint8 receivedArray2[SIZE_PASSWORD] = {};
uint8 receivedArray3[SIZE_PASSWORD] = {};
uint8 error=0;
void compareArrays(const uint8 *array1, const uint8 *array2);
void savePasswordToEEPROM(const uint8 *password);
void confirm_password();
void options();
void open_door();
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
void receiveArraysFromUART()
{
	for (int i = 0; i < SIZE_PASSWORD; i++) {
		receivedArray1[i] = UART_RecieveByte();
	}

	for (int i = 0; i < SIZE_PASSWORD; i++) {
		receivedArray2[i] = UART_RecieveByte();
	}
	// Only call compareArrays if the second array was received
	compareArrays(receivedArray1, receivedArray2);
}
void compareArrays(const uint8 *array1, const uint8 *array2)
{
	uint8 i;
	for (i = 0; i < SIZE_PASSWORD; i++) {
		if (array1[i] != array2[i]) {
			UART_SendByte(WRONG_PASSWORD);
			receiveArraysFromUART();
			return;
		}
	}
	UART_SendByte(RIGHT_PASSWORD);
	savePasswordToEEPROM(receivedArray1);
}


void savePasswordToEEPROM(const uint8 *password) {
	for (uint8 i = 0; i < SIZE_PASSWORD; i++) {
		EEPROM_writeByte((0x01+i), password[i]);
	}
	options();
}
void options()
{
	uint8 indicator=UART_RecieveByte();
	if(indicator=='o')
	{
		confirm_password();
		open_door();
	}
	else if(indicator=='p')
	{
		confirm_password();
		receiveArraysFromUART();
	}
}
void open_door()
{


	DcMotor_Rotate(CW,FULL_SPEED);


	delay(15);


	DcMotor_Rotate(OFF,OFF_SPEED);

	delay(15);



	DcMotor_Rotate(ACW,FULL_SPEED);

	delay(15);

	DcMotor_Rotate(OFF,OFF_SPEED);
	options();



}
void confirm_password()
{
	uint8 val = 0;
	uint8 i;
	for (i = 0; i < SIZE_PASSWORD; i++) {
		receivedArray3[i] = UART_RecieveByte();
	}
	for (i= 0; i < SIZE_PASSWORD; i++) {
		EEPROM_readByte((0x01)+i,&val);
		if((receivedArray3[i])!=val)
		{
			UART_SendByte(NOT_CONFIRMED);
			error++;
			if(error==3)
			{

				buzzer_ON();
				delay(60);
				error=0;
				options();
			}
			confirm_password();
		}
	}
	if(i== SIZE_PASSWORD){
		UART_SendByte(CONFIRMED);
		error=0;
	}
}

int main(void) {
	buzzer_init();
	UART_ConfigType config_uart = {BIT_DATA_8, NONE, STOP_BIT_1, 9600};
	UART_init(&config_uart);

	TWI_ConfigType config_twi = {0x01, 400000};
	TWI_init(&config_twi);


	DcMotor_Init();
	receiveArraysFromUART();
	while (1) {

	}
}

