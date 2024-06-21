
/*
 * Module: PWM
 *
 * Description: Header file for the PWM driver
 */
#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"
/*Definitions*/
#define PWM_PORT PORTB_ID
#define PWM_PIN PIN3_ID

/*function prototype*/
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
