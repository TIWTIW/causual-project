
#include "test_function.h"

void kalman_init(Kalman_state_t *state)
{
	state->Pcov[0] = 10e-6;
	state->Pcov[1] = 10e-6;
	state->Pcov[2] = 10e-6;

	state->Qcov[0] = 10e-5;
	state->Qcov[1] = 10e-5;
	state->Qcov[2] = 10e-7;

	state->Rcov[0] = 10e-3;
	state->Rcov[1] = 10e-3;
	state->Rcov[2] = 10e-3;
}

pose_t Location_Kalman(pose_t pose_vo, pose_t pose_imu, Kalman_state_t *state)
{
	// State Prediction
	pose_t pose_pre, pose_kalman;
	pose_pre.x = pose_imu.x;
	pose_pre.y = pose_imu.y;
	pose_pre.theta = pose_imu.theta;

	state->Pcov[0] += state->Qcov[0];
	state->Pcov[1] += state->Qcov[1];
	state->Pcov[2] += state->Qcov[2];

	state->Gain[0] = state->Pcov[0] / (state->Pcov[0]+state->Rcov[0]);
	state->Gain[1] = state->Pcov[1] / (state->Pcov[1]+state->Rcov[1]);
	state->Gain[2] = state->Pcov[2] / (state->Pcov[2]+state->Rcov[2]);

	pose_kalman.x = pose_pre.x + state->Gain[0]*(pose_vo.x - pose_pre.x);
	pose_kalman.y = pose_pre.y + state->Gain[1]*(pose_vo.y - pose_pre.y);
	pose_kalman.theta = pose_pre.theta + state->Gain[2]*(pose_vo.theta - pose_pre.theta);

	state->Pcov[0] = (1-state->Gain[0]) * state->Pcov[0];
	state->Pcov[1] = (1-state->Gain[1]) * state->Pcov[1];
	state->Pcov[2] = (1-state->Gain[2]) * state->Pcov[2];

	return pose_kalman;
}