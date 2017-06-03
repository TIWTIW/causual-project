
/**************************************************************/
// This file contains the functions used to format the data output.
// Just used for logs and debug.
/**************************************************************/

#include "COM_UserTypes.h"
#include "COM_Protocol.h"



/***************************************************************/
// Data Structure Format Output
// Robot Pose Format Output
ostream&  operator << ( ostream&  os, const pose_t &t )
{
    os << "(" << t.x << ", " << t.y << ", " << t.theta << ")";
    return os;
}
ofstream& operator << ( ofstream& os, const pose_t &t )
{
    os << "(" << t.x << ", " << t.y << ", " << t.theta << ")";
    return os;
}

// Robot Sensor Data Format Output
ostream&  operator << ( ostream&  os, const sensor_info &t )
{
    os << "Robot Sensor Data: "
       << "\n\tIMU7011 Angle: " << t.IMU7011_Angle
       << "\n\tIMU7011 Angle Rate:" << t.IMU7011_AngleRate
       << "\n\tGP2Y0A(L, R): " << t.GP2Y0A_Left << "--" << t.GP2Y0A_Right
       << "\n\tHall Total: " << t.Hall_Left_Total << "--" << t.Hall_Right_Total
       << "\n\tDrop: " << (int)(t.SEN1 & 0x0F)
       << "\n\tCompact: " << (int)(t.SEN1 & 0xC0)
       << "\n\tSuspend: " << (int)(t.SEN1 & 0x30)
       << endl;
       return os;
}
ofstream& operator << ( ofstream& os, const sensor_info &t )
{
    os << "Robot Sensor Data: "
       << "\n\tIMU7011 Angle: " << t.IMU7011_Angle
       << "\n\tIMU7011 Angle Rate:" << t.IMU7011_AngleRate
       << "\n\tGP2Y0A(L, R): " << t.GP2Y0A_Left << "--" << t.GP2Y0A_Right
       << "\n\tHall Total: " << t.Hall_Left_Total << "--" << t.Hall_Right_Total
       << "\n\tDrop: " << (int)(t.SEN1 & 0x0F)
       << "\n\tCompact: " << (int)(t.SEN1 & 0xC0)
       << "\n\tSuspend: " << (int)(t.SEN1 & 0x30)
       << endl;
       return os;
}




ostream& operator << ( ostream& os, const Hall_Encoder_Cnt_t &t )
{
    os << "Hall Data( L - R ): ( " << t.cntL << " - " << t.cntR << " )." << endl;
    return os;
}

ofstream& operator << ( ofstream& os, const Hall_Encoder_Cnt_t &t )
{
    os << "Hall Data( L - R ): ( " << t.cntL << " - " << t.cntR << " )." << endl;
    return os;
}

ostream& operator << ( ostream& os, const MPU6050_t &t )
{
    os << "MPU Data( Y-R-P ): ( " << t.AngY << "-" << t.AngR << "-" << t.AngP << " )." << endl;
    return os;
}
ofstream& operator << ( ofstream& os, const MPU6050_t &t )
{
    os << "MPU Data( Y-R-P ): ( " << t.AngY << "-" << t.AngR << "-" << t.AngP << " )." << endl;
    return os;
}

ostream& operator << ( ostream& os, const Motion_State_t &t )
{
    os << "Motion State: \n\t";
    switch( t.State )
    {
        case STAT_MOVE_STOP:
            os << "State: STOP"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_FORWARD:
            os << "State: Forward"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_BACKWARD:
            os << "State: Backward"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_TURNLEFT:
            os << "State: Turnleft"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_TURNRIGHT:
            os << "State: Turnright"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        default:
            os << "State: Unknown State"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
    }
    return os;
}
ofstream& operator << ( ofstream& os, const Motion_State_t &t )
{
    os << "Motion State: \n\t";
    switch( t.State )
    {
        case STAT_MOVE_STOP:
            os << "State: STOP"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_FORWARD:
            os << "State: Forward"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_BACKWARD:
            os << "State: Backward"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_TURNLEFT:
            os << "State: Turnleft"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        case STAT_MOVE_TURNRIGHT:
            os << "State: Turnright"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
        default:
            os << "State: Unknown State"
               << "\n\tSpeed: " << t.Speed
               << "\n\tAngSpeed: " << t.AngSpeed
               << "\n\tAccel: " << t.Accel
               << endl;
            break;
    }
    return os;
}


