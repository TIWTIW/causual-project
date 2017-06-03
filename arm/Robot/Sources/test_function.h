#ifndef _test_function_H_
#define _test_function_H_

#include "MyHeader.h"
#include "RobotTypes.h"

typedef struct 
{
	float Pcov[3];
	float Gain[3];
	float Rcov[3];
	float Qcov[3];
}Kalman_state_t;

void kalman_init(Kalman_state_t *state);
pose_t Location_Kalman(pose_t pose_vo, pose_t pose_imu, Kalman_state_t *state);
#endif