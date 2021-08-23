/*
 * FrameParser.h
 *
 * Created: 2021-08-19 13:07:40
 *  Author: Maciej Mikulski
 */ 


#ifndef FRAMEPARSER_H_
#define FRAMEPARSER_H_

#include <stdbool.h>
#include <string.h>

#include "FrameDefinitions.h"
#include "RingBuffer.h"
#include "uart.h"
#include "stepper.h"

/*******************************************************************
* NAME :            uint8_t parseFrame(RingBuffer_t *buf)
*
* DESCRIPTION :     Find frame in buffer, parse it and perform actions specific to 
*
* INPUTS :
*       PARAMETERS:
*           RingBuffer_t	*buf            Pointer to buffer structure, containing incoming data
*       GLOBALS :
*           RINGBUFLEN						Defines length of UART data buffer (RingBuffer.h)
* OUTPUTS :
*		RETURN:
*			Type:			int8_t			Status code
*			Values:			-1				No data in buffer
*							-2				No frames found in buffer
*/
int8_t parseFrame(RingBuffer_t *buf);


/*******************************************************************
* NAME :            int8_t findFrameStart(uint8_t *buf, uint8_t buflen, uint8_t *iter)
*
* DESCRIPTION :     Find starting location of first frame in buffer
*
* INPUTS :
*       PARAMETERS:
*           uint8_t			*buf			Pointer to buffer (uint8_t array) to be scanned
*			uint8_t			buflen			Length of buffer in bytes
*			uint8_t			startPos		Starting position for searching
* OUTPUTS :
*		PARAMETERS:
*			uint8_t			*iter			Place in buffer in which first frame starts
*		RETURN:
*			Type:			int8_t			Exit status
*			Values:			0				Frame found
*							-1				Frame not found
* NOTES :
*		If no frame is found the value in memory position pointed to by iter is not changed.
*/
int8_t findFrameStart(uint8_t *buf, uint8_t buflen, uint8_t startPos, uint8_t *iter);

/*******************************************************************
* NAME :            uint8_t getFrameLen(uint8_t id)
*
* DESCRIPTION :     Get length of given frame in bytes
*
* INPUTS :
*       PARAMETERS:
*           uint8_t			id				ID of checked frame
* OUTPUTS :
*		RETURN:
*			Type:			uint8_t			Frame length
*			Values:			1-255		Frame length
*							0				Invalid ID
*/
uint8_t getFrameLen(uint8_t id);

typedef enum
{
	NOTFOUND,
	HEADER,
	ID,
	LENGTH,
	PAYLOAD,
	CRC
}State_t;


#endif /* FRAMEPARSER_H_ */