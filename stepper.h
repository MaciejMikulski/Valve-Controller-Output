/*
 * stepper.h
 *
 * Created: 2020-07-01 16:27:30
 *  Author: User
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_

#define STEP_DELAY_TIME 10

#define DIR_PORT	PORTB
#define DIR_DDR		DDRB
#define DIR_PIN		PB0
#define STEP_PORT	PORTB
#define STEP_DDR	DDRB
#define STEP_PIN	PB1

typedef enum
{
	LEFT,
	RIGHT
}DIRECTION;

void stepperInit();
void step(uint8_t stepNum, DIRECTION dir);

#endif /* SERVO_H_ */