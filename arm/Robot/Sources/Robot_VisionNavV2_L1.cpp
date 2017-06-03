
#include "Robot_VisionNavV2.h"
#include "mapping/grid_map_core.h"
#include "mapping/grid_map_coordinate.h"
#include "logmodule/logmodule.hpp"
#include "generalfunction/Myfunctions.h"
#include "test_function.h"


static pid_t L0_pid;
static pid_t L2_pid;
//static unsigned short int MotionSerialNum = 1000;
//static unsigned char LastMotionStatus;

sem_t *mutex_takephoto;
static Mat GetTopFrame( void )
{
    if(getframe.hasinit==0)
    {
        getframe.init();
    }
    Mat image;
    sem_wait(mutex_takephoto);
    cout << "taking top photo..." << endl;
    for (int j=0; j<4; j++)
    {
        image=getframe.getVideoFrameTop();
        if( j>=2 && !image.empty() )
            break;
    }
    sem_post(mutex_takephoto);
    return image;
}
void take_photo( int& flag,Mat& img )
{
    Mat firstimg;
    for(int i=0;i<20;i++)
    {
        firstimg = getframe.getVideoFrameTop();       
        if((i>2)&&!(firstimg.empty()) )
        {
            img = firstimg.clone();
            break;
        }
    }
}

static pthread_mutex_t mutex_Robot_Pose_IMU; 
static struct pose_t Robot_Pose_IMU;
static pose_t GetIMUPose( void )
{
    pthread_mutex_lock( &mutex_Robot_Pose_IMU );
    pose_t ImuPose = Robot_Pose_IMU; 
    pthread_mutex_unlock( &mutex_Robot_Pose_IMU );
    return ImuPose;
}
static void SetIMUPose( pose_t ImuPose )
{
    pthread_mutex_lock( &mutex_Robot_Pose_IMU );
    Robot_Pose_IMU = ImuPose;
    pthread_mutex_unlock( &mutex_Robot_Pose_IMU );
}

static pthread_mutex_t mutex_Robot_Pose_Vision; 
static struct pose_t Robot_Pose_Vision;
static pose_t GetVisionPose( void )
{
    pthread_mutex_lock( &mutex_Robot_Pose_Vision );
    pose_t VisionPose = Robot_Pose_Vision; 
    pthread_mutex_unlock( &mutex_Robot_Pose_Vision );
    return VisionPose;
}
static void SetVisionPose( pose_t VisionPose )
{
    pthread_mutex_lock( &mutex_Robot_Pose_Vision );
    Robot_Pose_Vision = VisionPose;
    pthread_mutex_unlock( &mutex_Robot_Pose_Vision );
}

static pose_t GetPose( void )
{
    return GetIMUPose();
}

static pthread_mutex_t mutex_Robot_SensorData;
static sensor_info Robot_SensorData;
static sensor_info GetSensorData( void )
{
    pthread_mutex_lock( &mutex_Robot_SensorData );
    sensor_info SensorData = Robot_SensorData;
    pthread_mutex_unlock( &mutex_Robot_SensorData );
    return SensorData;
}
static void SetSensorData( sensor_info SensorData )
{
    pthread_mutex_lock( &mutex_Robot_SensorData );
    Robot_SensorData = SensorData;
    pthread_mutex_unlock( &mutex_Robot_SensorData );
}

static pthread_mutex_t mutex_Robot_MotionState;
static MotionStat_t Robot_MotionState;
static MotionStat_t GetMotionState( void )
{
    pthread_mutex_lock( &mutex_Robot_MotionState );
    MotionStat_t MotionState = Robot_MotionState;
    pthread_mutex_unlock( &mutex_Robot_MotionState );
    return MotionState;
}
static void SetMotionState( MotionStat_t MotionState )
{
    pthread_mutex_lock( &mutex_Robot_MotionState );
    Robot_MotionState =  MotionState;
    pthread_mutex_unlock( &mutex_Robot_MotionState );
}

