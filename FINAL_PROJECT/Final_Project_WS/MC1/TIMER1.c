
/*
 * Module: TIMER1
 *
 * Description: Source file for the TIMER1 driver
 */

#include"TIMER1.h"
#include <avr/io.h>
#include <avr/interrupt.h>


static volatile void (*g_callBackPtr)(void) = NULL_PTR;
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{

	// Initialize the Timer counter to zero
		TCNT1 = Config_Ptr-> initial_value;

	    // Configure Timer Control Register A (TCCR1A) to zeros (no effect on timer operation)
		TCCR1A = 0;

		 // Prescaler and mode
		TCCR1B = (TCCR1B & 0XE0) | ( Config_Ptr-> prescaler) | (( Config_Ptr-> mode)<<3);

		switch(Config_Ptr-> mode)
		{
		case NORMAL:
			TIMSK |= (1 << TOIE1);
			break;

		case COMPARE:

			TIMSK |= (1 << OCIE1A);
			// Set the Output Compare Register A (OCR1A)
			// This value determines the timer's counting range, which is set to 1 second
			OCR1A =Config_Ptr-> compare_value ;
			break;
		}


	    // Enable global interrupts by setting the I-bit in the Status Register (SREG)
		sei();


}
void Timer1_deInit()
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;

	TIMSK &= ~(1<<TOIE1);
	TIMSK &= ~(1<<OCIE1A);
}
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
