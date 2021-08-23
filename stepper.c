/*
 * stepper.c
 *
 * Created: 2020-07-01 16:27:20
 *  Author: User
 * 
 */
  #define F_CPU 8000000UL

 #include <avr/io.h>
 #include <util/delay.h>
 #include "stepper.h"

 void stepperInit()
 {
	DIR_DDR |= _BV(DIR_PIN);
	STEP_DDR |= _BV(STEP_PIN);

	DIR_PORT &= ~_BV(DIR_PIN);
	STEP_PORT &= ~_BV(STEP_PIN);
 }

void step(uint8_t stepNum,	DIRECTION dir)
{
	if(dir == LEFT)
		DIR_PORT |= _BV(DIR_PIN);
	else
		DIR_PORT &= ~_BV(DIR_PIN);

	for(int i = 0; i < stepNum; i++)
	{
		STEP_PORT |= _BV(STEP_PIN);
		_delay_ms(STEP_DELAY_TIME);
		STEP_PORT &= ~_BV(STEP_PIN);
		_delay_ms(STEP_DELAY_TIME);
	}
}