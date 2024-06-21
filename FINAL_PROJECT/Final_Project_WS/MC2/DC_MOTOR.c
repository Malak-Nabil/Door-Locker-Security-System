
/*
 * Module: DC_MOTOR
 *
 * Description: source file for the DC_MOTOR driver
 */

#include"DC_MOTOR.h"
#include"gpio.h"
#include"PWM.h"

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_PORT_ID, DC_PIN1_ID , PIN_OUTPUT); /* PB0 Output Pin */
	GPIO_setupPinDirection(DC_PORT_ID, DC_PIN2_ID , PIN_OUTPUT); /* PB1 Output Pin */

	/*Stop at the DC-Motor at the beginning */
	DcMotor_Rotate(OFF,OFF_SPEED);
}

void DcMotor_Rotate(DCMotor_State state,uint8 speed)
{
	uint8 duty_cycle=speed*(255/100);
	switch(state)
	{
	case OFF:
		/* Stop the motor */
		GPIO_writePin(DC_PORT_ID, DC_PIN1_ID, LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID, DC_PIN2_ID, LOGIC_LOW);
		PWM_Timer0_Start(duty_cycle);
		break;
	case CW:
		/* Rotates the motor CW */
		GPIO_writePin(DC_PORT_ID, DC_PIN1_ID, LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID, DC_PIN2_ID, LOGIC_HIGH);
		PWM_Timer0_Start(duty_cycle);
		break;
	case ACW:
		/* Rotates the motor A-CW */
		GPIO_writePin(DC_PORT_ID, DC_PIN1_ID, LOGIC_HIGH);
		GPIO_writePin(DC_PORT_ID, DC_PIN2_ID, LOGIC_LOW);
		PWM_Timer0_Start(duty_cycle);
		break;
	default:
		/* Do Nothing */
		break;
	}

}
