#include "CommandGenerator.h"
#include <cmath>

static unsigned short int CMD_SerialNum = 1000;
static unsigned char CMD_DefaultPrio = 1;

const float Safty_MoveBack_Length = 50; // 50 mm


MCB_t GetMotionCommand( pose_t curr_pose, pose_t aim_pose, int *flag )
{
    //return GetMotionCommand_Basic( cur_pose, aim_pose );
    MCB_t Res = GetMotionCommand_V20170308( curr_pose, aim_pose, flag);
    return Res;
}

MCB_t GetMotionCommand_Basic( pose_t cur_pose, pose_t aim_pose )
{
    CMD_SerialNum ++;
    MCB_t Res_cmd;
    Res_cmd.serialnum = CMD_SerialNum;
    Res_cmd.priority  = CMD_DefaultPrio;
    Res_cmd.SetSpeed = 800;
    Res_cmd.SetAngSpeed = 800;

    /*
    if ( Is_Postion_Equal( cur_pose, aim_pose ) )
    {
        Res_cmd.cmd_move = CMD_MOVE_Stop;
        return Res_cmd;
    }*/
    // Get the motion Vector( m_x, m_y )
    float m_x = aim_pose.x-cur_pose.x;
    float m_y = aim_pose.y-cur_pose.y;

    // Calculate the motion vector length and angle
    float m_length = sqrt( m_x*m_x+m_y*m_y );

    if ( Is_Length_Equal( 0.0, m_length ) )
    {
        float delta_theta = aim_pose.theta - cur_pose.theta;

        if ( delta_theta >= -360 && delta_theta < -180 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetAngle = 100 * (delta_theta + 360);
        }
        else if ( delta_theta >= -180 && delta_theta < 0 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetAngle = 100 * ( -delta_theta );
        }
        else if ( delta_theta >= 0 && delta_theta < 180 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetAngle = 100 * delta_theta ;
        }
        else if ( delta_theta >= 180 && delta_theta <= 360 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetAngle = 100 * ( 360 - delta_theta );
        }
        else
        {
            cout << "Input Parameter Error!" << endl;
            cout << "delta_theta=" << delta_theta  << endl;
        }
        Res_cmd.SetDis = 0;
        return Res_cmd;
    }
    //cout << "Motion Vector: " << m_x << ", " << m_y << endl;
    float m_angle = atan2f( m_y, m_x ) / K;
    //cout << "Motion Vector Angle: " << m_angle << endl;

    if ( Is_Angle_Equal( m_angle, cur_pose.theta ) )
    {
        Res_cmd.cmd_move = CMD_MOVE_Forward;
        Res_cmd.SetDis   = m_length * 2.5; // Trans From unit mm to cnt
        Res_cmd.SetAngle = 0;
        return Res_cmd;
    }
    
    float delta_theta = m_angle - cur_pose.theta;
    delta_theta = delta_theta < -360? delta_theta+360 : delta_theta;
    delta_theta = delta_theta > 360? delta_theta-360 : delta_theta;

    if ( delta_theta >= -360 && delta_theta < -180 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
        Res_cmd.SetAngle = 100 * (delta_theta + 360);
    }
    else if ( delta_theta >= -180 && delta_theta < 0 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
        Res_cmd.SetAngle = 100 * ( -delta_theta );
    }
    else if ( delta_theta >= 0 && delta_theta < 180 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
        Res_cmd.SetAngle = 100 * delta_theta ;
    }
    else if ( delta_theta >= 180 && delta_theta <= 360 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
        Res_cmd.SetAngle = 100 * ( 360 - delta_theta );
    }
    else
    {
        cout << "Input Parameter Error!" << endl;
        cout << "delta_theta=" << delta_theta  << endl;
    }
    Res_cmd.SetDis = 0;
    return Res_cmd;
}

