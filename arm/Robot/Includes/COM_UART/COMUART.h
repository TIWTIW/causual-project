/*  
 * Module meta: 
 *   Module Name: Communication Module
 *   Description: 
 *   Author     : 
 *   Maintainer :
 *   Version    :
**/



#ifndef COM_UART_COMUART_H_
#define COM_UART_COMUART_H_

#include <iostream>
#include <string>

// UART configuration related header files
#include <cstdlib>          // Standard Library Definition
#include <unistd.h>         // UNIX Standard Function Definition
#include <sys/types.h>      // Basic Data Types Definition
#include <sys/stat.h>       //
#include <fcntl.h>          // File Control Definition
#include <termios.h>        // POSIX Terminal Control Definnition
#include <cerrno>           // Error Related
#include <cstring>

// User defined header files
#include "CRC.h"
#include "COM_Protocol.h"
#include "COM_UserTypes.h"


using namespace std;

// UART object definition
class COM_UART{

public:
    COM_UART( );
    COM_UART( char* SerialPort );
    virtual ~COM_UART( );
    // UART COM Initialization Function
    // 0: Succeed; -1: Failed
    int COM_UART_Init( void );
    int COM_UART_Init( string SerialPort );
    // Send Motion Command
    int COM_Motion( MCB_t cmd_motion );
    // Send System Command
    int COM_System( unsigned char cmd_sys );
    // Receive and Resolve the Data from STM32
    // Input parameter should be actual parameter
    int Recv( Hall_t &delta_cnt, MPU_t &mpu_data,
              unsigned char &SEN1, unsigned char &SEN2,
              Dis_t &dis_data, MotionStat_t &motion_data,
              MotionRes_t &motion_res);

    int Recv( sensor_info & sensor_data, 
              MotionStat_t &motion_stat,
              MotionRes_t &motion_res );
    // Get the UART Statistics
    USI_t COM_Statistics( void );

private:
    // UART File Descriptor
    int m_fd;
    // Default Baud Rate is B115200
    speed_t m_BaudRate;
    // UART Serial Port Name
    //char* m_Serial_Port;
    string m_Serial_Port;
    // UART Communication Tx Buffer
    unsigned char m_UART_Tx[16];
    // UART Communication Rx Buffer
    unsigned char m_UART_Rx[30];

    // Statistics Variables
    UART_Stat_Info_t m_Statistics;

private:
    void _uart_close(void);
    int _send(void);
    int _recv(void);
};

#endif /* COM_UART_COMUART_H_ */