ostream& operator << ( ostream& os, const Motion_Execute_Res_t &t )
{
    os << "Serial Number: " << t.serialnum << "\t\t";
    switch( t.state )
    {
        case ME_STATE_Init:
            os << "Execute State: Init" << endl;
            break;
        case ME_STATE_Running:
            os << "Execute State: Running" << endl;
            break;
        case ME_STATE_Done:
            os << "Execute State: Done" << endl;
            break;
        case ME_STATE_ABORT1:
            os << "Execute State: Abort For New Command" << endl;
            break;
        case ME_STATE_ABORT2:
            os << "Execute State: Abort For Drop" << endl;
            break;
        case ME_STATE_ABORT3:
            os << "Execute State: Abort For Suspend" << endl;
            break;
        case ME_STATE_ABORT4:
            os << "Execute State: Abort For Compact" << endl;
            break;
    }
    return os;
}
ofstream& operator << ( ofstream& os, const Motion_Execute_Res_t &t )
{
    os << "Serial Number: " << t.serialnum << "\t\t";
    switch( t.state )
    {
        case ME_STATE_Init:
            os << "Execute State: Init" << endl;
            break;
        case ME_STATE_Running:
            os << "Execute State: Running" << endl;
            break;
        case ME_STATE_Done:
            os << "Execute State: Done" << endl;
            break;
        case ME_STATE_ABORT1:
            os << "Execute State: Abort For New Command" << endl;
            break;
        case ME_STATE_ABORT2:
            os << "Execute State: Abort For Drop" << endl;
            break;
        case ME_STATE_ABORT3:
            os << "Execute State: Abort For Suspend" << endl;
            break;
        case ME_STATE_ABORT4:
            os << "Execute State: Abort For Compact" << endl;
            break;
    }
    return os;
}

ostream& operator << ( ostream& os, const Motion_Control_Block_t &t )
{
    os << "Motion Control Block Details: "
       << "\n\tSerial Number: " << t.serialnum
       << "\n\tPriority: " << (int)t.priority
       << "\n\tMotion Command: " << (int)t.cmd_move
       << "\n\tParameter Speed: " << t.SetSpeed
       << "\n\tParameter Angle Speed: " << t.SetAngSpeed
       << "\n\tParameter Distance: " << t.SetDis
       << "\n\tParameter Angle: " << t.SetAngle
       << endl;
    return os;
}
ofstream& operator << ( ofstream& os, const Motion_Control_Block_t &t )
{
    os << "Motion Control Block Details: "
       << "\n\tSerial Number: " << t.serialnum
       << "\n\tPriority: " << t.priority
       << "\n\tMotion Command: " << (int)t.cmd_move
       << "\n\tParameter Speed: " << t.SetSpeed
       << "\n\tParameter Angle Speed: " << t.SetAngSpeed
       << "\n\tParameter Distance: " << t.SetDis
       << "\n\tParameter Angle: " << t.SetAngle
       << endl;
    return os;
}

ostream& operator << ( ostream& os, const UART_Stat_Info_t &t )
{
    os << "UART Communication Statistics Details: "
       << "\n\tCorrectRate: " << (float)t.cnt_correct/(t.cnt_correct + t.cnt_error) * 100 << "%"
       << "\n\tFrame Received: " << t.cnt_recv
       << "\n\tFrame Sent: " <<t.cnt_send
       << "\n\tFrame Sent Count:"
       << "\n\t\t"
       << endl;
    return os;
}
ofstream& operator << ( ofstream& os, const UART_Stat_Info_t &t )
{
    os << "UART Communication Statistics Details: "
       << "\n\tCorrectRate: " << (float)t.cnt_correct/(t.cnt_correct + t.cnt_error) * 100 << "%"
       << "\n\tFrame Received: " << t.cnt_recv
       << "\n\tFrame Sent: " <<t.cnt_send
       << "\n\tFrame Sent Count:"
       << "\n\t\t"
       << endl;
    return os;
}
