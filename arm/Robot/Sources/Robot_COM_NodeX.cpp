
#include "Robot_COM_NodeX.h"
#include <opencv2/features2d/features2d.hpp>
#include "logmodule/logmodule.hpp"
#include "generalfunction/Myfunctions.h"

CRobot CCRobot;
static MCB_t cmd_motion;
static unsigned short int MotionSerialNum = 1000;

MCB_t GetCmdMotion( void )
{
    MCB_t cmd_motion;
    // For Testing
    cmd_motion.serialnum = 1000;
    cmd_motion.priority  = 0000;
    cmd_motion.cmd_move  = CMD_MOVE_Forward;
    cmd_motion.SetSpeed  = 400;
    cmd_motion.SetDis    = 000;
    cmd_motion.SetAngSpeed = 000;
    cmd_motion.SetAngle  = 000;
    // Get the CMD From the message queue
    return cmd_motion;
}

void Handler_Signals_Main(int signum, siginfo_t *info, void *oldact)
{
    
    //MCB_t cmd_motion = GetCmdMotion();
    MotionSerialNum++;
    cmd_motion.serialnum = MotionSerialNum;
    cmd_motion.SetSpeed = 800;
    printf("Received Signal %d from process %d with parameter %d \n ", signum, (int)(info->si_pid), info->si_value.sival_int );
    cout << "Serial Number: " << cmd_motion.serialnum << endl;
    int motionParameter = info->si_value.sival_int;
    switch( signum )
    {
        case SIG_CMD_MOTION_FORWARD:
            cmd_motion.cmd_move = motionParameter>0 ? CMD_MOVE_Forward : CMD_MOVE_Backward;
            cmd_motion.SetDis = 2.5 * abs(motionParameter);
            ///*
            if( CCRobot.cmd_Motion( cmd_motion ) != 0)
            {
                cout << "Failed to Send the Motion Command: " << endl;
            }
            //cout << cmd_motion << endl;
            //*/         
            //cout << "Motion Command Has been Sent! \n" << cmd_motion << endl;
            break;
        case SIG_CMD_MOTION_TURNLEFT:
            cmd_motion.cmd_move = motionParameter>0 ? CMD_MOVE_TurnLeft : CMD_MOVE_TurnRight;
            cmd_motion.SetAngle = 100 * abs(motionParameter);
            ///*
            if( CCRobot.cmd_Motion( cmd_motion ) != 0)
            {
                cout << "Failed to Send the Motion Command: " << endl;
            }
            //cout << cmd_motion << endl;
            //*/

            //cout << "Motion Command Has been Sent! \n" << cmd_motion << endl;
            break;
        case SIG_CMD_MOTION_STOP:
            cmd_motion.cmd_move = CMD_MOVE_Stop;
            if( CCRobot.cmd_Motion( cmd_motion ) != 0)
            {
                cout << "Failed to Send the Motion Command: " << endl;
            }
            break;
        default :
            printf("Received Signal %d Has No Handlers!\n", signum );
            break;
    }
}

