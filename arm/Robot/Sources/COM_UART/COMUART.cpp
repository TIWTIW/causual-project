

#include "COMUART.h"

COM_UART::COM_UART() {
    m_BaudRate = B115200;
    m_Serial_Port = "/dev/ttySAC1";
    m_fd = 0;

    m_Statistics.cnt_error = 0;
    m_Statistics.cnt_correct = 0;

    bzero(&m_Statistics, sizeof(UART_Stat_Info_t));

    bzero(m_UART_Rx, 30);
    bzero(m_UART_Tx, 16);
}

COM_UART::COM_UART(char* SerialPort) {
    m_BaudRate = B115200;
    m_Serial_Port = SerialPort;
    m_fd = 0;

    bzero(&m_Statistics, sizeof(UART_Stat_Info_t));

    bzero(m_UART_Rx, 30);
    bzero(m_UART_Tx, 16);
}


// The dis-constructor of class COM_UART.
COM_UART::~COM_UART()
{
    close(m_fd);
}

int COM_UART::COM_UART_Init( string SerialPort )
{
    m_Serial_Port = SerialPort;
    return COM_UART_Init();
}
int COM_UART::COM_UART_Init(void)
{
    m_fd = open(m_Serial_Port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    //m_fd = open(m_Serial_Port.c_str(), O_RDWR | O_NOCTTY );
    if(m_fd == -1)
    {
        perror("Fatal Error--_uart_init(): Failed to open the Serial Port!!!");
        return -1;
    }
    /*
    int flags = fcntl(fd, F_GETFL,0);
    flags &= ~O_NONBLOCK;
    fcntl(fd,F_SETFL,flags);
    */
    fcntl(m_fd, F_SETFL, 0);

    // cout << "The FD is: " << m_fd << endl;

    struct termios attr;
    // Get the Attributes
    if(tcgetattr(m_fd,&attr)!=0)
    {
        cout<<"Fatal Error--_uart_init(): Get Serial parameters error!"<<endl;
        return -1;
    }
    // Set the Baud Rate, Default is 115200
    // Candidates: B230400,B115200,B57600, B38400, B19200, B9600, B4800 ...
    cfsetispeed(&attr, m_BaudRate); // input  rate
    cfsetospeed(&attr, m_BaudRate); // output rate

    // Control modes Settings
    attr.c_cflag |= CLOCAL; // Ignore modem control lines
    attr.c_cflag |= CREAD;  // Enable receiver

    attr.c_cflag &= ~CSIZE; // Character size mask
    attr.c_cflag |= CS8;    // Data length: CS5, CS6, CS7, CS8

    attr.c_cflag &= ~PARENB; // Disable Parity Check

    attr.c_cflag &= ~CSTOPB; // Set Stop bit length to 1
    //attr.c_cflag |= CSTOPB;  // Set Stop bit length to 2

    // Output modes Settings
    attr.c_oflag &= ~OPOST; // Disable implementation-defined output processing

    // local modes Settings
    attr.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //

    // input modes Settings
    attr.c_iflag &= ~(ICRNL | IXON);
    //attr.c_iflag |= IXON | IXOFF; // Enable XON/XOFF flow control on input/output
    attr.c_iflag |= IXANY; // Typing any character will restart  stopped  output.

    // Special modes Settings
    attr.c_cc[VTIME] = 0; // Timeout in deci-seconds for non-canonical read(ms).
    attr.c_cc[VMIN] = 0;  // Minimum number of characters for noncanonical read

    tcflush(m_fd,TCIOFLUSH); // flushes both data received but not read,
    //and  data  written  but not transmitted.

    // Set the Attributes
    if(tcsetattr(m_fd,TCSANOW,&attr)!=0)
    {
        perror("Fatal Error--_uart_init(): Failed to Set the Serial Port!!!");
        return -1;
    }
    // Set the Serial port Attributes Succeed
    //cout << "Info--_uart_init(): Set the Serial port Attributes Succeed!" << endl;
    return 0;
}

/* UART Communication Protocol before V2.0.20170214
int COM_UART::Recv( sensor_info & sensor_data, 
                    MotionStat_t &motion_stat,
                    MotionRes_t &motion_res )
{
    // Receive the frame
    if( _recv() != 30 )
    {
        //cout << "testPoint:COM_UART::Recv" << endl;
        //cout << "Info--UART_Update(): No new frame comes!" << endl;
        return 1;
    }
    // Decode the Frame has received
    // CRC check
    if( (m_UART_Rx[0] != Frame_Head_STM2ARM) || (LM_CRC_TableDriven(m_UART_Rx, 30) !=0) )
    {
        //cout << "Error--_UART_Decoder(): Frame Broken!" << endl;
        return -1;
    }
    // CRC Check Passed, then decode
    short int tmpH = 0;
    short int tmpL = 0;

    // Byte[1~4]: Hall Code Disk
    tmpH = m_UART_Rx[1] << 8;
    tmpL = m_UART_Rx[2] & 0x00ff;
    sensor_data.Hall_Left_Delta = tmpH | tmpL;
    sensor_data.Hall_Left_Total += sensor_data.Hall_Left_Delta;
    tmpH = m_UART_Rx[3] << 8;
    tmpL = m_UART_Rx[4] & 0x00ff;
    sensor_data.Hall_Right_Delta = tmpH | tmpL;
    sensor_data.Hall_Right_Total += sensor_data.Hall_Right_Delta;
    // Byte[5~8]: IMU7011 Data
    tmpH = m_UART_Rx[5] << 8;
    tmpL = m_UART_Rx[6] & 0x00ff;
    sensor_data.IMU7011_Angle = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[7] << 8;
    tmpL = m_UART_Rx[8] & 0x00ff;
    sensor_data.IMU7011_AngleRate = ((float)(tmpH | tmpL ))/100;
    // Byte[9~10]: Reserved
    // Byte[11~12]: Sensor Group
    sensor_data.SEN1 = m_UART_Rx[11];
    sensor_data.SEN2 = m_UART_Rx[12];
    // Byte[13~16]: Distance Sensor data
    tmpH = m_UART_Rx[13] << 8;
    tmpL = m_UART_Rx[14] & 0x00ff;
    sensor_data.GP2Y0A_Left = tmpH | tmpL;
    tmpH = m_UART_Rx[15] << 8;
    tmpL = m_UART_Rx[16] & 0x00ff;
    sensor_data.GP2Y0A_Right = tmpH | tmpL;

    // Byte[17~23]: Motion State
    motion_stat.State = m_UART_Rx[17];
    tmpH = m_UART_Rx[18] << 8;
    tmpL = m_UART_Rx[19] & 0x00ff;
    motion_stat.Speed = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[20] << 8;
    tmpL = m_UART_Rx[21] & 0x00ff;
    motion_stat.AngSpeed = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[22] << 8;
    tmpL = m_UART_Rx[23] & 0x00ff;
    motion_stat.Accel = ((float)(tmpH | tmpL ))/100;
    // Byte[24~26]: Motion Execute Result
    tmpH = m_UART_Rx[24] << 8;
    tmpL = m_UART_Rx[25] & 0x00ff;
    motion_res.serialnum = tmpH | tmpL;
    motion_res.state = m_UART_Rx[26]; 
    // Clear the Receive Buffer
    bzero(m_UART_Rx, 30);
    
    return 0;    
}
*/
int COM_UART::Recv( sensor_info & sensor_data, 
                    MotionStat_t &motion_stat,
                    MotionRes_t &motion_res )
{
    // UART Communication Protocol  Version 2.0.20170214
    // Receive the frame
    if( _recv() != 30 )
    {
        //cout << "testPoint:COM_UART::Recv" << endl;
        //cout << "Info--UART_Update(): No new frame comes!" << endl;
        return 1;
    }
    // Decode the Frame has received
    // CRC check
    if( (m_UART_Rx[0] != Frame_Head_STM2ARM) || (LM_CRC_TableDriven(m_UART_Rx, 30) !=0) )
    {
        //cout << "Error--_UART_Decoder(): Frame Broken!" << endl;
        return -1;
    }
    // CRC Check Passed, then decode
    short int tmpH = 0;
    short int tmpL = 0;
    unsigned int tmpint32 = 0;

    // Byte[1~8]: Hall Code Disk
    tmpint32 = m_UART_Rx[1] << 24 & 0xff000000;
    tmpint32 = m_UART_Rx[2] << 16 | tmpint32;
    tmpint32 = m_UART_Rx[3] << 8  | tmpint32;
    tmpint32 = m_UART_Rx[4]       | tmpint32;
    sensor_data.Hall_Left_Total = tmpint32;

    tmpint32 = m_UART_Rx[5] << 24 & 0xff000000;
    tmpint32 = m_UART_Rx[6] << 16 | tmpint32;
    tmpint32 = m_UART_Rx[7] << 8  | tmpint32;
    tmpint32 = m_UART_Rx[8]       | tmpint32;
    sensor_data.Hall_Right_Total = tmpint32;

    // Byte[9~12]: Distance Sensor data
    tmpH = m_UART_Rx[9] << 8;
    tmpL = m_UART_Rx[10] & 0x00ff;
    sensor_data.GP2Y0A_Left = tmpH | tmpL;
    tmpH = m_UART_Rx[11] << 8;
    tmpL = m_UART_Rx[12] & 0x00ff;
    sensor_data.GP2Y0A_Right = tmpH | tmpL;

    // Byte[13~14]: Sensor Group
    sensor_data.SEN1 = m_UART_Rx[13];
    sensor_data.SEN2 = m_UART_Rx[14];
    // Byte[15]: Motion State
    motion_stat.State = m_UART_Rx[15];  

    // Byte[16~19]: IMU7011 Data
    tmpH = m_UART_Rx[16] << 8;
    tmpL = m_UART_Rx[17] & 0x00ff;
    sensor_data.IMU7011_Angle = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[18] << 8;
    tmpL = m_UART_Rx[19] & 0x00ff;
    sensor_data.IMU7011_AngleRate = ((float)(tmpH | tmpL ))/100;
    // Byte[20~24]: Reserved

    // Byte[25~27]: Motion Execute Result
    tmpH = m_UART_Rx[25] << 8;
    tmpL = m_UART_Rx[26] & 0x00ff;
    motion_res.serialnum = tmpH | tmpL;
    motion_res.state = m_UART_Rx[27]; 

    // Clear the Receive Buffer
    bzero(m_UART_Rx, 30);
    
    return 0;    
}


    // Receive and Resolve the Data from STM32
    // Input parameter should be actual parameter
int COM_UART::Recv( Hall_t &delta_cnt, MPU_t &mpu_data,
                    unsigned char &SEN1, unsigned char &SEN2,
                    Dis_t &dis_data, MotionStat_t &motion_data,
                    MotionRes_t &motion_res)
{
    // Receive the frame
    if( _recv() != 30 )
    {
        //cout << "Info--UART_Update(): No new frame comes!" << endl;
        return 1;
    }
    // Decode the Frame has received
    // CRC check
    if( (m_UART_Rx[0] != Frame_Head_STM2ARM) || (LM_CRC_TableDriven(m_UART_Rx, 30) !=0) )
    {
        cout << "Error--_UART_Decoder(): Frame Broken!" << endl;
        return -1;
    }
    // CRC Check Passed, then decode
    unsigned short int tmpH = 0;
    unsigned short int tmpL = 0;
    // Decode the Delta Hall counter data
    tmpH = m_UART_Rx[1] << 8;
    tmpL = m_UART_Rx[2] & 0x00ff;
    delta_cnt.cntL = tmpH | tmpL;
    tmpH = m_UART_Rx[3] << 8;
    tmpL = m_UART_Rx[4] & 0x00ff;
    delta_cnt.cntR = tmpH | tmpL;
    // Decode the MPU data
    tmpH = m_UART_Rx[5] << 8;
    tmpL = m_UART_Rx[6] & 0x00ff;
    mpu_data.AngR = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[7] << 8;
    tmpL = m_UART_Rx[8] & 0x00ff;
    mpu_data.AngP = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[9] << 8;
    tmpL = m_UART_Rx[10] & 0x00ff;
    mpu_data.AngY = ((float)(tmpH | tmpL ))/100;
    // Decode the SEN1 & SEN2
    SEN1 = m_UART_Rx[11];
    SEN2 = m_UART_Rx[12];
    // Decode the Distance data
    tmpH = m_UART_Rx[13] << 8;
    tmpL = m_UART_Rx[14] & 0x00ff;
    dis_data.disL_cnt = tmpH | tmpL;
    tmpH = m_UART_Rx[15] << 8;
    tmpL = m_UART_Rx[16] & 0x00ff;
    dis_data.disR_cnt = tmpH | tmpL;
    // Decode the Motion State
    motion_data.State = m_UART_Rx[17];
    tmpH = m_UART_Rx[18] << 8;
    tmpL = m_UART_Rx[19] & 0x00ff;
    motion_data.Speed = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[20] << 8;
    tmpL = m_UART_Rx[21] & 0x00ff;
    motion_data.AngSpeed = ((float)(tmpH | tmpL ))/100;
    tmpH = m_UART_Rx[22] << 8;
    tmpL = m_UART_Rx[23] & 0x00ff;
    motion_data.Accel = ((float)(tmpH | tmpL ))/100;
    // Decode the Motion Execute Result
    tmpH = m_UART_Rx[24] << 8;
    tmpL = m_UART_Rx[25] & 0x00ff;
    motion_res.serialnum = tmpH | tmpL;
    motion_res.state = m_UART_Rx[26];

    //
    bzero(m_UART_Rx, 30);
    return 0;
}

int COM_UART::COM_Motion( MCB_t cmd_motion )
{
    // Entry Data Check
    if( 0 ) // Data check error happened
    {
        cout << "Error--UART_Ctrl(): Entry data error!" << endl;
        return -2;
    }

    // Encode the command
    // Set the frame head
    m_UART_Tx[0] = Frame_Head_ARM2STM;
    // Set the system command
    m_UART_Tx[1] = 0x00; // Mens this frame is not a system command frame
    // Set the motion command
    m_UART_Tx[2] = cmd_motion.cmd_move & 0xff;
    
    // Set the reserved command
    m_UART_Tx[3] = 0x00;
    // Set the command serials number
    m_UART_Tx[4] = (unsigned char)(cmd_motion.serialnum>>8) & 0xff;
    m_UART_Tx[5] = (unsigned char)(cmd_motion.serialnum   ) & 0xff;
    // Set the motion parameter
    // Set Speed
    m_UART_Tx[6] = (unsigned char)(cmd_motion.SetSpeed>>8) & 0xff;
    m_UART_Tx[7] = (unsigned char)(cmd_motion.SetSpeed   ) & 0xff;
    // Set Distance
    m_UART_Tx[8] = (unsigned char)(cmd_motion.SetDis>>8) & 0xff;
    m_UART_Tx[9] = (unsigned char)(cmd_motion.SetDis   ) & 0xff;
    // Set Angle Speed
    m_UART_Tx[10] = (unsigned char)(cmd_motion.SetAngSpeed>>8) & 0xff;
    m_UART_Tx[11] = (unsigned char)(cmd_motion.SetAngSpeed   ) & 0xff;
    // Set Angle
    m_UART_Tx[12] = (unsigned char)(cmd_motion.SetAngle>>8) & 0xff;
    m_UART_Tx[13] = (unsigned char)(cmd_motion.SetAngle   ) & 0xff;
    // Set the CRC Flag
    unsigned short checksum = LM_CRC_TableDriven(m_UART_Tx,14);
    m_UART_Tx[14] = (checksum>>8) & 0xff;
    m_UART_Tx[15] =  checksum     & 0xff;

    // Send the command
    int res = _send();
    if( res != 16 )
    {
        perror("Error--UART_Ctrl(): Send The frame error!");
        return 1;
    }
    bzero(m_UART_Tx, 16);
    return 0; // Control signal sent succeed!
}

int COM_UART::COM_System( unsigned char cmd_sys )
{
    // Entry Data Check
    if( 0 ) // Data check error happened
    {
        cout << "Error: UART: Entry data error!" << endl;
        return -2;
    }
    // Encode the command
    // Set the frame head
    m_UART_Tx[0] = Frame_Head_ARM2STM;
    // Set the system command
    m_UART_Tx[1] = cmd_sys;
    // Set the CRC Flag
    unsigned short checksum = LM_CRC_TableDriven(m_UART_Tx,14);
    m_UART_Tx[14] = (checksum>>8) & 0xff;
    m_UART_Tx[15] =  checksum     & 0xff;
    // Send the command
    int res = _send();
    if( res != 16 )
    {
        perror("Error: UART Send The frame error!");
        return 1;
    }
    bzero(m_UART_Tx, 16);
    return 0; // Control signal sent succeed!
}


// Send A Frame to STM: 16 Bytes
int COM_UART::_send(void)
{
    return write(m_fd, m_UART_Tx, 16);
}

// Receive A Frame from the STM: 30 Bytes
int COM_UART::_recv(void)
{
    return read(m_fd, m_UART_Rx, 30);
}
