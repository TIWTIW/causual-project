/*
 * crc_limin.cc
 *
 *  Created on: 2016年7月12日
 *      Author: limin
 */

#include "CRC.h"

// the definition below is just for table generate
typedef unsigned short width_t;
#define WIDTH (8*sizeof(width_t))
#define TOPBIT (1<<(WIDTH-1))

using namespace std;

// The Lookup table for quick computing CRC-CCITT
// Generated by the function void TableInit(void);
//The Begin of the Table
CRC LM_CRC_LOOKUP_TABLE[256] = {
		0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
		0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
		0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
		0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
		0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
		0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
		0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
		0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
		0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
		0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
		0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
		0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
		0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
		0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
		0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
		0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
		0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
		0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
		0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
		0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
		0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
		0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
		0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
		0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
		0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
		0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
		0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
		0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
		0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
		0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
		0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
		0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0,
};

//CRC LM_CRC_LOOKUP_TABLE[256] = {0};

/*
 * FunctionName: LM_CRC_Simple
 * Prototype   : CRC LM_CRC_Simple(unsigned char* data, int num);
 * para_input@1: unsigned char*data -- the address of the data to be calculated
 * para_input@2: int num -- the length of the data in then units of bytes
 * para_out    : an CRC object which was defined in the header file
 * Author      : liminkmf@mail.ustc.edu.cn AT USTC(http://www.ustc.edu.cn)
 * Description : This function is used to calculate the CRC checksum. It is
 *     implemented directly(not in the way of lookup table), so it is slow.
 *     The high speed CRC calculate function is
 *     CRC LM_CRC_TableDriven(unsigned char *data, int num) which is defined in
 *     this file too.
 *
 * Examples:
 *     unsigned char data1[20] = {'1','2','3','4','5','6','7','8','9',0x00,0x00};
 *     CRC test1 = LM_CRC_Simple(data1,9);
 *     // The test1 should be 0x29b1
 * Change log:
 *
 * */
CRC LM_CRC_Simple(char *data, int num)
{
	CRC Re_CRC = INITIAL_VAL;
	for(int i=0; i<num; i++)
	{
		Re_CRC = Re_CRC ^ (data[i]<<8);
		for(int j=0; j<8; j++)
		{
			if(Re_CRC & 0x8000)
			{
				Re_CRC = (Re_CRC << 1) ^ POLYNOMIAL;
			}
			else
			{
				Re_CRC <<= 1;
			}
		}
		Re_CRC &= 0xffff;
	}
	return (Re_CRC);
}

/*
 * FunctionName: LM_CRC_TableDriven
 * Prototype   : CRC LM_CRC_TableDriven(unsigned char* data, int num);
 * para_input@1: unsigned char*data -- the address of the data to be calculated
 * para_input@2: int num -- the length of the data in then units of bytes
 * para_out    : an CRC object which was defined in the header file
 * Author      : liminkmf@mail.ustc.edu.cn AT USTC(http://www.ustc.edu.cn)
 * Description : This function is used to calculate the CRC checksum. It is
 *     implemented  in the way of lookup table, so it is fast.
 *
 * Examples:
 *     // !!! Please o The Lookup Table Exist, if don't please use function
 *     // void TableInit(void) firstly to get the lookup table
 *     unsigned char data1[20] = {'1','2','3','4','5','6','7','8','9',0x00,0x00};
 *     CRC test2 = LM_CRC_TableDriven(data1,9);
 *     // The test2 should be 0x29b1
 * Change log:
 *
 * */
CRC LM_CRC_TableDriven(unsigned char *data, int num)
{
	CRC Re_CRC = INITIAL_VAL;
	// Table Init
	// TableInit();
	for(int i=0; i<num; i++)
	{
		// The expression is so simple refer to the document
		// 'A Painless Guide to CRC Error Detection Algorithm'
		Re_CRC = (Re_CRC<<8) ^ LM_CRC_LOOKUP_TABLE[((Re_CRC>>8)^data[i])];
	}

	return Re_CRC;
}

/*
 * FunctionName: TableInit
 * Prototype   : void TableInit(void);
 * para_input  : void
 * para_out    : void
 * Author      : liminkmf@mail.ustc.edu.cn AT USTC(http://www.ustc.edu.cn)
 * Description : This function is used to generate the lookup table for high
 *     speed CRC calculation.
 *
 * Change log:
 *
 * */
void TableInit(void)
{
	// Calculate the table
	for(int i=0; i<256; i++)
	{
		// Initialize the Remainder
		CRC Re_CRC = (i<<8);
		for(int bit=0; bit<8; bit++)
		{
			if(Re_CRC & TOPBIT)
			{
				Re_CRC = (Re_CRC<<1) ^ POLYNOMIAL;
			}
			else
			{
				Re_CRC <<= 1;
			}
		}
		// Ensure the length of CRC is 16bits(Just For 16bits CRC)
		// You can change it to Re_CRC &= 0xffffffff for 32bits CRC
		Re_CRC &= 0xffff;
		// Save the results to the lookup table
		LM_CRC_LOOKUP_TABLE[i] = Re_CRC;
	}

	// the code below is used to save the table to a file
	ofstream out;
	string filename = "CRC-CCITT_Table.txt";
	//char* filename = "CRC16_Table.txt";
	//char* filename = "CRC32_Tbale.txt";
	out.open(filename.c_str());
	string message = "This is the lookup table for CRC-CCITT\n";
	out << message;
	out << "****************************************************\n"
		<< "* Name       : CRC-CCITT                           *\n"
		<< "* Width      : 16                                  *\n"
		<< "* Polynomial : 1021                                *\n"
		<< "* InitValue  : 0xffff                              *\n"
		<< "* XOR_OUT    : 0x0000                              *\n"
		<< "* RefIn      : FALSE                               *\n"
		<< "* RefOut     : FALSE                               *\n"
		<< "****************************************************\n"
		<< "*test value  : 123456789                           *\n"
		<< "*test result : 0x29b1                              *\n"
		<< "****************************************************\n"
		<< "\n//The Begin of the Table\n";
	// Output the table to the file
	out << "CRC LM_CRC_LOOKUP_TABLE[256] = {\n\t";
	for(int i=0; i<256; i++)
	{
		out <<setfill('0');
		if(i%8==7)
		{
			out<<"0x"<<noshowbase<<setw(4)<<hex<<LM_CRC_LOOKUP_TABLE[i] <<dec<<", \n\t";
		}
		else
		{
			out<<"0x"<<noshowbase<<setw(4)<<hex<<LM_CRC_LOOKUP_TABLE[i] <<dec<<", ";
		}
	}
	out << "};// The End of the Table\n";
}