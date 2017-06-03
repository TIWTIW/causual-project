#ifndef __ROBOT_DEFINES_IPC_H_
#define __ROBOT_DEFINES_IPC_H_

#include "RobotTypes.h"


/*
** Message Queue Definitions
**/

#define MQ_Command "/MQ_Command"

#define msg_queue01 "/mq_node01"

// message queue between level 1 and level 2
// the message type is msg_node12_t, defined below
#define msg_queue12 "/mq_node12"

// message queue between level 2 and level 3
// the message type is msg_node13_t, defined below
#define msg_queue13 "/mq_node13"

// message queue between level 2 and level 3
// the message type is msg_node23_t, defined below
#define msg_queue23 "/mq_node23"


#define SEM_PIDLIST "/sem_pidlist"


#define shm_msg01 "/shm_node01"
#define sem_msg01 "sem_node01"
#define shm_msg12 "/shm_node12"
#define sem_msg12 "sem_node12"


#define Shm_Name_AimPose "/shm_aimpose"
#define Sem_Name_AimPose "/sem_aimpose"

#define Sem_Name_takephoto "/sem_takephoto"
#define Sem_Name_VisionLocation "/sem_visionlocation"


/*
 * Signal (used to synchronize different process) Definitions
*/

// Level 3 notify the global path has been updated
#define SIG_GlobalPath_Updated 64
// Level 2 notify level 3 to re-planning the global path
#define SIG_GlobalPath_RePlan  63
// Level 2 notify the local path has been updated
#define SIG_LocalPath_Updated  62
// level 1 notify the pose has been updated
#define SIG_Pose_Updated       61

// Level n Initialization has done
#define SIG_INIT_L0 34 
#define SIG_INIT_L1 35
#define SIG_INIT_L2 36
#define SIG_INIT_L3 37
// Notify the Vision Navigation Program Start to Work
#define SIG_Vision_Nav_Start 38


#define SIG_CMD_MOTION_FORWARD 39
#define SIG_CMD_MOTION_TURNLEFT 40
#define SIG_CMD_MOTION_STOP 41

/*
** Shared Memory Definitions
**/


#endif