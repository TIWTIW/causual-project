/*
 * crc_limin.h
 *
 *  Created on: 2016年7月12日
 *      Author: limin
 */

#ifndef CRC_LIMIN_H_
#define CRC_LIMIN_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sys/types.h>
#include <cstdint>

// choose the CRC algorithm
// if you change it, please update the lookup table in the file crc_limin.cc
#define CRC_CCITT

// Indicate here if want to use a lookup table to calculate the crc
//#define Table_Driven true
// Definition for CRC-CCITT Algorithm
#ifdef CRC_CCITT

#define POLYNOMIAL 		0x1021
#define INITIAL_VAL		0xffff
#define FINAL_XOR_VAL	0x0000
#define REVERSED_DATA	FALSE
#define REVERSED_OUT	FALSE
#endif // CRC_CCITT

// Definition for CRC16 Algorithm
#ifdef CRC16
typedef unsigned short CRC;
#define POLYNOMIAL 		0x8005
#define INITIAL_VAL		0x0000
#define FINAL_XOR_VAL	0x0000
#define REVERSED_DATA	FALSE
#define REVERSED_OUT	FALSE
#endif // CRC16

typedef unsigned short CRC;
CRC LM_CRC_Simple(char *data, int num);
CRC LM_CRC_TableDriven(unsigned char *data, int num);
void TableInit(void);

#endif /* CRC_LIMIN_H_ */
