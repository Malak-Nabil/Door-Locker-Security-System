
/*
 * Module: BUZZER
 *
 * Description: Header file for the keypad driver
 */

#include"buzzer.h"
#include"gpio.h"

void buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN,LOGIC_LOW);
}

void buzzer_ON()
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN,LOGIC_HIGH);
}

void buzzer_OFF()
{
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}