void *pThread_SendCommand( void *argv )
{
    usleep(100000);

    log_t log("./logs/pThread_SendCommand"+time_filename_str(), "UART Send Command By LiMin ");

    mq_unlink( MQ_Command );
    mqd_t mq_cmd = mq_open( MQ_Command, O_RDWR | O_CREAT, FILE_MODE, NULL);
    if ( mq_cmd == -1 )
    {
        perror("Error-Level-0: Failed to Create Message Queue: /MQ_Command");
        exit( -1 );
    }
    log.fs(INFO) << "Init: MQ_Command Created!" << endl;

    struct mq_attr mqCMD_attr;
    mq_getattr(mq_cmd, &mqCMD_attr);
    unsigned int prio;
    void *buff;
    buff = malloc(mqCMD_attr.mq_msgsize);

    MCB_t CommandToSend;

    log.fs(INFO) << "Info-Level-0: pThread_SendCommand Start to Work!" << endl;
    
    unsigned int cnt_cmdStop = 0;
    unsigned int cnt_cmdForward = 0;
    unsigned int cnt_cmdBackward = 0;
    unsigned int cnt_cmdTurnleft = 0;
    unsigned int cnt_cmdTurnright = 0;
    unsigned int cnt_cmdUnknown = 0;
    unsigned int cnt_cmdTotal = 0;
    unsigned int cnt_ErrMQRecv = 0;
    double Start_Runtime = (double)cv::getTickCount()/cv::getTickFrequency();
    double Total_Runtime = 0;
    int tickCNT = 0;

    while( true )
    {
        if ( mq_receive(mq_cmd, (char*)buff, mqCMD_attr.mq_msgsize, &prio)==-1 )
        {
            cnt_ErrMQRecv++;
            log.fs(FATAL) << "Failed to Receive Command From Level-1" << endl;
            perror("Warning-Level-0: Failed to Receive Command From Level-1");
        }
        else
        {
            CommandToSend = *(MCB_t*)buff;
            //cout << "Debug-Level-0: Received Command--" << CommandToSend.serialnum << endl;
            if( CCRobot.cmd_Motion( CommandToSend ) != 0)
            {
                log.fs(FATAL) << "Failed to Send the Motion Command: " << endl;
            }

            // Performance statistics information
            switch( CommandToSend.cmd_move  )
            {
                case CMD_MOVE_Stop:
                    cnt_cmdStop++;
                    break;
                case CMD_MOVE_Forward:
                    cnt_cmdForward++;
                    break;
                case CMD_MOVE_Backward:
                    cnt_cmdBackward++;
                    break;
                case CMD_MOVE_TurnLeft:
                    cnt_cmdTurnleft++;
                    break;
                case CMD_MOVE_TurnRight:
                    cnt_cmdTurnright++;
                    break;
                default:
                    cnt_cmdUnknown++;
                    break;
            }
            cnt_cmdTotal ++;
        } // --if--
        Total_Runtime = (double)cv::getTickCount()/cv::getTickFrequency() - Start_Runtime;
        tickCNT++;
        if(tickCNT%10==0)
        {
            log.fs(INFO) << "Command statistics information:"
                         << "\n\t Total CMD count   : " << cnt_cmdTotal
                         << "\n\t Send CMD Frequency: " << cnt_cmdTotal/Total_Runtime
                         << "\n\t Stop Command      : " << cnt_cmdStop <<"("<< 100*(float)cnt_cmdStop/cnt_cmdTotal << "%)"
                         << "\n\t Forward command   : " << cnt_cmdForward <<"("<< 100*(float)cnt_cmdForward/cnt_cmdTotal << "%)"
                         << "\n\t Backward command  : " << cnt_cmdBackward <<"("<< 100*(float)cnt_cmdBackward/cnt_cmdTotal << "%)"
                         << "\n\t Turn left command : " << cnt_cmdTurnleft <<"("<< 100*(float)cnt_cmdTurnleft/cnt_cmdTotal << "%)"
                         << "\n\t Turn right command: " << cnt_cmdTurnright <<"("<< 100*(float)cnt_cmdTurnright/cnt_cmdTotal << "%)"
                         << "\n\t Unknown command   : " << cnt_cmdUnknown <<"("<< 100*(float)cnt_cmdUnknown/cnt_cmdTotal << "%)"
                         << "\n\t Read MQ Error     : " << cnt_ErrMQRecv
                         << "\n\n" << endl;
                     }
    } //--while--
}

