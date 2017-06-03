/*
#include "pose.h"

#include "COMUART.h"

#define PI 3.1415926

static INFO_FRAME lastframe;

static POSE LastVisionPose;

static int flag = 1;

POSE VisionPoseUpdate_V1( const unsigned char LastMotionState, const POSE ImuCurrentPose )
{
    POSE Delta_Pose;
    bzero( &Delta_Pose, sizeof(POSE) );

    DATA Delta_Pose_Ref;
    Delta_Pose_Ref.x1 = ImuCurrentPose.x - LastVisionPose.x;
    Delta_Pose_Ref.y1 = ImuCurrentPose.y - LastVisionPose.y;
    Delta_Pose_Ref.theta1 = ImuCurrentPose.theta - LastVisionPose.theta; 

    Delta_Pose_Ref.x1 = Delta_Pose_Ref.x1/10;
    Delta_Pose_Ref.y1 = Delta_Pose_Ref.y1/10;

    cout << "Debug-VisionPoseUpdate_V1--Input Parameters: " << endl; 
    cout << "\t Last Motion State: " << (int)LastMotionState << endl;
    cout << "\t Current IMU Pose:  " << ImuCurrentPose << endl;

    switch( LastMotionState )
    {
        case STAT_MOVE_STOP:
            return LastVisionPose;
            break;
        case STAT_MOVE_FORWARD:
            cout << "Debug-VisionPoseUpdate_V1: Computing PoseLine !" << endl;
            Delta_Pose = computePoseLine( lastframe, Delta_Pose_Ref, flag );
            cout << "Debug-VisionPoseUpdate_V1: Compute PoseLine Done !" << endl;
            if ( Delta_Pose.x == 0 && Delta_Pose.y == 0 )
            {
                LastVisionPose = ImuCurrentPose;
                return LastVisionPose;
            }
            else
            {
                LastVisionPose.theta += Delta_Pose.theta * PI/180;
                LastVisionPose.x += Delta_Pose.x * cosf( LastVisionPose.theta );
                LastVisionPose.y += Delta_Pose.y * sinf( LastVisionPose.theta );
                return LastVisionPose;
            }
            break;
        case STAT_MOVE_BACKWARD:
            return LastVisionPose;
            break;
        case STAT_MOVE_TURNLEFT:
            Delta_Pose = computePoseRotate( lastframe, Delta_Pose_Ref, flag );
            if ( Delta_Pose.x == 0 && Delta_Pose.y == 0 )
            {
                LastVisionPose = ImuCurrentPose;
                return LastVisionPose;
            }
            else
            {
                LastVisionPose.theta += Delta_Pose.theta * PI/180;
                LastVisionPose.x += Delta_Pose.x * cosf( LastVisionPose.theta );
                LastVisionPose.y += Delta_Pose.y * sinf( LastVisionPose.theta );
                return LastVisionPose;
            }
            break;
        case STAT_MOVE_TURNRIGHT:
            Delta_Pose = computePoseRotate( lastframe, Delta_Pose_Ref, flag );
            if ( Delta_Pose.x == 0 && Delta_Pose.y == 0 )
            {
                LastVisionPose = ImuCurrentPose;
                return LastVisionPose;
            }
            else
            {
                LastVisionPose.theta += Delta_Pose.theta * PI/180;
                LastVisionPose.x += Delta_Pose.x * cosf( LastVisionPose.theta );
                LastVisionPose.y += Delta_Pose.y * sinf( LastVisionPose.theta );
                return LastVisionPose;
            }
            break;
        default:
            cout << "Error-VisionPoseUpdate: This Line should Never be Output!" << endl;
            break;
    }
}

*/