/*
 * RingBuffer.c
 *
 * Created: 2021-08-18 15:02:01
 *  Author: Maciej Mikulski
 */ 
 #include "RingBuffer.h"


void bufferInit(RingBuffer_t *buf)
{
	buf->readHead = 0;
	buf->writeHead = 0;
}

void put(RingBuffer_t *buf, uint8_t *data)
{
	buf->data[buf->writeHead] = *data;
	buf->writeHead = (buf->writeHead + 1) % RINGBUFLEN;
	
	if(buf->writeHead == buf->readHead)
	{
		buf->readHead = (buf->readHead + 1) % RINGBUFLEN;
	}
}

void bufferWrite(RingBuffer_t *buf, uint8_t *data, uint8_t len)
{
	for(int i = 0; i < len; i++)
	{
		put(buf, data + i);
	}
}

int8_t get(RingBuffer_t *buf, uint8_t *data)
{
	if(isEmpty(buf))
	{
		return -1;
	}

	*data = buf->data[buf->readHead];
	buf->readHead = (buf->readHead + 1) % RINGBUFLEN;
	return 0;
 }

int8_t bufferRead(RingBuffer_t *buf, uint8_t *data, uint8_t len)
{
	if(buf->writeHead == buf->readHead)
	{
		return -1;
	}
	else
	{
		*data = buf->data[buf->readHead];
		if(buf->readHead == RINGBUFLEN)
		{
			buf->readHead = 0;
		}
		else
		{
			buf->readHead++;
		}
		return 0;
	}
}	

uint8_t isEmpty(RingBuffer_t *buf)
{
	return buf->writeHead == buf->readHead;
}

uint8_t isFull(RingBuffer_t *buf)
{
	return ((buf->writeHead + 1) % RINGBUFLEN) == buf->readHead;
}

void bufferReset(RingBuffer_t *buf)
{
	buf->writeHead = buf->readHead;
}

uint8_t bytesInBuffer(RingBuffer_t *buf) //Return number of bytes currently available in buffer
{
	if(buf->writeHead > buf->readHead)
	{
		return buf->writeHead-buf->readHead;
	}
	else if(buf->readHead > buf->writeHead)
	{
		return RINGBUFLEN - buf->readHead + buf->writeHead;
	}
	else
	{
		return 0;
	}
}
