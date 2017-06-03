#ifndef _COMMAMDGENERATOR_H_H
#define _COMMAMDGENERATOR_H_H

#include "MyHeader.h"
#include "RobotTypes.h"
#include "Robot_Defines_IPC.h"
#include "COM_UART/COMUART.h"
#include <iostream>

#include "location_imu.h"

MCB_t GetMotionCommand( pose_t curr_pose, pose_t aim_pose, int *flag );
MCB_t GetMotionCommand_Basic( pose_t curr_pose, pose_t aim_pose );
MCB_t GetMotionCommand_V20170302( pose_t curr_pose, pose_t aim_pose );
MCB_t GetMotionCommand_V20170307( pose_t curr_pose, pose_t aim_pose, int *flag );
MCB_t GetMotionCommand_V20170308( pose_t curr_pose, pose_t aim_pose, int *flag );
#endif // _COMMAMDGENERATOR_H_H
