/*
 * FrameParser.c
 *
 * Created: 2021-08-19 13:07:27
 *  Author: Maciej Mikulski
 */ 

 #include "FrameParser.h"

 int8_t parseFrame(RingBuffer_t *buf)
 {
	uint8_t tempBuffer[RINGBUFLEN];
	uint8_t frameIterator = 0, frameID, frameLen;

	int dataLen = bytesInBuffer(buf);

	if(dataLen != 0)
		memcpy(tempBuffer, buf->data, dataLen);
	else
		return -1; //No data in buffer. End function

	if(findFrameStart(tempBuffer, dataLen, 0, &frameIterator) == -1)
		return -2; //No frame found

	if(frameIterator < (dataLen - 1)) //There is still data in buffer
		frameID = tempBuffer[++frameIterator];
	else
		return -3; //Incomplete frame

	frameLen = getFrameLen(frameID);

	if(dataLen - frameIterator >= frameLen - 1)
	{
		
	}
	else
		return -3; //Incomplete frame


	return 0;
 }

int8_t findFrameStart(uint8_t *buf, uint8_t buflen, uint8_t startPos, uint8_t *iter)
{
	for(int i = startPos; i < buflen; i++)
	{
		if(buf[i] == 0xAA)
		{
			*iter = i;
			return 0;
		}
	}
	return -1;
}

uint8_t getFrameLen(uint8_t id)
{
	switch(id)
	{
		case MSG_ACK:
		case INCOMPLETE_FRAME:
		case INVALID_FRAME:
			return sizeof(AckFrame);
		case MSG_DIAGNOSTIC:
			return sizeof(DiagnosticFrame);
		case CMD_STEP:
			return sizeof(StepFrame);
		case CMD_HOME:
			return sizeof(HomeFrame);
		case CMD_SET_POS:
			return sizeof(SetPositionFrame);
		case CMD_SET_NEW_POS_VAL:
			return sizeof(NewPositionValueFrame);
		case CMD_REQUEST_DIAGNOSTICS:
			return sizeof(DiagnosticFrame);
		default:
			return 0;
	}
}