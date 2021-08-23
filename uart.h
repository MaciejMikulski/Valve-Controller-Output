#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "RingBuffer.h"

RingBuffer_t UARTBuffer;
uint8_t flag;

void UART_init();
void UART_send(unsigned char data);

#endif /* UART_H_ */