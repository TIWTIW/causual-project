#include "RobotTypes.h"

CRobot::CRobot()
{
    // The constructor of class CRobot
    // Initialize the Variables

}
CRobot::~CRobot()
{
    // The destructor of the class CRobot
}

int CRobot::Init( void )
{
    // Communication Devices Initialization
    if( m_UART1.COM_UART_Init( UART1_NAME_str ) != 0 )
    {
        //cout << "Error: Failed to initialize the UART1! " << endl;
        return -1;
    }
    // Robot Variable Initialization
    bzero( &m_vPose, sizeof(pose_t) );
    bzero( &m_imuPose, sizeof(pose_t) );
    bzero( &m_info_sensors, sizeof(sensor_info) );
    bzero( &m_info_MotionState, sizeof(MotionStat_t) );
    bzero( &m_info_MotionRes, sizeof(MotionRes_t) );


    // The CRobot initialization Function
    // Multi-Thread Initialize
    pthread_mutex_init( &m_mutex_UART1_send, NULL );
    pthread_mutex_init( &m_mutex_vPose, NULL );
    pthread_mutex_init( &m_mutex_imuPose, NULL );
    pthread_mutex_init( &m_mutex_info_sensors, NULL );

    //pthread_attr_t pthread_attr;
    //pthread_attr_init( &pthread_attr );
    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    /*
    if( pthread_create( &m_pidDataFuseL0, NULL, pThread_DataFuse_L0, this) != 0)
    {
        perror("Error: Create pThread_DataFuse_L0 Failed!");
        return -1;
    }
    */
    return 0;
}

int CRobot::cmd_SystemInit( void )
{
    // Step 1: Initialize the ARM End
    if( this->Init() )
    {
        cout << "Failed to Initialize the ARM End!" << endl;
        return -1;
    }
    // Step 2: Initialize the STM32 End
    pthread_mutex_unlock( &m_mutex_UART1_send );
    if( m_UART1.COM_System( CMD_SYS_Init ) != 0 )
    {
        cout << "Failed to Initialize the STM32 System!" << endl;
        pthread_mutex_unlock( &m_mutex_UART1_send );
        return -1;
    }
    //cout << "STM32 System Initialize Command has been Sent!" << endl;
    pthread_mutex_unlock( &m_mutex_UART1_send );

    return 0;
}


int CRobot::cmd_SystemSleep( void )
{
    // Step 1: Sleep the STM32 End
    pthread_mutex_lock( &m_mutex_UART1_send );
    if( m_UART1.COM_System( CMD_SYS_Sleep ) != 0 )
    {
        cout << "Failed to Sleep the STM32 System!" << endl;
        pthread_mutex_unlock( &m_mutex_UART1_send );
        return -1;
    }
    pthread_mutex_unlock( &m_mutex_UART1_send );
    // Step 2: Sleep the ARM End
    if( 0 )
    {
        cout << "Failed to Sleep the ARM End!" << endl;
        return -1;
    }

    return 0;
}
int CRobot::cmd_SystemShut( void )
{
    // Step 1: Shutdown the STM32 End
    pthread_mutex_lock( &m_mutex_UART1_send );
    if( m_UART1.COM_System( CMD_SYS_Shut ) != 0 )
    {
        cout << "Failed to Shutdown the STM32 System!" << endl;
        pthread_mutex_unlock( &m_mutex_UART1_send );
        return -1;
    }
    pthread_mutex_unlock( &m_mutex_UART1_send );
    // Step 2: Shutdown the ARM End
    if( 0 )
    {
        cout << "Failed to Shutdown the ARM End!" << endl;
        return -1;
    }

    return 0;
}
int CRobot::cmd_Motion( MCB_t cmd_motion )
{
    // Check the Motion Command Block

    // Send the Motion Command
    pthread_mutex_lock( &m_mutex_UART1_send );
    if( m_UART1.COM_Motion( cmd_motion ) != 0)
    {
        cout << "Failed to Send the Motion Command: " << endl;
        pthread_mutex_unlock( &m_mutex_UART1_send );
        return -1;
    }
    pthread_mutex_unlock( &m_mutex_UART1_send );

    return 0;
}

