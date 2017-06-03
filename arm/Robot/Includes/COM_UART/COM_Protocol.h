/*
 * Title  : COM_Protocol.h
 * Author : liminkmf@mail.ustc.edu.cn
 * Version: V2.0 2016-11-09
 * Description:
 *     This is the COM UART communication protocol(Version 2.0) definition
 * file.
 *
 * Copyright (c) limin @ ISPC-USTC.
 *
**/

/************************************************************************/
// Protocol Definition Part I: STM to ARM frame definition
// Total Bytes: 30Bytes(27B used, 3B unused)

// Protocol Definition Part II: ARM to STM frame definition
// Total Bytes: 16Bytes(14B used, 2B unused)

// Warning: if you want to know the definition details, please refer to the
// Document in the directory ../../Document

/************************************************************************/


#ifndef COM_UART_PROTOCOLS_H_
#define COM_UART_PROTOCOLS_H_

// Frame Head Definition
#define Frame_Head_STM2ARM  0x11  // Frame from STM32 to ARM through UART
#define Frame_Head_ARM2STM  0x42  // Frame from ARM to STM32 through UART
//#define Frame_Head_ARM2PC   0x64  // Frame from ARM to PC through WiFi
//#define Frame_Head_PC2ARM   0x98  // Frame from PC to ARM through WiFi

// System Command Definitions
#define CMD_SYS_Init    0x01  // System Initialization
#define CMD_SYS_Sleep   0x02  // System Sleep
#define CMD_SYS_Shut    0x04  // System Shutdown

// Motion Command Definitions
#define CMD_MOVE_Stop            0xFF
#define CMD_MOVE_Forward         0x80  // Forward With Motion Parameters
#define CMD_MOVE_Forward_Free    0x81  // Forward Without Motion Parameters
#define CMD_MOVE_Backward        0x40  // Backward With Motion Parameters
#define CMD_MOVE_Backward_Free   0x41  // Backward Without Motion Parameters
#define CMD_MOVE_TurnLeft        0x20  // TurnLeft With Motion Parameters
#define CMD_MOVE_TurnLeft_Free	 0x21  // TurnLeft Without Motion Parameters
#define CMD_MOVE_TurnRight       0x10  // TurnRight With Motion Parameters
#define CMD_MOVE_TurnRight_Free  0x11  // TurnRight Without MOtion Parameters

// Motion State Definitions
#define STAT_MOVE_STOP         0x01
#define STAT_MOVE_FORWARD      0x02
#define STAT_MOVE_BACKWARD     0x04
#define STAT_MOVE_TURNLEFT     0x08
#define STAT_MOVE_TURNRIGHT    0x10
#define STAT_MOVE_ERROR        0xFF

// Motion Execute Result Definition
#define RES_DONE         0x01
#define RES_ABORT_1      0x02
#define RES_ABORT_2      0x04
#define RES_ABORT_3      0x08
#define RES_ABORT_4      0x10
#define RES_ABORT_ERROR  0xFF


// Motion Execute State
#define ME_STATE_Init      0xF1
#define ME_STATE_Running   0xF2
#define ME_STATE_Done      0xF3
#define ME_STATE_ABORT1     0xE1 // New Command
#define ME_STATE_ABORT2     0xE2 // DropState
#define ME_STATE_ABORT3     0xE3 // SuspendState
#define ME_STATE_ABORT4     0xE4 // CompactState

#endif /* COM_UART_PROTOCOLS_H_ */
