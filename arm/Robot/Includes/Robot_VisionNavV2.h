#ifndef __ROBOT_VISIONNAV_V2_H_
#define __ROBOT_VISIONNAV_V2_H_

#include <iostream>
#include "MyHeader.h"
#include "RobotTypes.h"
#include "Robot_Defines_IPC.h"
#include "COM_UART/COMUART.h"
#include "pose.h"
#include "location_imu.h"
#include "Robot_COM_NodeX.h"
#include "CommandGenerator.h"
#include "videodevice.h"
#include "distance_measure.h"
#include "distance_decoder.h"

#include <iostream>
#include <string>
using namespace std;

extern sem_t *mutex_takephoto;
Mat GetMatFrame( videoDevice videoName );


int Level1_Lacation_Trajectory( void );
void* pThread_L1_CommandUpdate( void*argv );

int Level2_LocalPlanning( pid_t L0_pid );
int Level3_GlobalPlanning( pid_t L0_pid, pid_t L1_pid );

void* pThread_MapUpdate( void *argv );

void* pThread_COM_Node1( void *argv );
void* pThread_COM_Node2( void *argv );
void* pThread_TAKE_Photo( void *argv );
void  Alongplanning(pose_t posetake ,pair<float,float> *obsttake ,int &cam_mask , int &flag ,int direction);


void *pThread_GP(void* param);
void *pThread_LP(void* param);

void* pThread_Location(void *argv);
bool thePointIsOCP(pose_t pose);
#endif //__ROBOT_VISIONNAV_V2_H_
