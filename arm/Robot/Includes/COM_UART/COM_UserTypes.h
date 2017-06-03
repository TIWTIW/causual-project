

#ifndef COM_UART_USERTYPES_H_
#define COM_UART_USERTYPES_H_

#include <iostream>
#include <fstream>

using namespace std;

// data structure of robot pose
typedef struct pose_t{
    float x;        // pose x
    float y;        // pose y
    float theta;    // pose theta
} location_t;
ostream&  operator << ( ostream&  os, const pose_t &t );
ofstream& operator << ( ofstream& os, const pose_t &t );


// Sensor Data Types
typedef struct sensors_t
{
    // IMU7011: single-axis Gyroscope( Detect the Yaw angle )
    float IMU7011_Angle;        // unit: degree; range: -180.00~180.00
    float IMU7011_AngleRate;    // unit: degree/s; range: -? ~ +?
    // GP2Y0A41SK0F: Distance Measuring Sensor Unit( Sharp Co. Ltd. )
    unsigned short GP2Y0A_Left;          // unit: mm; range: 0 ~ 200
    unsigned short GP2Y0A_Right;         // unit: mm; range 0~ 200
    // Compact(7:6) | Suspend(5:4) | Drop(3:0)
    unsigned char SEN1;
    // Dust Full
    unsigned char SEN2;
    // Hall: Hall Code Disk used to Measure move distance
    unsigned int Hall_Left_Total;  // unit: cnt; range:
    unsigned int Hall_Right_Total; // unit: cnt; range:
    unsigned short Hall_Left_Delta;      // unit: cnt;range: 0~65535
    unsigned short Hall_Right_Delta;     // unit: cnt;range: 0~65535
} sensor_info;
ostream&  operator << ( ostream&  os, const sensor_info &t );
ofstream& operator << ( ofstream& os, const sensor_info &t );




// Sensor Related Data Types
typedef struct Hall_Encoder_Cnt_t
{
    // 1 circle means: 564(12 x 47) counts or 228 mm
    unsigned short int cntL;  // Left wheel
    unsigned short int cntR; // Right wheel
} Hall_t;

typedef struct MPU6050_t
{
    // Unit: degree per second
    float AngY;  // Yaw angle
    float AngR;  // Roll angle
    float AngP;  // Pitch angle
} MPU_t;

// Motion Related Data Types
typedef struct Motion_State_t
{
    unsigned char State;     // Robot Motion State
    // Robot Motion State are defined in COM_Protocol.h
    float         Speed;     // Robot Move Speed, Unit: mm/s
    float         AngSpeed;  // Robot Rotation Angle Speed, Unit: degree per second
    float         Accel;     // Robot Move Acceleration, Unit: mm^2/s
} MotionStat_t;

typedef struct Motion_Execute_Res_t
{
    unsigned short int serialnum;  // Motion Serials Number(0~65535)
    unsigned char      state;      // Motion Execute Result
    // Motion Execute Result are defined in COM_Protocol.h
} MotionRes_t;

typedef struct Disance_t
{
    unsigned short int disL_cnt;
    unsigned short int disR_cnt;
} Dis_t;

typedef struct Motion_Control_Block_t
{
    unsigned short int serialnum;  // Motion Serials Number(0~65535)
    unsigned char      priority;   // Motion Execute Priority(0~255)
    unsigned char      cmd_move;   // Motion Command
    // Motion Command are defined in COM_Protocol.h
    unsigned short int SetSpeed;  // Motion Parameter: Speed (0~500 mm/s * 2.476)
    unsigned short int SetDis;    // Motion Parameter: Move Distance(0~65535 mm)
    unsigned short int SetAngSpeed; // MOtion Parameter: Angle Speed (0~90 d/s)
    unsigned short int SetAngle;    // Motion Parameter: Rotation angle( 0~360 degree)
} MCB_t;

// UART Statistic Related Data Type
typedef struct UART_Stat_Info_t
{
    unsigned int cnt_correct;
    unsigned int cnt_error;
    // count send and receive frame
    unsigned int cnt_send;
    unsigned int cnt_recv;
    // count details
    unsigned int cnt_send_sys;
    unsigned int cnt_send_stop;
    unsigned int cnt_send_forward;
    unsigned int cnt_send_backward;
    unsigned int cnt_send_turnleft;
    unsigned int cnt_send_turnright;
} USI_t;

/**************************************************************************/
// Part II: The format output of the types defined above,
// Warning ! please remember to remove them before use this file in the platform of STM32.

ostream& operator << ( ostream& os, const Hall_Encoder_Cnt_t &t );
ofstream& operator << ( ofstream& os, const Hall_Encoder_Cnt_t &t );

ostream& operator << ( ostream& os, const MPU6050_t &t );
ofstream& operator << ( ofstream& os, const MPU6050_t &t );

ostream& operator << ( ostream& os, const Motion_State_t &t );
ofstream& operator << ( ofstream& os, const Motion_State_t &t );


ostream& operator << ( ostream& os, const Motion_Execute_Res_t &t );
ofstream& operator << ( ofstream& os, const Motion_Execute_Res_t &t );

ostream& operator << ( ostream& os, const Motion_Control_Block_t &t );
ofstream& operator << ( ofstream& os, const Motion_Control_Block_t &t );

ostream& operator << ( ostream& os, const Motion_Control_Block_t &t );
ofstream& operator << ( ofstream& os, const Motion_Control_Block_t &t );

#endif // COM_UART_USERTYPES_H_