MCB_t GetMotionCommand_V20170302( pose_t cur_pose, pose_t aim_pose )
{
    CMD_SerialNum ++;
    MCB_t Res_cmd;
    Res_cmd.serialnum = CMD_SerialNum;
    Res_cmd.priority  = CMD_DefaultPrio;
    Res_cmd.SetSpeed = 800;
    Res_cmd.SetAngSpeed = 800;

    /*
    if ( Is_Postion_Equal( cur_pose, aim_pose ) )
    {
        // If Reach the aim_pose, the command should be CMD_MOVE_Stop
        Res_cmd.cmd_move = CMD_MOVE_Stop;
        Res_cmd.SetDis = 0;
        Res_cmd.SetAngle = 0;
        Res_cmd.SetSpeed = 0;
        Res_cmd.SetAngSpeed = 0;
        return Res_cmd;
    }
    */

    // Get the motion Vector( m_x, m_y )
    float m_x = aim_pose.x-cur_pose.x;
    float m_y = aim_pose.y-cur_pose.y;

    // Calculate the motion vector length and angle
    float m_length = sqrt( m_x*m_x+m_y*m_y );
    float m_angle = atan2f( m_y, m_x ) / K;
    //cout << "Motion Vector Angle : " << m_angle << endl;
    //cout << "Motion Vector Length: " << m_angle << endl;
    // If the motion vector is short enough

    if ( Is_Length_Equal( 0.0, m_length ) )
    {
        float delta_theta = aim_pose.theta - cur_pose.theta;

        if ( delta_theta >= -360 && delta_theta < -180 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetAngle = 100 * (delta_theta + 360);
        }
        else if ( delta_theta >= -180 && delta_theta < 0 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetAngle = 100 * ( -delta_theta );
        }
        else if ( delta_theta >= 0 && delta_theta < 180 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetAngle = 100 * delta_theta ;
        }
        else if ( delta_theta >= 180 && delta_theta <= 360 )
        {
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetAngle = 100 * ( 360 - delta_theta );
        }
        else
        {
            cout << "Input Parameter Error!" << endl;
            cout << "delta_theta=" << delta_theta  << endl;
        }
        Res_cmd.SetDis = 0;
        return Res_cmd;
    }


    if ( Is_Angle_Equal( m_angle, cur_pose.theta ) )
    {
        Res_cmd.cmd_move = CMD_MOVE_Forward;
        Res_cmd.SetDis   = m_length * 2.5; // Trans From unit mm to cnt
        Res_cmd.SetAngle = 0;
        return Res_cmd;
    }
    
    float delta_theta = m_angle - cur_pose.theta;
    delta_theta = delta_theta < -360? delta_theta+360 : delta_theta;
    delta_theta = delta_theta > 360? delta_theta-360 : delta_theta;

    float tmp = abs(delta_theta)-180;

    if( abs( tmp ) < 5 && m_length <= Safty_MoveBack_Length )
    {
        Res_cmd.cmd_move = CMD_MOVE_Backward;
        Res_cmd.SetDis   = m_length * 2.5; // Trans From unit mm to cnt
        Res_cmd.SetAngle = 0;
        return Res_cmd;
    }

    if ( delta_theta >= -360 && delta_theta < -180 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
        Res_cmd.SetAngle = 100 * (delta_theta + 360);
    }
    else if ( delta_theta >= -180 && delta_theta < 0 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
        Res_cmd.SetAngle = 100 * ( -delta_theta );
    }
    else if ( delta_theta >= 0 && delta_theta < 180 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
        Res_cmd.SetAngle = 100 * delta_theta ;
    }
    else if ( delta_theta >= 180 && delta_theta <= 360 )
    {
        Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
        Res_cmd.SetAngle = 100 * ( 360 - delta_theta );
    }
    else
    {
        cout << "Input Parameter Error!" << endl;
        cout << "delta_theta=" << delta_theta  << endl;
    }
    Res_cmd.SetDis = 0;
    return Res_cmd;
}


