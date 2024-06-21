
/*
 * Module: BUZZER
 *
 * Description: Header file for the keypad driver
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PORT PORTB_ID

#define BUZZER_PIN  PIN4_ID

void buzzer_init();
void buzzer_ON();
void buzzer_OFF();

#endif /* BUZZER_H_ */