int P_COM_Node0( pid_t L1_pid )
{
    log_t log( "./logs/COM_UART"+time_filename_str(), "Command Update Module");

    if ( CCRobot.cmd_SystemInit() != 0 )
    {
        log.fs(ERROR) << "Failed to initialize the system, program will exit with code -1." << endl;
        //printf("Killing Process %d\n", L1_pid );
        //kill( L1_pid, SIGKILL );
        return -1;
    }

    log.fs(INFO) << "Level-0 Init: System(STM 32) Initialized!" << endl;

    bzero( &cmd_motion, sizeof(MCB_t) );
    // Create a thread to handle the command from high level
    pthread_t m_pid_L0_CommandRecvAndSend;
    if ( pthread_create( &m_pid_L0_CommandRecvAndSend, NULL, pThread_SendCommand, NULL )!=0 )
    {
        log.fs(ERROR) << "Failed To Create pThread_SendCommand, Program will exit with code -1." << endl;
        perror( "Error-Level-0: Failed To Create pThread_SendCommand" );
        return(-1);
    }
    log.fs(INFO) << "Level-0 Init: pThread_SendCommand created!" << endl;
    
    // Create and Initialize the shared memory object
    shm_unlink( shm_msg01 );
    int fd_shm01 = shm_open( shm_msg01, O_RDWR|O_CREAT|O_EXCL, FILE_MODE );
    if( fd_shm01==-1 )
    {
        log.fs(ERROR) << "Failed to create shared memory object, program will exit with code -1." << endl;
        perror( "Error-Level-0: Failed to Create shm_msg01--/shm_node01:" );
        return( -1 );
    }
    if( ftruncate( fd_shm01, sizeof(Robot_msg_node01_t) ) == -1)
    {
        log.fs(ERROR) << "Failed to modify the shared memory size, program will exit with code -1." << endl;
        perror("Error-Level-0: Failed to modify the shared memory size: ");
        return( -1 );
    }
    Robot_msg_node01_t *msg_ptr = (Robot_msg_node01_t*)mmap(NULL, sizeof(Robot_msg_node01_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shm01, 0);
    close( fd_shm01 );
    // Create and Initialize the semaphore
    sem_unlink( sem_msg01 );
    sem_t *mutex;
    mutex = sem_open( sem_msg01, O_CREAT|O_EXCL, FILE_MODE, 1);
    if( mutex == SEM_FAILED )
    {
        log.fs(ERROR) << "Failed to Open the semaphore" << endl;;
        perror(" Error-Level-0: Failed to Open the semaphore--/sem_node01:");
        return( -1 );
    }
    sem_close( mutex );
    log.fs(INFO) << "Level-0 Init: Shared memory object Initialized!" << endl;

    // Signals Received By Main Process Handles Initialization
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    act.sa_sigaction = Handler_Signals_Main;
    if ( sigaction( SIG_CMD_MOTION_FORWARD , &act, NULL ) < 0 )
    {
        perror( "Error-Level-0: Install Signal SIG_CMD_MOTION Failed!" );
        return( -1 );
    }
    log.fs(INFO) << "Level-0 Init: Installed Signal SIG_CMD_MOTION" << endl;
    if ( sigaction( SIG_CMD_MOTION_TURNLEFT , &act, NULL ) < 0 )
    {
        perror( "Error-Level-0: Install Signal SIG_CMD_MOTION Failed!" );
        return( -1 );
    }
    log.fs(INFO) << "Level-0 Init: Installed Signal SIG_CMD_MOTION" << endl;

    sensor_info sensor_data;
    MotionStat_t motion_stat;
    MotionRes_t motion_res;
    bzero( &sensor_data, sizeof(sensor_info) );
    bzero( &motion_stat, sizeof(MotionStat_t) );
    bzero( &motion_res, sizeof(MotionRes_t) );

    //Robot_msg_node01_t *msg_ptr = new Robot_msg_node01_t;
    //int prio = 1;

    // Open the shared memory object and named semaphore
    fd_shm01 = shm_open( shm_msg01, O_RDWR, FILE_MODE );
    if( fd_shm01==-1 )
    {
        log.fs(ERROR) << "Failed to open the share memory object /shm_node01" << endl;
        perror( "Error-Level-0: Failed to Open shm_msg01--/shm_node01:" );
        return( -1 );
    }
    msg_ptr = (Robot_msg_node01_t*)mmap(NULL, sizeof(Robot_msg_node01_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shm01, 0);
    close(fd_shm01);
    mutex = sem_open( sem_msg01, 0 );
    log.fs(INFO) << "Level-0 Init: Variables Initialized!" << endl;

    log.fs(INFO) << "Communication thread at level-0 is working..." << endl;
    
    // UART communication performance statistics
    unsigned int cnt_Err_EmptyFrame = 0;
    unsigned int cnt_Err_BrokenFrame = 0;
    unsigned int cnt_Err_Unknown = 0;
    unsigned int cnt_CorrectFrame = 0;
    unsigned int cnt_TotalFrame = 0;
    double Start_Runtime = (double)cv::getTickCount()/cv::getTickFrequency();
    double Total_Runtime = 0.0;
    int tickCNT = 0; // every 1000 loop print a statistics information
    while( true )
    {
        //switch( 0 ) // Only For off-line Debug
        switch( CCRobot.m_UART1.Recv( sensor_data, motion_stat, motion_res ) )
        {
            case 1: // No New Frame comes
                //cout << "Warning: No New Frame Comes!" << endl;
                cnt_Err_EmptyFrame ++;
                break;
            case -1: // Frame Broken
                log.fs(WARNING) << "Received UART Frame Broken!" << endl;
                cnt_Err_BrokenFrame ++;
                break;
            case 0: // Receive New Frame Correctly
                CCRobot.SetSensors( sensor_data );
                CCRobot.SetMotionState( motion_stat );
                CCRobot.SetMotionRes( motion_res );
                // Send the data to the message queue
                sem_wait( mutex );
                msg_ptr->RobotSensor = sensor_data;
                msg_ptr->RobotState = motion_stat;
                msg_ptr->RobotMotionRes = motion_res;
                sem_post( mutex );

                cnt_CorrectFrame ++;
                break;
            default:
                cnt_Err_Unknown++;
                log.fs(FATAL) << "This Line Should Never be Output!" << endl;
                break;
        }
        /******************************************/
        usleep(5000); // up communication rate is about 47 Hz

        // if debug
        
        cnt_TotalFrame = cnt_CorrectFrame + cnt_Err_BrokenFrame;
        
        Total_Runtime = (double)cv::getTickCount()/cv::getTickFrequency() - Start_Runtime;
        
        tickCNT++;
        if( tickCNT%1000==0 )
        {
            log.fs(INFO) << "\nUART Communication statistics information: " 
                         << "\n\t Device Name:   " << UART1_NAME_str
                         << "\n\t Frequency(Hz): " << (float)cnt_TotalFrame/Total_Runtime
                         << "\n\t Correct Rate(%%) : " << 100*(float)cnt_CorrectFrame/cnt_TotalFrame
                         << "\n\t Empty Rate(%%): " << 100*(float)cnt_Err_EmptyFrame/(cnt_Err_EmptyFrame+cnt_TotalFrame)
                         << "\n\t Broken Rate(%%):" << 100*(float)cnt_Err_BrokenFrame/cnt_TotalFrame
                         << "\n\t Total Runtime(s): " << Total_Runtime
                         << "\n\t Total Frame:   " << cnt_TotalFrame
                         << "\n\t Empty Frame  : " << cnt_Err_EmptyFrame 
                         << "\n\t Broken Frame : " << cnt_Err_BrokenFrame
                         << "\n\t Correct Frame : " << cnt_CorrectFrame
                         << "\n\t Unknown Frame : " << cnt_Err_Unknown
                         << endl;
        }  
    }
}
