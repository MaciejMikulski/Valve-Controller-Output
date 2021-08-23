#include "uart.h"

void UART_init()
{
	bufferInit(&UARTBuffer);
	UCSRA |= _BV(U2X); 
	UCSRB |= (_BV(RXCIE) | _BV(TXEN) | _BV(RXEN)); //Enable transmitters and receive interrupt
	UCSRC |= ( _BV(UPM1) | _BV(UCSZ1) | _BV(UCSZ0)); //Even parity, 8-bit, tryb asynchroniczny, 1 stop-bit, 
	UBRRL |= 0xCF; //4800 baud
}

void UART_send(unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));
	UDR = data;
}