static pthread_mutex_t mutex_Robot_MotionRes;
static MotionRes_t  Robot_MotionRes;
static MotionRes_t GetMotionRes( void )
{
    pthread_mutex_lock( &mutex_Robot_MotionRes );
    MotionRes_t MotionRes = Robot_MotionRes;
    pthread_mutex_unlock( &mutex_Robot_MotionRes );
    return MotionRes;
}
static void SetMotionRes( MotionRes_t MotionRes )
{
    pthread_mutex_lock( &mutex_Robot_MotionRes );
    Robot_MotionRes = MotionRes;
    pthread_mutex_unlock( &mutex_Robot_MotionRes );
}


// Aim Position From Level-2
static Robot_msg_AimPosition *AimPosition;
static sem_t *mutex_aimPosition;
static pose_t  GetAimPose( void )
{
    pose_t tmp;
    sem_wait( mutex_aimPosition );
    tmp = AimPosition->AimPosition;
    AimPosition->FlagNewAimPoseSet = false;
    sem_post( mutex_aimPosition);
    return tmp;
}

static bool IsNewAimPoseSet(void)
{
    sem_wait( mutex_aimPosition );
    bool flag = AimPosition->FlagNewAimPoseSet;
    sem_post( mutex_aimPosition );
    return flag;
}
static void SetAimPoseReached( void )
{
    sem_wait( mutex_aimPosition );
    AimPosition->FlagAimPoseReached = true;
    sem_post( mutex_aimPosition );
}
static bool IsAimPoseReached(void)
{
    sem_wait( mutex_aimPosition );
    bool flag = AimPosition->FlagAimPoseReached;
    sem_post( mutex_aimPosition );
    return flag;
}

int Level1_Lacation_Trajectory( void )
{
    L0_pid = getppid();    
    L2_pid = fork();
    
    bzero( &Robot_Pose_IMU, sizeof( pose_t ) );
    pthread_mutex_init( &mutex_Robot_Pose_IMU, NULL );
    bzero( &Robot_Pose_Vision, sizeof( pose_t ) );
    pthread_mutex_init( &mutex_Robot_Pose_Vision, NULL );

    pthread_mutex_init( &mutex_Robot_SensorData, NULL );
    bzero( &Robot_SensorData, sizeof( sensor_info ) );
    pthread_mutex_init( &mutex_Robot_MotionState, NULL );
    bzero( &Robot_MotionState, sizeof( MotionStat_t ) );
    pthread_mutex_init( &mutex_Robot_MotionRes, NULL );
    bzero( &Robot_MotionRes, sizeof( MotionRes_t ) );


    // Step-2: Create Semaphore for take photo
    sem_unlink( Sem_Name_takephoto );
    mutex_takephoto = sem_open( Sem_Name_takephoto, O_CREAT|O_EXCL, FILE_MODE, 1);
    sem_close( mutex_takephoto );
    sem_unlink(Sem_Name_VisionLocation);
    sem_t *mutex_visionlocation;
    mutex_visionlocation = sem_open( Sem_Name_VisionLocation, O_CREAT|O_EXCL, FILE_MODE, 1);
    sem_close( mutex_visionlocation );

    if( mutex_takephoto == SEM_FAILED )
    {
        perror(" Error-Level-1: Failed to Open the semaphore--/sem_node12:");
        // Cancel this thread
    }
    // Close the semaphore, please open it at the start of the take photo thread!

    if ( L2_pid<0 )
    {
        perror("Error: Failed to Create Process L1");
        printf("Program Will exit with code -1\n");
        return -1;
    }
    else if( L2_pid == 0 )
    {
        // Level 1 Process
        sleep(1);
        Level2_LocalPlanning( L0_pid );
    }
    

    // Create the Communication Node1_pthread
    pthread_t m_pid_L1_COM_Node1;
    if( pthread_create( &m_pid_L1_COM_Node1, NULL, pThread_COM_Node1, &L2_pid) != 0)
    {
        perror("Error-Level-1: Create pThread_COM_Node1 Failed!");
        return(-1);
    }
    pthread_t m_pid_pThread_L1_CommandUpdate;
    if( pthread_create( &m_pid_pThread_L1_CommandUpdate, NULL, pThread_L1_CommandUpdate, NULL) != 0)
    {
        perror("Error-Level-1: Create pThread_L1_CommandUpdate Failed!");
        return(-1);
    }

    printf("Process Level 2 %d Created!\n", L2_pid );

    pthread_t m_pidMotionLocation;
    if(pthread_create(&m_pidMotionLocation, NULL, pThread_Location, NULL) != 0)
    //if (pthread_create(&m_pidMotionLocation, NULL, pThread_Motion_Location, &L2_pid) != 0)
    {
        perror("Error--Robot(): Create pThread_Motion_Photo Failed!");
        return(-1);
    }

    while( true )
    { 
        cout << "Level1 is Working..." << endl; sleep(10); 
    }
}

