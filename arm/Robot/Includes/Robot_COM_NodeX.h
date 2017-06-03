#ifndef _ROBOT_COM_NODEX_H_
#define _ROBOT_COM_NODEX_H_

#include "MyHeader.h"
#include "COM_UART/COMUART.h"
#include "Robot_Defines_IPC.h"

struct Robot_msg_node01_t
{
    sensors_t RobotSensor;
    MotionStat_t RobotState;
    MotionRes_t RobotMotionRes;
};

struct Robot_msg_node12_t
{
    int GP2Y0A_L;
    int GP2Y0A_R;
    pose_t RobotPose;
    unsigned char SEN1;
    unsigned char SEN2;
    // Fang Need Motion Execute Result, added in 2017-02-13
    MotionRes_t MotionRes;
};


struct Robot_msg_AimPosition
{
    location_t AimPosition;
    bool FlagAimPoseReached; // true means aim pose reached
    bool FlagNewAimPoseSet;  // true means a new aim pose was set
};

int P_COM_Node0( pid_t pid_L1 );

void Handler_Signals_Main(int signum, siginfo_t *info, void *argv);

MCB_t GetCmdMotion( void );

#endif // _ROBOT_COM_NODEX_H_