// Sub-objects Set and Get Functions
void CRobot::SetvPose( pose_t vPose )
{
    pthread_mutex_lock( &m_mutex_vPose );
    m_vPose = vPose;
    pthread_mutex_unlock( &m_mutex_vPose );
}
pose_t CRobot::GetvPose( void )
{
    pthread_mutex_lock( &m_mutex_vPose );
    pose_t vPose = m_vPose;
    pthread_mutex_unlock( &m_mutex_vPose );
    return vPose;
}
void CRobot::SetimuPose( pose_t imuPose )
{
    pthread_mutex_lock( &m_mutex_imuPose );
    m_imuPose = imuPose;
    pthread_mutex_unlock( &m_mutex_imuPose );
}
pose_t CRobot::GetimuPose( void )
{
    pthread_mutex_lock( &m_mutex_imuPose );
    pose_t imuPose = m_imuPose;
    pthread_mutex_unlock( &m_mutex_imuPose );
    return imuPose;
}

void CRobot::SetSensors( sensor_info sensor_info )
{
    pthread_mutex_lock( &m_mutex_info_sensors );
    m_info_sensors = sensor_info;
    pthread_mutex_unlock( &m_mutex_info_sensors );
}

sensor_info CRobot::GetSensors( void )
{
    pthread_mutex_lock( &m_mutex_info_sensors );
    sensor_info info_sensors = m_info_sensors;
    pthread_mutex_unlock( &m_mutex_info_sensors );
    return info_sensors;
}

void CRobot::SetMotionState( MotionStat_t motion_state )
{
    pthread_mutex_lock( &m_mutex_info_motionstate );
    m_info_MotionState = motion_state;
    pthread_mutex_unlock( &m_mutex_info_motionstate );
}
void CRobot::SetMotionRes( MotionRes_t motion_res )
{
    pthread_mutex_lock( &m_mutex_info_motionres );
    m_info_MotionRes = motion_res;
    pthread_mutex_unlock( &m_mutex_info_motionres );
}

MotionStat_t CRobot::GetMotionState( void )
{
    pthread_mutex_lock( &m_mutex_info_motionstate );
    MotionStat_t info_motionstate = m_info_MotionState;
    pthread_mutex_unlock( &m_mutex_info_motionstate );
    return info_motionstate;
}
MotionRes_t CRobot::GetMotionRes( void )
{
    pthread_mutex_lock( &m_mutex_info_motionres );
    MotionRes_t info_motionres = m_info_MotionRes;
    pthread_mutex_unlock( &m_mutex_info_motionres );
    return info_motionres;
}

/*
void* CRobot::pThread_DataFuse_L0(void *pParam)
{
    if( pParam == NULL )
    {
        cout << "Error: The Entry Parameter of CRobot::pThread_DataFuse_L0() should be a CRobot Variable!" << endl;
        // Through Error
    }
    CRobot *pThis = (CRobot*)pParam;
    cout << "Info: CRobot::pThread_DataFuse_L0 Started!" << endl;

    // Temp Variable Used to Receive Data From the UART1
    sensor_info sensor_data;
    MotionStat_t motion_stat;
    MotionRes_t motion_res;

    bzero( &sensor_data, sizeof(sensor_info) );
    bzero( &motion_stat, sizeof(MotionStat_t) );
    bzero( &motion_res, sizeof(MotionRes_t) );

    while( true )
    {
        // Receive the Frame From the UART
        switch( pThis->m_UART1.Recv( sensor_data, motion_stat, motion_res ) )
        {
            case 1: // No New Frame comes
              //cout << "Warning: No New Frame Comes!" << endl;
              break;
            case -1: // Frame Broken
              cout << "Error: UART1 Frame Broken!" << endl;
              break;
            case 0: // Receive New Frame Correctly
              pThis->m_info_sensors = sensor_data;
              //cout << sensor_data << endl;
              pThis->m_info_MotionState = motion_stat;
              pThis->m_info_MotionRes = motion_res;
              // Update the imuPose Through sensors data
              // pThis->m_imuPose = Location_IMU();
              // Post the Condition Variable
              break;
            default:
              break;
        }
        usleep(8000);
    }
}
*/