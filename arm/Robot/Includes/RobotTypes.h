#ifndef _ROBOTTYPES_H_
#define _ROBOTTYPES_H_

#include <ctime>
#include <string>
#include <fstream>

#include "pthread.h"
#include "COM_UART/COMUART.h"

#define UART1_NAME_str "/dev/ttySAC1"
//#define UART1_NAME_str "/dev/ttyUSB0"


#include "COMUART.h"


using namespace std;

enum MoveState
{
    ROTATE,
    FORWARD
};
typedef pose_t POSE;
typedef POSE DATA;

typedef struct Point_t
{
    float x;
    float y;
} point_t;

typedef struct Grid_Point_t
{
    int x;
    int y;
}grid_t;

class CRobot
{
public:
    CRobot();
    ~CRobot();
    int Init( void );

// Sub-object: Communication Node -- UART1: ARM1<-->STM32
// Send Command to STM32 and Receive Robot Info From STM32
public:
    //COM_UART m_UART1("/dev/ttySAC1"); // ARM and STM32 Communicate through the device ttySAC1
    COM_UART m_UART1;
    pthread_mutex_t m_mutex_UART1_send; // Ensure only one command was sent at same time

public:
    int cmd_SystemInit( void ); // Both ARM and STM32 System Initialize
    int cmd_SystemSleep( void );   // Robot Enter the Sleeping State
    int cmd_SystemShut( void );    // Shutdown the Robot
    int cmd_Motion( MCB_t cmd_motion ); // Control the Robot Execute Basic Motion

/******************************************************************/
/* Sub-Module: Data Fuse Level-0
 * Sub-Module-meta
 *     Module Name: DataFuse_L0
 *     Description: 
 *     Author     :
 *     Maintainer :
 *     Version    :
 * Sub-Module Introduction:
**/
//private:
    //pthread_t m_pidDataFuseL0; // Handle the Information from Level-0
    //static void* pThread_DataFuse_L0(void *pParam);
/******************************************************************/


// Sub-object: Vision Location Pose
// This Variable can only be Modified by Vision Location Module
private:
    pose_t   m_vPose;   // Robot Global Pose From Vision Location
    pthread_mutex_t m_mutex_vPose;
public:
    void SetvPose( pose_t vPose );
    pose_t GetvPose( void );

// Sub-object: IMU Location Pose
// This can only modified by inner thread--pThread_DataFuse_L0 
private:
    pose_t   m_imuPose; // Robot Global Pose From IMU Location
    pthread_mutex_t m_mutex_imuPose;
public:
    void SetimuPose( pose_t imuPose );
    pose_t GetimuPose( void );

// Sub-object: Robot Sensor Information
private:
    sensor_info m_info_sensors; // Robot Sensor Information
    pthread_mutex_t m_mutex_info_sensors;
public:
    void SetSensors( sensor_info sensor_info );
    sensor_info GetSensors( void );

private:
    MotionStat_t m_info_MotionState;
    pthread_mutex_t m_mutex_info_motionstate;
    MotionRes_t  m_info_MotionRes;
    pthread_mutex_t m_mutex_info_motionres;
public:
    void SetMotionState( MotionStat_t motion_state );
    void SetMotionRes( MotionRes_t motion_res );
    MotionStat_t GetMotionState( void );
    MotionRes_t  GetMotionRes( void );

}; // The End of Declaration of Class CRobot


#endif //_ROBOTTYPES_H_
