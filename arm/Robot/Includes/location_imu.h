
#ifndef _LOCATION_IMU_H_
#define _LOCATION_IMU_H_



#include "MyHeader.h"
#include "RobotTypes.h"
#include "Robot_Defines_IPC.h"
#include "COM_UART/COMUART.h"
#include <iostream>

#define PI  3.1415926

#define K   (PI/180)

pose_t ImuPoseUpdate( pose_t old_pose, unsigned char RobotMotionState, float curr_angle, float delta_disL, float delta_disR );

point_t TF_Coordinator( point_t originPoint, float Delta_X, float Delta_Y, float Delta_Theta );

bool Is_Postion_Equal( const pose_t P1, const pose_t P2 );
bool Is_PoseEqual( const pose_t P1, const pose_t P2 );

bool Is_Length_Equal( const float len1, const float len2 );
bool Is_Angle_Equal( const float theta1, const float theta2 );

float disEuclid( const pose_t P1, const pose_t P2 );

float angleAdd( const float angle1, const float angle2 );
float angleMinus( const float angle1, const float angle2 );


#endif //_LOCATION_IMU_H_
