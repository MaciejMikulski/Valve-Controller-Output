/*
 * RingBuffer.h
 *
 * Ring buffer for use in UART communication
 *
 * Created: 2021-08-18 15:01:45
 * Author: Maciej Mikulski
 */ 

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

#define RINGBUFLEN 20

typedef struct
{
	uint8_t data[RINGBUFLEN];
	uint8_t writeHead;
	uint8_t readHead;
}RingBuffer_t;

void bufferInit(RingBuffer_t *buf);
void put(RingBuffer_t *buf, uint8_t *data);
void bufferWrite(RingBuffer_t *buf, uint8_t *data, uint8_t len);
int8_t get(RingBuffer_t *buf, uint8_t *data);
int8_t bufferRead(RingBuffer_t *buf, uint8_t *data, uint8_t len);
uint8_t isEmpty(RingBuffer_t *buf);
uint8_t isFull(RingBuffer_t *buf);
void bufferReset(RingBuffer_t *buf);
uint8_t bytesInBuffer(RingBuffer_t *buf);

#endif /* RINGBUFFER_H_ */