/****************************************************/

void* pThread_COM_Node1( void *argv )
{   
    log_t log("./logs/COM_Node1"+time_filename_str(), "Level-1 Communication Node");
    // Open the shared memory object and named semaphore
    int fd_shm01 = shm_open( shm_msg01, O_RDWR, FILE_MODE );
    if( fd_shm01==-1 )
    {
        perror( "Error-Level-1: Failed to Open shm_msg01--/shm_node01:" );
        exit(-1);
    }
    Robot_msg_node01_t (*msg_tmp) = (Robot_msg_node01_t*)mmap(NULL, sizeof(Robot_msg_node01_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shm01, 0);
    close(fd_shm01);
    sem_t *mutex;
    mutex = sem_open( sem_msg01, 0 );

    // Step-1: Create and Initialize Shared Memory Object
    shm_unlink( shm_msg12 );
    int fd_shm12 = shm_open( shm_msg12, O_RDWR|O_CREAT|O_EXCL, FILE_MODE );
    if( fd_shm12==-1 )
    {
        perror( "Error-Level-1: Failed to Create shm_msg12--/shm_node01:" );
        exit( -1 );
    }
    if( ftruncate( fd_shm12, sizeof(Robot_msg_node12_t) ) == -1)
    {
        perror("Error-Level-1: Failed to modify the shared memory size: ");
        exit( -1 );
    }
    Robot_msg_node12_t *msg12_ptr = (Robot_msg_node12_t*)mmap(NULL, sizeof(Robot_msg_node12_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shm12, 0);
    close( fd_shm12 );

    // Step-2: Create Semaphore
    sem_unlink( sem_msg12 );
    sem_t *mutex_msg12;
    mutex_msg12 = sem_open( sem_msg12, O_CREAT|O_EXCL, FILE_MODE, 1);
    if( mutex_msg12 == SEM_FAILED )
    {
        perror(" Error-Level-1: Failed to Open the semaphore--/sem_node12:");
        exit( -1 );
    }
    sem_close( mutex_msg12 );

    // Step-3: Open Shared Memory Object and Semaphore
    fd_shm12 = shm_open( shm_msg12, O_RDWR, FILE_MODE );
    if ( fd_shm12==-1 )
    {
        perror( "Error-Level-1: Failed to Open the shm_msg12--/shm_node12:" );
        exit(-1);
    }
    msg12_ptr = (Robot_msg_node12_t*)mmap(NULL, sizeof(Robot_msg_node12_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shm12, 0);
    close( fd_shm12 );
    mutex_msg12 = sem_open( sem_msg12, 0 );

    unsigned int LastHallRecord_Left = 0;
    unsigned int LastHallRecord_Right = 0;


    log.fs(INFO) << "Communication Node1 start to work!" << endl;
    unsigned int tickCNT = 0;
    while( true )
    {
        sem_wait( mutex );
        SetSensorData( (*msg_tmp).RobotSensor );
        SetMotionState( (*msg_tmp).RobotState );
        SetMotionRes( (*msg_tmp).RobotMotionRes );
        sem_post( mutex );
        //cout << (*msg_tmp).RobotSensor << endl;
        //cout << (*msg_tmp).RobotState << endl;
        //cout << (*msg_tmp).RobotMotionRes << endl;
        pose_t oldPose = GetIMUPose();
        unsigned char RobotCurrState = (*msg_tmp).RobotState.State;
        float curr_angle = (*msg_tmp).RobotSensor.IMU7011_Angle;
        float delta_disL = 0.404 * ( (*msg_tmp).RobotSensor.Hall_Left_Total - LastHallRecord_Left );
        LastHallRecord_Left = (*msg_tmp).RobotSensor.Hall_Left_Total;

        //float delta_disR = 0.404 * msg_tmp.RobotSensor.Hall_Right_Delta;
        float delta_disR = 0.404 * ( (*msg_tmp).RobotSensor.Hall_Left_Total - LastHallRecord_Right ); // Hall_Right_Delta is inaccurate
        LastHallRecord_Right = (*msg_tmp).RobotSensor.Hall_Left_Total;

        //cout << "Delta Distance Left : " << delta_disL << endl;
        //cout << "Delta Distance Right: " << delta_disR << endl;

        pose_t NewImuPose = ImuPoseUpdate( oldPose, RobotCurrState, curr_angle, delta_disL, delta_disR );
        //cout << "IMU Locating:" << NewImuPose << endl;
        tickCNT++;
        if(tickCNT%50 == 0)
        {
            log.fs(INFO) << NewImuPose << endl;
        }
            
        SetIMUPose( NewImuPose );
        
        sem_wait( mutex_msg12 );
        msg12_ptr->GP2Y0A_L = GetSensorData().GP2Y0A_Left;
        msg12_ptr->GP2Y0A_R = GetSensorData().GP2Y0A_Right;
        msg12_ptr->RobotPose = GetPose();
        msg12_ptr->MotionRes  = GetMotionRes();
        msg12_ptr->SEN1 = GetSensorData().SEN1;
        sem_post( mutex_msg12 );        
    }
}

/**********************************************************************************/
/**************************************************************/
 // @Module Name       : CommmandUpdate
 // @Module Author     : LiMin
 // @Module History    : 
 //     1. Modified by LiMin @ 2017-03-16, Debug and now it work well;
 // 
 // @Module Description: 
 //     This module is used to generate motion command to control the robot 
 // move to the aim position which is set by level-2 thread local path planning.
 // 
 //     
 //
/**************************************************************/
void* pThread_L1_CommandUpdate( void*argv )
{
    // Command Update Thread Initialization
    
    log_t logcmd( "./logs/CommandUpdate"+time_filename_str(), "Command Update Module");
    logcmd.fs(INFO) << "command update thread Initializing... " << endl;

    // Init-1: Open the Command Send message queue to send the motion command
    mqd_t mq_cmd = mq_open( MQ_Command, O_RDWR );
    if ( mq_cmd == -1 )
    {
        perror("Error-Level-1::pThread_L1_CommandUpdate: Failed to Open MQ_Command");
        // Cancel this thread 
    }

    logcmd.fs(INFO) << "command send queue opened." << endl;
    // Init-2: Open and map the shared memory object
    // Step-1: Create and Initialize Shared Memory Object
    shm_unlink( Shm_Name_AimPose );
    int fd_shmAimPose = shm_open( Shm_Name_AimPose, O_RDWR|O_CREAT|O_EXCL, FILE_MODE );
    if( fd_shmAimPose==-1 )
    {
        perror( "Error-Level-1::pThread_L1_CommandUpdate: Failed to Create Shm_Name_AimPose." );
        // Cancel this thread 
    }
    if( ftruncate( fd_shmAimPose, sizeof(Robot_msg_AimPosition) ) == -1)
    {
        perror("Error-Level-1::pThread_L1_CommandUpdate: Failed to modify the shared memory size.");
        // Cancel this thread 
    }
    AimPosition = (Robot_msg_AimPosition*)mmap(NULL, sizeof(Robot_msg_AimPosition), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shmAimPose, 0);
    close( fd_shmAimPose );
    // Step-2: Create Semaphore
    sem_unlink( Sem_Name_AimPose );
    mutex_aimPosition = sem_open( Sem_Name_AimPose, O_CREAT|O_EXCL, FILE_MODE, 1);
    if( mutex_aimPosition == SEM_FAILED )
    {
        perror(" Error-Level-1: Failed to Open the semaphore--/sem_node12:");
        // Cancel this thread
    }
    sem_close( mutex_aimPosition );
    // Step-3: Open Shared Memory Object and Semaphore
    fd_shmAimPose = shm_open( Shm_Name_AimPose, O_RDWR, FILE_MODE );
    if ( fd_shmAimPose==-1 )
    {
        perror( "Error-Level-1: Failed to Open the Shm_Name_AimPose." );
        // Cancel this thread
    }
    AimPosition = (Robot_msg_AimPosition*)mmap(NULL, sizeof(Robot_msg_AimPosition), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shmAimPose, 0);
    close( fd_shmAimPose );
    mutex_aimPosition = sem_open( Sem_Name_AimPose, 0 );
    logcmd.fs(INFO) << "The shared memory object Opened and mapped" << endl;

    AimPosition->FlagAimPoseReached = false;
    pose_t NextPosition;

    MCB_t *NextMotionCmd = new MCB_t;
    MCB_t CurrMotionCmd;
    bzero(&CurrMotionCmd, sizeof(MCB_t));
    bzero(NextMotionCmd, sizeof(MCB_t));
    MotionRes_t CurrMotionRes;
    int flagRes;

    sem_t *mutex_visionlocation;
    mutex_visionlocation = sem_open(Sem_Name_VisionLocation, 0 );

    // Modified by limin @ 2017-03-08, check faster
    //usleep(1500000); // ensure the stm-32 init
    logcmd.fs(INFO) << "command update thread start to work!" << endl;
    // only for debug
    while( true )
    {
        // check the FlagNewAimPoseSet
        //logcmd.fs(INFO) << "CMD Update:" << GetAimPose() << IsNewAimPoseSet() << endl;
        if( IsNewAimPoseSet() )
        {
            NextPosition = GetAimPose();
            logcmd.fs(WARNING) << "New Aim Pose Set: " << GetPose() << NextPosition << endl;
            sem_wait( mutex_visionlocation );
            *NextMotionCmd = GetMotionCommand( GetPose(), NextPosition, &flagRes );
            if ( mq_send( mq_cmd, (char*)NextMotionCmd, sizeof(MCB_t), 1 ) == -1)
            {
                perror("Warning-Level-1::pThread_L1_CommandUpdate: Failed to Send Command!");
                continue;
            }
            CurrMotionCmd = *NextMotionCmd;
            sem_post( mutex_visionlocation );
            logcmd.fs(INFO) << "Current Pose: " << GetPose()
                            << "Aim Position: " << NextPosition
                            << "\n"
                            << CurrMotionCmd << endl;
        }
        // Check whether the aim pose reached
        if( Is_PoseEqual( GetPose(), NextPosition ) && !IsAimPoseReached())
        {
            logcmd.fs(WARNING) << "Aim Pose Reached--case 1!" 
                               << "Current Pose: " << GetPose() 
                               << "Aim Position: " << NextPosition  << endl;

            NextMotionCmd->cmd_move = CMD_MOVE_Stop;
            NextMotionCmd->serialnum++;
            sem_wait( mutex_visionlocation );
            if ( mq_send( mq_cmd, (char*)NextMotionCmd, sizeof(MCB_t), 1 ) == -1)
            {
                perror("Warning-Level-1::pThread_L1_CommandUpdate: Failed to Send Command!");
                continue;
            }
            CurrMotionCmd = *NextMotionCmd;
            SetAimPoseReached();
            sem_post( mutex_visionlocation );

            logcmd.fs(INFO) << "Current Pose: " << GetPose()
                            << "Aim Position: " << NextPosition
                            << "\n"
                            << CurrMotionCmd << endl;
        }
        // check whether the current motion command has been executed
        CurrMotionRes = GetMotionRes();
        if( !IsAimPoseReached() && CurrMotionRes.serialnum == CurrMotionCmd.serialnum && CurrMotionRes.state == ME_STATE_Done )
        {
            logcmd.fs(WARNING) << "Current Command "<< CurrMotionRes.serialnum <<" has been executed!"  << GetPose() << NextPosition  << endl;

            if( !Is_PoseEqual( GetPose(), NextPosition ) )
            {
                *NextMotionCmd = GetMotionCommand( GetPose(), NextPosition, &flagRes );
                sem_wait( mutex_visionlocation );
                if ( mq_send( mq_cmd, (char*)NextMotionCmd, sizeof(MCB_t), 1 ) == -1)
                {
                    perror("Warning-Level-1::pThread_L1_CommandUpdate: Failed to Send Command!");
                    continue;
                }
                sem_post( mutex_visionlocation );
                CurrMotionCmd = *NextMotionCmd;
                logcmd.fs(INFO) << "Current Pose: " << GetPose()
                                << "Aim Position: " << NextPosition
                                << "\n"
                                << CurrMotionCmd << endl;
            }
            else
            {
                logcmd.fs(WARNING) << "Aim Pose Reached--case 2!" << GetPose() << NextPosition  << endl;
                SetAimPoseReached();
            }
        }
        // check whether need re-calculate command
        usleep(20000);
    } // thread main loop
    return 0;
}
// This is the end of Module Command update 
// --*END*--
/*****************************************************************************/


/**********************************************************************************/
/**************************************************************/
 // @Module Name       : Location
 // @Module Author     : LiMin & WangXiaotong
 // @Module History    : 
 //     1. Create by WangXiaotong at 2017-03-03
 //     2. Modified by LiMin at 2017-03-14: Reconstruct the code and add log recorder
 //     3. Modified by LiMin at 2017-03-14: Reconstruct the code and change the thread name
 //     4. Modified by LiMin at 2017-03-27: Add Kalman filter to confuse IMU pose and vision pose
 //         Add statistics information in log file.
 // @Module Description: 
 //     This module is a thread work at level-1 process, it will 
 // capture the top camera frame and calculate the robot pose(x,y,theta).
 // 
 //     
 //
/**************************************************************/
void* pThread_Location(void *argv)
{
    // Step-0: Prepare log record
    
    log_t log("./logs/Location"+time_filename_str(), "Vision Location and Inertial Location Confuse");
    log.fs(INFO) << "Location Confuse thread Initializing..." << endl;
    // Step-2: Thread Initial
    string path_str = "topImages";
    if( DeleteDir( path_str.c_str() )!=0 )
    {
        log.fs(ERROR) << "Failed to delete the old topImage files!" << endl;
        //return 0;
    }
    if( !CreateDir( path_str.c_str() ) )
    {
        log.fs(ERROR) << "Failed to create the topImage store directory!" << endl;
        return 0;
    }
    log.fs(WARNING) << "Directory topImages has been created!" << endl;

    Mat frame;
    if(getframe.init()==0)
    {
        getframe.setExposureMode(3);
        for( unsigned int i=0;i<10;i++ )
        {
            frame=getframe.getVideoFrameTop();
            if(i>2&&!frame.empty())
                break;
        }
    }
    else 
    {
        log.fs(FATAL) << "Camera Top Initial failed!!!" << endl;
        return 0;
    }

    // Step-3: Open the semaphore
    sem_t *mutex_visionlocation;
    mutex_takephoto = sem_open( Sem_Name_takephoto, 0 );
    mutex_visionlocation = sem_open(Sem_Name_VisionLocation, 0 );
    log.fs(INFO) << "semaphore--Sem_Name_takephoto:"<< Sem_Name_takephoto << "opened!" << endl;

    Pose::Ptr VisionLocation(new Pose);
    Camera::Ptr camera(new Camera);
    Frame::Ptr pFrame = Frame::createFrame();


    bool flagVisionLocation = false;
    pose_t lastIMUPose = GetIMUPose();
    pose_t currIMUPose = GetIMUPose();
    pose_t currIMUPose_new = GetIMUPose();
    pose_t visionPose;
    pose_t adjustPose;
    unsigned char LastMotionStatus;
    
    log.fs(INFO) << "Vision Location Start to Work at Pose: " << currIMUPose << endl;

    int flag = 0;

    
    // for new feature test
    Kalman_state_t *kalmanstate = new Kalman_state_t;
    kalman_init(kalmanstate);
    log.fs(INFO) << "Kalman filer init!" << endl;

    // 
    unsigned int cnt_VO = 0;
    unsigned int cnt_VOSuccees = 0;
    double Start_Runtime = (double)cv::getTickCount()/cv::getTickFrequency();
    double Total_Runtime = 0;
    double RunningTime = 0;
    int tickCNT = 0;
    
    log.fs(INFO) << "currIMUPose\t" << "visionPose\t" << "currIMUPose_new\t" << "adjustPose\t" << endl;\
    while( true )
    {
        log.fs(INFO) << "Waiting for VO signal..." << endl;
        sem_wait( mutex_visionlocation );
        // command update thread will stop work

        // Get current top camera frame
        frame = GetTopFrame();
        Frame::Ptr pFrame = Frame::createFrame();  
        pFrame->camera_ = camera;
        pFrame->img_ = frame;

        // Get current IMU Pose to minimum the search box size
        currIMUPose = GetIMUPose();
        // Get the current motion state
        LastMotionStatus = GetMotionState().State;

        // Calculate the input reference data
        DATA Delta_Pose_Ref;
        Delta_Pose_Ref.x = -fabs(currIMUPose.x - lastIMUPose.x)/10;
        Delta_Pose_Ref.y = -fabs(currIMUPose.y - lastIMUPose.y)/10;
        Delta_Pose_Ref.theta = currIMUPose.theta - lastIMUPose.theta;
        //cout<<"Delta_Pose_Ref: "<<Delta_Pose_Ref.x<<" "<<Delta_Pose_Ref.y<<" "<<Delta_Pose_Ref.theta<<endl;
        
        sem_post( mutex_visionlocation );
        // command update thread will start work!

        // Calculate the vision pose while motion is executed
        double t1=(double)getTickCount();
        flagVisionLocation = VisionLocation->addFrame(pFrame,flag, LastMotionStatus, Delta_Pose_Ref );
        double t2=(double)getTickCount();
        double time = (t2-t1)/getTickFrequency();
        RunningTime += time;
        cnt_VO++;

        // Get the vision pose and the IMU pose while vision location done
        visionPose = VisionLocation->getPoseTotal();
        currIMUPose_new = GetIMUPose();

        // If vision locating success
        if( flagVisionLocation )
        {
            float delta_x = currIMUPose_new.x - currIMUPose.x;
            float delta_y = currIMUPose_new.y - currIMUPose.y;
            float delta_theta = currIMUPose_new.theta - currIMUPose.theta;
            //float delta_t = currIMUPose_new.theta - currIMUPose.theta;
            adjustPose.x = visionPose.x*10 + delta_x;
            adjustPose.y = visionPose.y*10 + delta_y;
            adjustPose.theta = visionPose.theta + delta_theta;

            SetVisionPose(adjustPose);


            pose_t PoseKalman = Location_Kalman( adjustPose, currIMUPose_new, kalmanstate);
            //SetIMUPose(adjustPose);

            string time_stamp = time_filename_str();
            
            log.fs(INFO) << "Vision Location Result: "
                         << "\n\t Time Usage:   " << time << "s."
                         << "\n\t currIMU Pose: " << currIMUPose
                         << "\n\t lastIMU Pose: " << lastIMUPose
                         << "\n\t Vision Res:   " << visionPose
                         << "\n\t IMU Pose New: " << currIMUPose_new
                         << "\n\t Confused Pose:" << adjustPose
                         << "\n\t Kalman Pose  :" << PoseKalman
                         << "\n\t Image path:   " << path_str+"/"+time_stamp+".jpg"
                         << endl << endl;

            imwrite( path_str+"/"+time_stamp+".jpg", frame);

            cnt_VOSuccees++;
            
        }
        lastIMUPose = currIMUPose;

        flag ++;
        Total_Runtime = (double)cv::getTickCount()/cv::getTickFrequency() - Start_Runtime;
        tickCNT++;
        if(tickCNT%10==0)
        {
            log.fs(INFO) << "VO and INS Confuse statistics information:"
                         << "\n\t Total VO count  : " << cnt_VO
                         << "\n\t Success VO count: " << cnt_VOSuccees
                         << "\n\t VO Success rate : " << 100*(float)cnt_VOSuccees/cnt_VO
                         << "\n\t Average VO time(s): " << RunningTime/cnt_VO
                         << "\n\t VO Frequency    : " << cnt_VO/Total_Runtime
                         << endl;
        }
        usleep(20000);
    }
    return 0;
}
// This is the end of Module Location 
// --*END*--
/*****************************************************************************/
