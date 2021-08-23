/*
 * Sterownik_Zaworu_Opryskiwacz_Output.c
 *
 * Created: 2020-08-11 10:38:34
 * Author : User
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "stepper.h"

ISR(USART_RX_vect)
{
	uint8_t tmp = UDR;
	bufferWrite(&UARTBuffer, &tmp, 1);
}

int main(void)
{
	uint8_t data = 0;
	stepperInit();
	UART_init();
	sei();
	while(1)
	{
		if(!isEmpty(&UARTBuffer))
		{
			if(bufferRead(&UARTBuffer, &data, 1) != -1)
			{
				step(data, LEFT);
				UART_send(data);
			}
		}
	}
}
