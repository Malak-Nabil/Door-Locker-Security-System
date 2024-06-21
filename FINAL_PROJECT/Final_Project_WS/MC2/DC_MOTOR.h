
/*
 * Module: DC_MOTOR
 *
 * Description: header file for the DC_MOTOR driver
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"

typedef enum
{
	OFF,CW,ACW
}DCMotor_State;

/*definitions*/
#define DC_PORT_ID  PORTB_ID
#define DC_PIN1_ID  PIN0_ID
#define DC_PIN2_ID  PIN1_ID

#define FULL_SPEED  100
#define OFF_SPEED   0


/*function prototype*/
void DcMotor_Init(void);
void DcMotor_Rotate(DCMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
