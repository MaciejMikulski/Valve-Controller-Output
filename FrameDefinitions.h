/*
 * FrameDefinitions.hpp
 *
 *  Created on: 08.09.2020
 *      Author: Konrad
 *
 * Modified on: 16.02.2021
 *          By: Kuba and Lukasz
 *
 * Modified on: 12.08.2021
 *          By: Maciej
 */

#ifndef INC_FRAMEDEFINITIONS_HPP_
#define INC_FRAMEDEFINITIONS_HPP_

#include <stdint.h>

// Frame identifiers
typedef enum
    {
        // 0xF0 - 0xFD - frames sent from the motor control board
    MSG_ACK = 0xF1, // Acknowledge received and parsed message
    MSG_DIAGNOSTIC = 0xF2, // Diagnostic frame (PB housekeeping data)

    // 0x00 - 0x0F - frames sent to the motor control board
    CMD_STEP = 0x01, // Step motor by desired number of steps in indicated direction
    CMD_HOME = 0x02, // Set motor to home position
    CMD_SET_POS = 0x03, // Go to position no. x
	CMD_SET_NEW_POS_VAL = 0x04, // Set new step value to specified position (saved in EEPROM)
    CMD_REQUEST_DIAGNOSTICS = 0x05, // Request diagnostic frame

    // 0xFE - incomplete frame
    INCOMPLETE_FRAME = 0xFE,
    // 0xFF - invalid frame
    INVALID_FRAME = 0xFF
}FrameType;

// Frame start byte
static const uint8_t FRAME_START_BYTE = 0xAA;

// Erase CMD password bytes
static const uint8_t ERASE_CMD_FIRST_BYTE = 0x1C;
static const uint8_t ERASE_CMD_SECOND_BYTE = 0xDB;

// Size of the CRC
static const uint32_t CRC_SIZE = 2;

/*
 * Frame header
 * Len: 2 bytes
 */
typedef struct
{
    uint8_t startByte;
    FrameType frameId;
}__attribute__((packed, aligned(1)))FrameHeader;

/*
 * MSG_ACK
 * Len: 5 bytes
 */
typedef struct
{
    FrameHeader header;
    uint8_t receivedId;
    uint16_t crc;
}__attribute__((packed, aligned(1)))AckFrame;

/*
 * CMD_STEP
 * Len: 6 bytes
 */
typedef struct
{
    FrameHeader header;
    uint16_t numberOfSteps;
    uint16_t crc;
}__attribute__((packed, aligned(1)))StepFrame;

/*
 * CMD_HOME
 * Len: 4 bytes
 */
typedef struct 
{
	FrameHeader header;
	uint16_t crc;
}__attribute__((packed, aligned(1)))HomeFrame;

/*
 * CMD_SET_POS
 * Len: 5 bytes
 */
typedef struct
{
	FrameHeader header;
	uint8_t position;
	uint16_t crc;
}__attribute__((packed, aligned(1)))SetPositionFrame;

/*
 * CMD_SET_NEW_POS_VAL
 * Len: 7 bytes
 */
 typedef struct
 {
	FrameHeader header;
	uint8_t position;
	uint16_t newStepCountValue;
	uint16_t crc;
 }__attribute__((packed, aligned(1)))NewPositionValueFrame;

/*
 * DiagnosticPayload
 * Len: 11 bytes 
 */
typedef struct
{
	uint8_t currenPosition; //1 - 5
	uint16_t positionNSteps[5]; //Contains step values for all 5 positions	
}__attribute__((packed, aligned(1)))DiagnosticPayload;


/*
 * MSG_DIAGNOSTIC
 * Len: 15 bytes
 */
typedef struct
{
    FrameHeader header;
    uint8_t currentMotorPosition;
    uint16_t crc;
}__attribute__((packed, aligned(1)))DiagnosticFrame;

/*
 * CMD_REQUESTDIAGNOSTICS
 * Len: 5 bytes
 */
typedef struct
{
    FrameHeader header;
	uint8_t payload;
    uint16_t crc;
}__attribute__((packed, aligned(1)))RequestDiagnosticsFrame;

#endif /* FRAMEDEFINITIONS_HPP_ */

