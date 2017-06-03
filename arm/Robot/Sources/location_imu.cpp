

#include "location_imu.h"

static unsigned char LastState = STAT_MOVE_STOP;


float disEuclid( const pose_t P1, const pose_t P2 )
{
    return sqrt( (P1.x-P2.x)*(P1.x-P2.x) + (P1.y-P2.y)*((P1.y-P2.y)) );
}

float angleAdd( const float angle1, const float angle2 )
{
    float res = angle2 + angle1;
    res = res >= 180  ? res-360 : res;
    res = res <= -180 ? res+360 : res;
    return res;
}
float angleMinus( const float angle1, const float angle2 )
{
    float res = angle1 - angle2;
    res = res >= 180  ? res-360 : res;
    res = res <= -180 ? res+360 : res;
    return res;
}

bool Is_PoseEqual( const pose_t P1, const pose_t P2 )
{
    const float Thres_offset_len = 10;
    const float Thres_offset_angle = 1; // degree
    if( fabs(P1.x-P2.x) > Thres_offset_len )
        return false;
    if( fabs(P1.y-P2.y) > Thres_offset_len )
        return false;
    float delta_theta = fabs(P1.theta-P2.theta) ;
    delta_theta = delta_theta>180? fabs(delta_theta-360) : delta_theta ;
    if( delta_theta > Thres_offset_angle )
        return false;
    return true;
}

bool Is_Postion_Equal( const pose_t P1, const pose_t P2 )
{
    if ( Is_Length_Equal( P1.x, P2.x ) && Is_Length_Equal( P1.y, P2.y ) && Is_Angle_Equal( P1.theta,P2.theta ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Is_Length_Equal( const float len1, const float len2 )
{
    float MAX_DIS_THRESHOLD = 40; // mm
    return( fabs( len1-len2 )<=MAX_DIS_THRESHOLD );
}

bool Is_Angle_Equal( const float theta1, const float theta2 )
{
    float MAX_THETA_THRESHOLD = 1; // degree
    float delta_theta = fabs(theta1-theta2) ;
    delta_theta = delta_theta>180? fabs(delta_theta-360) : delta_theta ;
    return(  delta_theta<=MAX_THETA_THRESHOLD );
}

static pose_t ImuPoseUpdate_Basic( pose_t old_pose, unsigned char RobotMotionState, float curr_angle, float delta_disL, float delta_disR )
{
    //cout << "Updating Robot Pose..." << endl;
    static unsigned int count_FunctionCall = 0 ;
    //static int Total_Runtime = 0;
    count_FunctionCall ++;
    //clock_t time_start = clock();

    pose_t new_pose;
    bzero( &new_pose, sizeof(pose_t) );

    new_pose.theta = -curr_angle;
    //float avrg_theta = (new_pose.theta+old_pose.theta)  * 0.5 ;
    float avrg_theta = new_pose.theta;

    float delta_dis;
    switch( RobotMotionState )
    {
        case STAT_MOVE_STOP:
            //delta_dis = (delta_disL + delta_disR)  * 0.5;
            new_pose.x = old_pose.x ;//+ delta_dis * cosf(avrg_theta * K);
            new_pose.y = old_pose.y ;//+ delta_dis * sinf(avrg_theta * K);
           break;
        case STAT_MOVE_FORWARD:
            delta_dis = (delta_disL + delta_disR)  * 0.5;
            new_pose.x = old_pose.x + delta_dis * cosf(avrg_theta * K);
            new_pose.y = old_pose.y + delta_dis * sinf(avrg_theta * K);
            break;
        case STAT_MOVE_BACKWARD:
            delta_dis = (delta_disL + delta_disR)  * 0.5;
            new_pose.x = old_pose.x - delta_dis * cosf(avrg_theta * K);
            new_pose.y = old_pose.y - delta_dis * sinf(avrg_theta * K);
            break;
        case STAT_MOVE_TURNLEFT:
            //delta_dis = (delta_disL - delta_disR)  * 0.5;
            delta_dis = 0;
            new_pose.x = old_pose.x;// + delta_dis * cosf(avrg_theta * K);
            new_pose.y = old_pose.y;// + delta_dis * sinf(avrg_theta * K);
            break;
        case STAT_MOVE_TURNRIGHT:
            //delta_dis = (delta_disL - delta_disR)  * 0.5;
            delta_dis = 0;
            new_pose.x = old_pose.x;// + delta_dis * cosf(avrg_theta * K);
            new_pose.y = old_pose.y;// + delta_dis * sinf(avrg_theta * K);
            break;
        default:
            //cout << "Warning-ImuPoseUpdate(): Abnormal Motion State!" << endl;
            new_pose = old_pose;
            break;
    }
    
    /********************************************************/
    //clock_t time_end = clock();
    //Total_Runtime += time_end-time_start;
    //printf("ImuPoseUpdate_Basic Average Runtime: %1.2f us.\n", (float)Total_Runtime/count_FunctionCall);
    // 2017-01-03: This Function Can Work
    return new_pose;
}
static pose_t ImuPoseUpdate_Advance( pose_t old_pose, unsigned char RobotMotionState, float curr_angle, float delta_disL, float delta_disR )
{
    // TODO
}


pose_t ImuPoseUpdate( pose_t old_pose, unsigned char RobotMotionState, float curr_angle, float delta_disL, float delta_disR )
{
    //return ImuPoseUpdate_Advance( old_pose, RobotMotionState, curr_angle, delta_disL, delta_disR );
    return ImuPoseUpdate_Basic( old_pose, RobotMotionState, curr_angle, delta_disL, delta_disR );
}

point_t TF_Coordinator( point_t OldPosition, float Delta_X, float Delta_Y, float Delta_Theta, float lamda )
{
    point_t NewPosition;

    /*
    float c = lamda * cosf( Delta_Theta * K );
    float d = lamda * sinf( Delta_Theta * K );
    NewPosition.x = Delta_X + c*OldPosition.x + d*OldPosition.y;
    NewPosition.y = Delta_X - d*OldPosition.x + c*OldPosition.y;
    */
    // Or
    NewPosition.x =  lamda*(OldPosition.x * cosf(Delta_Theta * K) - OldPosition.y * sinf(Delta_Theta * K) ) + Delta_X;
    NewPosition.y =  lamda*(-OldPosition.x * sinf(Delta_Theta * K) + OldPosition.y * cosf(Delta_Theta * K) ) + Delta_Y;

    return NewPosition;
}