// Add by limin at 20170307
// Note-1: add result flag, please check the flag before use the command result returned by this function
//        0 means error command, 1 means correct
// Note-2: 
MCB_t GetMotionCommand_V20170307( pose_t cur_pose, pose_t aim_pose, int *flag )
{
    CMD_SerialNum ++;
    MCB_t Res_cmd;
    Res_cmd.serialnum = CMD_SerialNum;
    Res_cmd.priority  = CMD_DefaultPrio;
    Res_cmd.SetSpeed = 800; // Default speed
    Res_cmd.SetAngSpeed = 800; // default speed
    
    // Get the motion Vector( m_x, m_y )
    float m_x = aim_pose.x-cur_pose.x;
    float m_y = aim_pose.y-cur_pose.y;
    // Calculate the motion vector length and angle
    float m_length = sqrt( m_x*m_x+m_y*m_y );
    float m_angle = atan2f( m_y, m_x ) / K;
    //cout << "Motion Vector Angle : " << m_angle << endl;
    //cout << "Motion Vector Length: " << m_angle << endl;
    
    // Half an grid size
    if( m_length < 10 ) // If motion length is very small, only execute rotation motion
    {
        cout << "Motion Vector is too small, just rotate is Ok!" << endl;
        float delta_theta = aim_pose.theta - cur_pose.theta;
        delta_theta = delta_theta <= 180 ? delta_theta : delta_theta-360;
        delta_theta = delta_theta >=-180 ? delta_theta : delta_theta+360;
        if( delta_theta < 0 && delta_theta >= -180 )
        {
            // turn right
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*fabs(delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta >=0 && delta_theta <= 180 )
        {
            // turn left
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*delta_theta;
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line should never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }
    }
    else if( m_length >= 10 && m_length <= 50 )
    {
        float delta_theta1 =  m_angle-cur_pose.theta;
        delta_theta1 = delta_theta1 <= 180 ? delta_theta1 : delta_theta1-360;
        delta_theta1 = delta_theta1 >=-180 ? delta_theta1 : delta_theta1+360;

        float delta_theta2 = aim_pose.theta - m_angle;
        delta_theta2 = delta_theta2 <= 180 ? delta_theta2 : delta_theta2-360;
        delta_theta2 = delta_theta2 >=-180 ? delta_theta2 : delta_theta2+360;

        float delta_total = aim_pose.theta - cur_pose.theta;
        delta_total = delta_total <= 180 ? delta_total : delta_total-360;
        delta_total = delta_total >=-180 ? delta_total : delta_total+360;
        
        if( delta_theta1 <= 5 && delta_theta1 >= -5 )
        {
            // just move forward
            Res_cmd.cmd_move = CMD_MOVE_Forward;
            Res_cmd.SetDis   = m_length * 2.474;// * cos(delta_theta1*K) ; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 >= 175 || delta_theta1 <= -175 )
        {
            // just move backward
            Res_cmd.cmd_move = CMD_MOVE_Backward;
            Res_cmd.SetDis   = m_length  * 2.474; //* fabs( cos(delta_theta1*K) ); // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 < -5 && delta_theta1 >= -90 )
        {
            // turn right
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(-delta_total);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 > 5 && delta_theta1 <= 90 )
        {
            // turn left
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(delta_total);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 < -90 && delta_theta1 > -175 )
        {
            // turn left and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180+delta_total);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 > 90 && delta_theta1 < 175 )
        {
            // turn right and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180-delta_total);
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line will never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }

    }
    else if( m_length <= 500 && m_length > 50 ) // if motion vector length middle: move backward is safe
    {
        float delta_theta =  m_angle-cur_pose.theta;
        delta_theta = delta_theta <= 180 ? delta_theta : delta_theta-360;
        delta_theta = delta_theta >=-180 ? delta_theta : delta_theta+360;
        if ( delta_theta >= -2 && delta_theta <= 2 )
        {
            // move forward
            Res_cmd.cmd_move = CMD_MOVE_Forward;
            Res_cmd.SetDis   = m_length * 2.474; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta > 2 && delta_theta < 90  )
        {
            // turn left and move forward
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*delta_theta;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta >= 90 && delta_theta < 178 )
        {
            // turn right and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180-delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta>= 178 || delta_theta <= -178 )
        {
            // move backward
            Res_cmd.cmd_move = CMD_MOVE_Backward;
            Res_cmd.SetDis   = m_length * 2.474; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta < -2 && delta_theta >-90 )
        {
            // turn right and move forward
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(-delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta <= -90 && delta_theta > -178 )
        {
            // turn left and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180+delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line should never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }
    }
    else // motion vector is long and move backward is unsafe
    {
        float delta_theta =  m_angle-cur_pose.theta;
        delta_theta = delta_theta <= 180 ? delta_theta : delta_theta-360;
        delta_theta = delta_theta >=-180 ? delta_theta : delta_theta+360;
        if( delta_theta >= -2 && delta_theta <= 2 )
        {
            // move forward
            Res_cmd.cmd_move = CMD_MOVE_Forward;
            Res_cmd.SetDis   = m_length * 2.474; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta < -2 && delta_theta >= -180 )
        {
            // turn right
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*fabs(delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta > 2 && delta_theta <= 180 )
        {
            // turn left
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*delta_theta;
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line should never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }
    }
}

// Add by limin at 20170308
// Note-1: add result flag, please check the flag before use the command result returned by this function
//        0 means error command, 1 means correct
// Note-2: Repair a few bug in V20170307
MCB_t GetMotionCommand_V20170308( pose_t cur_pose, pose_t aim_pose, int *flag )
{
    CMD_SerialNum ++;
    MCB_t Res_cmd;
    Res_cmd.serialnum = CMD_SerialNum;
    Res_cmd.priority  = CMD_DefaultPrio;
    Res_cmd.SetSpeed = 800; // Default speed
    Res_cmd.SetAngSpeed = 800; // default speed
    
    // Get the motion Vector( m_x, m_y )
    float m_x = aim_pose.x-cur_pose.x;
    float m_y = aim_pose.y-cur_pose.y;
    // Calculate the motion vector length and angle
    float m_length = sqrt( m_x*m_x+m_y*m_y );
    float m_angle = atan2f( m_y, m_x ) / K;
    //cout << "Motion Vector Angle : " << m_angle << endl;
    //cout << "Motion Vector Length: " << m_angle << endl;
    
    // Half an grid size
    if( m_length < 10 ) // If motion length is very small, only execute rotation motion
    {
        /*
        cout << "Motion Vector is too small, just rotate is Ok!" << endl;
        cout << "Aim pose: " << aim_pose << endl;
        cout << "cur_pose: " << cur_pose << endl; 
        cout << "Motion Vector Angle : " << m_angle << endl;
        cout << "Motion Vector Length: " << m_length << endl;
        */
        float delta_theta = aim_pose.theta - cur_pose.theta;
        delta_theta = delta_theta <= 180 ? delta_theta : delta_theta-360;
        delta_theta = delta_theta >=-180 ? delta_theta : delta_theta+360;
        if( delta_theta < 0 && delta_theta >= -180 )
        {
            // turn right
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*fabs(delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta >=0 && delta_theta <= 180 )
        {
            // turn left
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*delta_theta;
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line should never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }
    }
    else if( m_length >= 10 && m_length <= 50 )
    {
        // In a short length, here must be designed carefully!
        /* // if debug
        /*
        cout << "Be care full!" << endl;
        cout << "Aim pose: " << aim_pose << endl;
        cout << "cur_pose: " << cur_pose << endl; 
        cout << "Motion Vector Angle : " << m_angle << endl;
        cout << "Motion Vector Length: " << m_length << endl;
        */
        float delta_theta1 =  m_angle-cur_pose.theta;
        delta_theta1 = delta_theta1 <= 180 ? delta_theta1 : delta_theta1-360;
        delta_theta1 = delta_theta1 >=-180 ? delta_theta1 : delta_theta1+360;
        /*
        float delta_theta2 = aim_pose.theta - m_angle;
        delta_theta2 = delta_theta2 <= 180 ? delta_theta2 : delta_theta2-360;
        delta_theta2 = delta_theta2 >=-180 ? delta_theta2 : delta_theta2+360;
        */
        /*
        float delta_total = aim_pose.theta - cur_pose.theta;
        delta_total = delta_total <= 180 ? delta_total : delta_total-360;
        delta_total = delta_total >=-180 ? delta_total : delta_total+360;
        */
        if( delta_theta1 <= 5 && delta_theta1 >= -5 )
        {
            // just move forward
            Res_cmd.cmd_move = CMD_MOVE_Forward;
            Res_cmd.SetDis   = m_length * 2.474;// * cos(delta_theta1*K) ; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 >= 175 || delta_theta1 <= -175 )
        {
            // just move backward
            Res_cmd.cmd_move = CMD_MOVE_Backward;
            Res_cmd.SetDis   = m_length  * 2.474; //* fabs( cos(delta_theta1*K) ); // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 < -5 && delta_theta1 >= -90 )
        {
            // turn right
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(-delta_theta1);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 > 5 && delta_theta1 <= 90 )
        {
            // turn left
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(delta_theta1);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 < -90 && delta_theta1 > -175 )
        {
            // turn left and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180+delta_theta1);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta1 > 90 && delta_theta1 < 175 )
        {
            // turn right and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180-delta_theta1);
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line will never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }

    }
    else if( m_length <= 500 && m_length > 50 ) 
    {
        // if motion vector length middle: move backward is safe
        float delta_theta =  m_angle-cur_pose.theta;
        delta_theta = delta_theta <= 180 ? delta_theta : delta_theta-360;
        delta_theta = delta_theta >=-180 ? delta_theta : delta_theta+360;
        if ( delta_theta >= -2 && delta_theta <= 2 )
        {
            // move forward
            Res_cmd.cmd_move = CMD_MOVE_Forward;
            Res_cmd.SetDis   = m_length * 2.474; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta > 2 && delta_theta < 90  )
        {
            // turn left and move forward
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*delta_theta;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta >= 90 && delta_theta < 178 )
        {
            // turn right and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180-delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta>= 178 || delta_theta <= -178 )
        {
            // move backward
            Res_cmd.cmd_move = CMD_MOVE_Backward;
            Res_cmd.SetDis   = m_length * 2.474; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta < -2 && delta_theta >-90 )
        {
            // turn right and move forward
            Res_cmd.cmd_move = CMD_MOVE_TurnRight;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(-delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta <= -90 && delta_theta > -178 )
        {
            // turn left and move backward
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft;
            Res_cmd.SetDis = 0;
            Res_cmd.SetAngle = 100*(180+delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line should never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }
    }
    else 
    {
        // motion vector is long and move backward is unsafe
        float delta_theta =  m_angle-cur_pose.theta;
        delta_theta = delta_theta <= 180 ? delta_theta : delta_theta-360;
        delta_theta = delta_theta >=-180 ? delta_theta : delta_theta+360;

        if( delta_theta >= -2 && delta_theta <= 2 )
        {
            // move forward
            Res_cmd.cmd_move = CMD_MOVE_Forward;
            Res_cmd.SetDis   = m_length * 2.474; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 0;
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta < -2 && delta_theta >= -180 )
        {
            // turn right
            Res_cmd.cmd_move = CMD_MOVE_TurnRight ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*fabs(delta_theta);
            *flag = 1;
            return Res_cmd;
        }
        else if( delta_theta > 2 && delta_theta <= 180 )
        {
            // turn left
            Res_cmd.cmd_move = CMD_MOVE_TurnLeft ;
            Res_cmd.SetDis   = 0; // Trans From unit mm to cnt
            Res_cmd.SetAngle = 100*delta_theta;
            *flag = 1;
            return Res_cmd;
        }
        else
        {
            cout << "This line should never reach!" << endl;
            *flag = 0;
            return Res_cmd;
        }
    }
}