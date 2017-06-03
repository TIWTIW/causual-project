
#include "Robot_VisionNavV2.h"
#include "mapping/mapping.h"
#include "logmodule/logmodule.hpp"
#include "generalfunction/Myfunctions.h"


#define RIGHT 2
#define LEFT 0 
static pid_t L0_pid;
static pid_t L1_pid;
/******************************/
// Mapping module variables
const unsigned int GridMapSizeX = 500;
const unsigned int GridMapSizeY = 500;
pthread_mutex_t mutex_mapData;
Grid_Map_t mapData( GridMapSizeX, GridMapSizeY );
/******************************/
/******************************/
// Global Path Planning module variables
int cnt = 0;
int flag_GPLP = 1;
pthread_mutex_t mutex_GPLP;
pthread_cond_t cond_GPLP;
/******************************/
/****************************************************/
// --*Start*--: Interface between Global Planning and Local Planning
float CleanDirection;
pthread_mutex_t mutex_CleanDirection;
void SetCleanDirection( float direction )
{
    pthread_mutex_lock( &mutex_CleanDirection );
    CleanDirection = direction;
    pthread_mutex_unlock( &mutex_CleanDirection );
}
float GetCleanDirection(void)
{
    pthread_mutex_lock( &mutex_CleanDirection );
    float direction = CleanDirection;
    pthread_mutex_unlock( &mutex_CleanDirection );
    return direction;
}
vector<pose_t> GlobalPath;
pthread_mutex_t mutex_GlobalPath;
void SetGlobalPath( vector<pose_t> path_divided )
{
    pthread_mutex_lock( &mutex_GlobalPath );
    GlobalPath = path_divided;
    pthread_mutex_unlock( &mutex_GlobalPath );
}
vector<pose_t> GetGlobalPath(void)
{
    pthread_mutex_lock( &mutex_GlobalPath );
    vector<pose_t> path_divided = GlobalPath;
    pthread_mutex_unlock( &mutex_GlobalPath );
    return path_divided;
}
// --*END*--: Interface between Global Planning and Local Planning
/****************************************************/

static videoDevice getframefxz("/dev/video0", 30);
static pose_t posetake;//拍照时的位姿
static pose_t poseaim;//目标位姿

static int right_or_left;

static float grayaver=0;

// If the obstatake updated please ensure set this flag to true!!
static bool flagFrontImageUpdate = false;
static pair<float,float> obsttake[32];//拍照时得到的前方障碍物信息

static float turnlength=15;//当判断为可绕行状态时，转弯过后需要直行的距离

static float thetaINcol=0;//清扫列中的机器人位姿角
static float yINcol=0;//机器人切换行走状态时用来记录位姿
static float xINcol=0;

static float thetaWHENalong=0;//机器人沿边行走过程中的位姿角，不断的变化
static float xWHENalong=0;
static float yWHENalong=0;

static float constDIS=0;
static int InRangeFlag=0;

static float xScan1=0;
static float xScan2=0;

//static int imageindex=0;
static int cam_mask=0;//摄像头屏蔽标志 0：不屏蔽 1：摄像头等待拍摄信号 2：摄像头不工作，直接跳过
static int edgemask=0;//边缘检测屏蔽标志 0：不屏蔽，启用边缘检测 1：屏蔽边缘检测
static int takeok=0;//cam_mask=1时配合使用，表示拍摄完毕

static int signaled1=0;//信号量发送标志 0：未发送 1：已发送
static int signaled2=0;//同上

static int preflag=4;

static pthread_mutex_t mutex_Take;
static pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond1=PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex2=PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond2=PTHREAD_COND_INITIALIZER;
//static pthread_mutex_t mutex3=PTHREAD_MUTEX_INITIALIZER;
//static pthread_cond_t cond3=PTHREAD_COND_INITIALIZER;

bool theAreaIsOCP(pose_t pose)
{
    Grid_Map_t dilateMap;
    Grid_Map_t mapSnap;
    Map_Attr_t mapAttr;

    pthread_mutex_lock( &mutex_mapData );
    //mapSnap = mapData.clone();
    mapData.copyto( mapSnap );
    pthread_mutex_unlock( &mutex_mapData );
    mapAttr = mapSnap.GetAttr();
    cout<<"mapAttr="<<mapAttr<<endl;
    //mapSnap.dilate( &dilateMap );
    //dilateMap.Save(".", "dilateMap");
    //cout<<"axiba"<<endl;
    int flag=0;
    //Point pose_p = pose2grid(pose,mapAttr);
    for(int i=180;i>-abs(xScan2-xScan1)-170;i=i-40)
    {
        //Point pose_p=Map_Local_to_Global(Point(i,210*((xScan2-xScan1)/abs(xScan2-xScan1))),pose);
        Point pose_grid = PhyLocaltoMapIndex( Point(i,210*((xScan2-xScan1)/abs(xScan2-xScan1))), pose, mapAttr.map_grid_size );
        cout<<"theAreaIsOCP::pose_grid: "<<pose_grid<<" "<<mapSnap.IsOcp(pose_grid)<<endl;
        if(mapSnap.IsOcp(pose_grid)==false) 
        {
            flag++;
            if(flag>=8)
                break;
        }
        else
        {
            flag=0;
        }
    }
     
    if(flag<8)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool needLookRound(pose_t pose,float xmax,int direc)
{
    Grid_Map_t dilateMap;
    Grid_Map_t mapSnap;
    Map_Attr_t mapAttr;

    pthread_mutex_lock( &mutex_mapData );
    //mapSnap = mapData.clone();
    mapData.copyto( mapSnap );
    pthread_mutex_unlock( &mutex_mapData );
    mapAttr = mapSnap.GetAttr();
    //Point pose_p = pose2grid(pose,mapAttr);
    for(int i=xmax-140;i<160+xmax;i=i+40)
    {
        for(int j=180;j<=220;j=j+40)
        {
            Point pose_grid = PhyLocaltoMapIndex( Point(i,j*(1-direc)), pose, mapAttr.map_grid_size );
            cout<<"needLookRound: "<<pose_grid<<" "<<mapSnap.IsOcp(pose_grid)<<endl;
            if(mapSnap.IsOcp(pose_grid)) 
            {
                return 1;
            }
        } 
    }
    return 0;
}
bool needTurn(pose_t pose)
{
    Grid_Map_t dilateMap;
    Grid_Map_t mapSnap;
    Map_Attr_t mapAttr;

    pthread_mutex_lock( &mutex_mapData );
    //mapSnap = mapData.clone();
    mapData.copyto( mapSnap );
    pthread_mutex_unlock( &mutex_mapData );
    mapAttr = mapSnap.GetAttr();
    //Point pose_p = pose2grid(pose,mapAttr);
    int obst_cnt = 0;
    cout << "need turn pose: " << pose << endl;
    for(int y=-2; y<=2; y++)
    {
        Point MapIndex1 = GridLocaltoMapIndex( Point(4, y), pose, mapAttr.map_grid_size );
        Point MapIndex2 = GridLocaltoMapIndex( Point(5, y), pose, mapAttr.map_grid_size );
        cout<<"needTurn: "<<MapIndex1<<" "<<mapSnap.IsOcp(MapIndex1)<<endl;
        cout<<"needTurn: "<<MapIndex2<<" "<<mapSnap.IsOcp(MapIndex2)<<endl;
        if( mapSnap.IsOcp( MapIndex1 ) )
        {
            obst_cnt++;
        }
        if( mapSnap.IsOcp( MapIndex2 ) )
        {
            obst_cnt++;
        }
    }
    return obst_cnt;
}

static string to_string( int num)
{
    stringstream ss;  
    ss<<num;  
    return ss.str(); 
}

//static sem_t *mutex_takephoto; defined in L1
static Mat GetFrontFrame( void )
{
    if(getframefxz.hasinit==0)
    {
        getframefxz.init();
    }
    Mat image;
    sem_wait(mutex_takephoto);
    cout << "taking front photo..." << endl;
    for (int j=0; j<2; j++)
    {
        image=getframefxz.getVideoFrameFront();
    }
    sem_post(mutex_takephoto);
    return image;
}

// Created By fxz.
// Modified By limin @ 2017-03-15
// Delete By limin @ 2017-04-07
/*
static vector<Point> GetFrontObstacles(pair<float,float> *obsttake, const pose_t currPose, const Map_Attr_t mapAttr )
{
    vector<Point> obstacles;
    for (unsigned int i=0; i<32; i++)
    {
        if(obsttake[i].first<50 && obsttake[i].first>0)
        {
            // Local Position temp
            Point temp( 10*(obsttake[i].first+15), -10*obsttake[i].second  );
            // Trans Local to Global
            Point globalTemp = Map_Local_to_Global(temp, currPose);
            globalTemp = Phy_to_Grid( globalTemp, mapAttr );
            obstacles.push_back(globalTemp);
        }
    }

    return obstacles;
}*/

static pthread_mutex_t mutex_Robot_SEN1;
static unsigned char SEN1;
static unsigned char GetSEN1( void )
{
    pthread_mutex_lock( &mutex_Robot_SEN1 );
    unsigned char sen1 = SEN1;
    pthread_mutex_unlock( &mutex_Robot_SEN1 );
    return sen1;
}
static void SetSEN1( unsigned char sen1 )
{
    pthread_mutex_lock( &mutex_Robot_SEN1 );
    SEN1 = sen1;
    pthread_mutex_unlock( &mutex_Robot_SEN1 );
}
static int IsCompacted(void)
{
    char sen1;
    pthread_mutex_lock( &mutex_Robot_SEN1 );
    sen1 = SEN1;
    pthread_mutex_unlock( &mutex_Robot_SEN1 );
    switch( sen1 & 0xc0 )
    {
        case 0x80 :
            return 1;  // Left Compact
        case 0x40 :   
            return 2;  // Right Compact
        case 0xc0 :
            return 3;  // Both Compact
        default:
            return 0;  // No Compact
    }
}

static int GP2Y0A_L;
static int GP2Y0A_R;
static pthread_mutex_t mutex_GP2Y0A;
static int GetGP2Y0A_L( void )
{
    pthread_mutex_lock( &mutex_GP2Y0A );
    int disL = GP2Y0A_L; 
    pthread_mutex_unlock( &mutex_GP2Y0A );
    return disL;
}
static int GetGP2Y0A_R( void )
{
    pthread_mutex_lock( &mutex_GP2Y0A );
    int disR = GP2Y0A_R; 
    pthread_mutex_unlock( &mutex_GP2Y0A );
    return disR;
}
static int GetGP2Y0A(int direction)//根据direction来获取不同边的红外信息 0：左边 2:右边
{
    pthread_mutex_lock( &mutex_GP2Y0A );
    int disL ;
    if(direction==0)
    {
        disL= GP2Y0A_L; 
    }
    if(direction==2)
    {
        disL=GP2Y0A_R;
    }
    pthread_mutex_unlock( &mutex_GP2Y0A );
    return disL;
}
static void SetGP2Y0A( int disL, int disR )
{
    pthread_mutex_lock( &mutex_GP2Y0A );
    GP2Y0A_L = disL;
    GP2Y0A_R = disR;
    pthread_mutex_unlock( &mutex_GP2Y0A );
}

static pthread_mutex_t mutex_Robot_Pose; 
static struct pose_t Robot_Pose;
static pose_t GetPose( void )
{
    pthread_mutex_lock( &mutex_Robot_Pose );
    pose_t Pose = Robot_Pose; 
    pthread_mutex_unlock( &mutex_Robot_Pose );
    return Pose;
}
static void SetPose( pose_t Pose )
{
    pthread_mutex_lock( &mutex_Robot_Pose );
    Robot_Pose = Pose; 
    pthread_mutex_unlock( &mutex_Robot_Pose );
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
static void SetAimPose( location_t AimPose )
{
    cout<<"fxz's command="<<AimPose<<endl;
    sem_wait( mutex_aimPosition );
    AimPosition->AimPosition = AimPose;
    AimPosition->FlagAimPoseReached = false;
    AimPosition->FlagNewAimPoseSet = true;
    sem_post( mutex_aimPosition);
    cout << AimPosition->AimPosition << AimPosition->FlagNewAimPoseSet << AimPosition->FlagAimPoseReached << endl;
    usleep(20000);
}

static bool IsAimPoseReached( void )
{
    sem_wait( mutex_aimPosition );
    bool flag;
    flag = AimPosition->FlagAimPoseReached;
    sem_post( mutex_aimPosition );
    //cout << "AimPoseReachTestPoint: " << flag << endl;
    return flag;
}
int setExposureValue(int nowvalue,float nowgray)
{
    int nextvalue=240;
    switch(nowvalue)
    {
        case 60:
                if(nowgray<=4)
                {
                    nextvalue=300;
                }
                else if(nowgray<=10)
                {
                    nextvalue=240;
                }
                else if(nowgray<=20)
                {
                    nextvalue=180;
                }
                else if(nowgray<=40)
                {
                    nextvalue=120;
                }
                else
                {
                    nextvalue=60;
                }
                break;
        case 120:
                if(nowgray<=5)
                {
                    nextvalue=300;
                }
                else if(nowgray<=10)
                {
                    nextvalue=240;
                }
                else if(nowgray<=30)
                {
                    nextvalue=180;
                }
                else if(nowgray<=200)
                {
                    nextvalue=120;
                }
                else
                {
                    nextvalue=60;
                }
                break;
        case 180:
                if(nowgray<=5)
                {
                    nextvalue=300;
                }
                else if(nowgray<=65)
                {
                    nextvalue=240;
                }
                else if(nowgray<=160)
                {
                    nextvalue=180;
                }
                else if(nowgray<=200)
                {
                    nextvalue=120;
                }
                else
                {
                    nextvalue=60;
                }
                break;
        case 240:
                if(nowgray<=5)
                {
                    nextvalue=300;
                }
                else if(nowgray<=150)
                {
                    nextvalue=240;
                }
                else if(nowgray<=220)
                {
                    nextvalue=180;
                }
                else if(nowgray<=240)
                {
                    nextvalue=120;
                }
                else
                {
                    nextvalue=60;
                }
                break;
        case 300:
                if(nowgray<=150)
                {
                    nextvalue=300;
                }
                else if(nowgray<=200)
                {
                    nextvalue=240;
                }
                else if(nowgray<=245)
                {
                    nextvalue=180;
                }
                else if(nowgray<=250)
                {
                    nextvalue=120;
                }
                else
                {
                    nextvalue=60;
                }
                break;
        default :break;

    }
    return nextvalue;
}
static void takeImmediately()
{
    if(cam_mask==1)
    {
        pthread_mutex_lock(&mutex1);
        signaled1=1;
        pthread_mutex_unlock(&mutex1);
        pthread_cond_signal(&cond1);
        cout<<"takeImmediately::cond1 sent!"<<endl;
        pthread_mutex_lock(&mutex2);
        if(signaled2==0)
        {
            pthread_cond_wait(&cond2,&mutex2);
        }
        pthread_mutex_unlock(&mutex2);
        cout<<"takeImmediately::cond2 received!"<<endl;
        signaled1=0;
        signaled2=0;
    }
}
int Level2_LocalPlanning( pid_t pidnum )
{
    L0_pid = pidnum;
    L1_pid = getppid();
    /*
    pid_t L3_pid = fork();
    if ( L3_pid<0 )
    {
        perror("Error: Failed to Create Process L3");
        printf("Program Will exit with code -1\n");
        return -1;
    }
    else if( L3_pid == 0 )
    {
        // Level 1 Process
        Level3_GlobalPlanning( L0_pid, L1_pid );
    }*/
    sleep(2);
    
    // Open the Shared memory object to send the aim position
    int fd_shmAimPose = shm_open( Shm_Name_AimPose, O_RDWR, FILE_MODE );
    if ( fd_shmAimPose==-1 )
    {
        perror( "Error-Level-1: Failed to Open the Shm_Name_AimPose." );
        exit(-1);
    }
    AimPosition = (Robot_msg_AimPosition*)mmap(NULL, sizeof(Robot_msg_AimPosition), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shmAimPose, 0);
    close( fd_shmAimPose );
    mutex_aimPosition = sem_open( Sem_Name_AimPose, 0 );
    //cout << "The shared memory object Opened and mapped" << endl;

    bzero( &Robot_Pose, sizeof(pose_t) );
    pthread_mutex_init( &mutex_Robot_Pose, NULL );
    pthread_mutex_init( &mutex_GP2Y0A, NULL );
    pthread_mutex_init( &mutex_Robot_MotionRes, NULL );
    pthread_mutex_init( &mutex_Robot_SEN1, NULL );
    pthread_mutex_init( &mutex_GPLP, NULL );

    if(getframefxz.hasinit==0)//若摄像头未初始化，则初始化摄像头
    {
        getframefxz.init();
        getframefxz.setExposureMode(1);
        getframefxz.changeExposureValue(240);
    }

    // Create the Communication Node1_pthread
    pthread_t m_pid_L2_COM_Node2;
    if( pthread_create( &m_pid_L2_COM_Node2, NULL, pThread_COM_Node2, NULL) != 0)
    {
        perror("Error: Create pThread_COM_Node2 Failed!");
        return(-1);
    }
    // Map Update thread
    pthread_t m_pid_L2_MapUpdate;
    if( pthread_create( &m_pid_L2_MapUpdate, NULL, pThread_MapUpdate, NULL) != 0)
    {
        perror("Error-L2: Failed to Create the MapUpdate Thread!");
        return(-1);
    }
    // Global Path Planning 
    pthread_t m_pid_ThreadGP;
    if( pthread_create(&m_pid_ThreadGP, NULL, pThread_GP, NULL) != 0 )
    {
        perror("Failed to Create Thread GP!");
        return -1;
    }
    // Local Path Planning
    /*
    pthread_t m_pid_ThreadLP;
    if( pthread_create(&m_pid_ThreadLP, NULL, pThread_LP, NULL) != 0 )
    {
        perror("Failed to Create thread LP!");
        return -1;
    }*/

    // Local Path Planning test
    Mat image;
    //pose_t posenow;
    float distance[32];
    pose_t posenow;
    pair<float,float> obstnow[32];
    float frontnearest,extendnearest,extendfarthest;
    unsigned int frontnearestnum;
    float angle=0;
    vector<pair<float,float> >frontobst;


    //程序启动后，先获取一帧信息（位姿及障碍物信息），防止拍照线程晚于
    //路径规划线程启动而无数据可用

    if(getframefxz.hasinit==1)
    {
        for (int j=0;j<4;j++)
        {
            image=getframefxz.getVideoFrameFront();
        }
        //imwrite("save.jpg",image);
        posetake=GetPose();
        grayaver=distance_measure(image, distance, edgemask);
        distance_decoder(distance,obsttake);
        getframefxz.changeExposureValue(setExposureValue(getframefxz.getExposureValue(),grayaver));
        cout<<"grayaver="<<grayaver<<" exposure value="<<getframefxz.getExposureValue()<<endl;
        //imwrite("dete.jpg",image);
        //Along(obsttake,frontobst,frontnearest,frontnearestnum,extendnearest,extendfarthest,0);//frontnearest init
        //cout<<"frontnearest="<<frontnearest<<endl;
        //angle=AngleANDLengthGet(frontobst,turnlength,frontnearestnum,2,frontnearest);
        //cout<<"frontnearest="<<frontnearest<<" angle="<<angle<<endl;
    }
    //while(true){}
    pthread_t m_pid_L2_TAKE_Photo;//启动拍照线程
    if( pthread_create( &m_pid_L2_TAKE_Photo,NULL, pThread_TAKE_Photo, NULL) != 0)
    {
        perror("Error: Create pThread_TAKE_Photo Failed!");
        return(-1);
    }


    int flag=4;//flag是路径规划标志：4代表正常行走状态 
    //int num=1000;
    /*poseaim=GetPose();
    poseaim.x+=200*cos(poseaim.theta*3.14/180);
    SetAimPose(poseaim);
    while(true)
    {
        if(IsAimPoseReached())
        {
            cout<<"here!"<<endl;
            break;
        }
        usleep(50000);
    }
    while(true){}*/
    //while(true){ pose_t Aim=GetPose(); Aim.x+=70; SetAimPose( Aim ); usleep(200000);}

    while(true)
    {
        // Used for Local-Planning and Global-Planning transform
        pthread_mutex_lock(&mutex_GPLP);

        if(flag==4)
        {
            cout<<"now flag="<<flag<<endl;
            pthread_mutex_lock( &mutex_Take);
            posenow=GetPose();
            cout<<"posetake_when_cal="<<posetake<<endl;
            cout<<"pose_when_cal="<<posenow<<endl;
            obst_convert(posetake,posenow,obsttake,obstnow);
            pthread_mutex_unlock( &mutex_Take);
            Frontobst(obstnow,frontobst,frontnearest,frontnearestnum,extendnearest,extendfarthest,2);
            cout<<"frontnearest="<<frontnearest<<endl;
            poseaim=GetPose();
            if(preflag!=4 && frontnearest==100 && needTurn(poseaim))
            {
                if(poseaim.theta>-90 && poseaim.theta<90)
                {
                    right_or_left=RIGHT;
                }
                else
                {
                    right_or_left=LEFT;
                }
                preflag=flag;
                poseaim.theta=thetaINcol+90*(right_or_left-1);
                thetaWHENalong=poseaim.theta;
                SetAimPose(poseaim);
                thetaINcol=90+90*(right_or_left-1);
                while(true)
                {
                    if(IsAimPoseReached())
                    {
                        flag=0;
                        break;
                    }
                    usleep(20000);
                }
            }
            else
            {
                if(frontnearest<=25)//若离障碍物距离小于25，则直接走到障碍物边缘并转弯进入沿边模式
                {
                    cam_mask=2;
                    if(GetPose().theta>-90 && GetPose().theta<90)
                    {
                        right_or_left=RIGHT;
                    }
                    else
                    {
                        right_or_left=LEFT;
                    }
                    angle=AngleANDLengthGet(frontobst,turnlength,frontnearestnum,2-right_or_left,frontnearest);
                    turnlength+=1;
                    cout<<"frontnearest="<<frontnearest<<endl;
                    if(frontnearest-3<0)
                    {
                        frontnearest=3;
                    }
                    if(needLookRound(poseaim,frontnearest*10-30,2-right_or_left))
                    {
                        cam_mask=1;
                        poseaim.theta=thetaINcol+(right_or_left-1)*45;
                        SetAimPose(poseaim);
                        while(true)
                        {
                            if(IsAimPoseReached())
                            {
                                cam_mask = 1;
                                takeImmediately();
                                cam_mask=2;
                                break;
                            }
                            usleep(20000);
                        }
                        poseaim.theta=thetaINcol;
                        SetAimPose(poseaim);
                        while(true)
                        {
                            if(IsAimPoseReached())
                            {
                                break;
                            }
                            usleep(20000);
                        }
                    }
                    poseaim.x+=(frontnearest*10-30)*cos(poseaim.theta*3.14/180);
                    poseaim.y=yINcol;
                    poseaim.theta=thetaINcol;
                    SetAimPose(poseaim);
                    xScan2=poseaim.x;
                    cout<<"xScan1="<<xScan1<<" xScan2="<<xScan2<<endl;
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            if(theAreaIsOCP(poseaim))
                            {
                                cout<<"need global planning"<<endl;
                                pthread_cond_signal(&cond_GPLP);
                                pthread_mutex_unlock(&mutex_GPLP);
                                usleep(20000);
                                pthread_mutex_lock(&mutex_GPLP);
                                cout << "Global Planning has Done" << endl;
                                vector<pose_t> newGlobalPath = GetGlobalPath();
                                cout << "Global Path is: ";
                                for( vector<pose_t>::iterator iter = newGlobalPath.begin(); iter != newGlobalPath.end(); iter++ )
                                {
                                    cout << *iter << "-->";
                                }
                                cout << endl;
                                for( vector<pose_t>::iterator iter = newGlobalPath.begin(); iter != newGlobalPath.end(); iter++ )
                                {
                                    pose_t aim = *iter;
                                    SetAimPose(aim);
                                    cout << "Approaching " << aim << endl;
                                    while( !IsAimPoseReached() )
                                    {
                                        //cout << "Approaching " << tmp << endl;
                                        usleep(20000);
                                    }
                                    cout << aim << " Approached" << endl;
                                }
                                newGlobalPath.clear();
                                SetGlobalPath( newGlobalPath ); // aim pose has reached!

                                while(true)
                                {
                                    usleep(20000);
                                }
                            }
                            cout<<"angle="<<angle<<endl;
                            poseaim.theta=thetaINcol+(right_or_left-1)*angle;
                            thetaWHENalong=poseaim.theta;
                            SetAimPose(poseaim);
                            thetaINcol=90+(right_or_left-1)*90;
                            break;
                        }
                        usleep(20000);
                    }
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            preflag=flag;
                            takeImmediately();
                            xINcol=GetPose().x;
                            if(turnlength<=15)
                            {
                                flag=0;
                            }
                            else
                            {
                                constDIS=(turnlength-15+3)*10;
                                xWHENalong=poseaim.x;
                                yWHENalong=poseaim.y;
                                InRangeFlag=1;
                                flag=1;
                            }
                            cout<<"4_1_1"<<endl;
                            break;
                        }
                        usleep(20000);
                    }
                }
                else//若离障碍物较远，继续前进
                {
                    poseaim.x+=70*cos(poseaim.theta*3.14/180);
                    poseaim.y=yINcol;
                    poseaim.theta=thetaINcol;
                    SetAimPose(poseaim);
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            preflag=flag;
                            flag = 4;
                            poseaim=GetPose();
                            poseaim.x+=30*cos(poseaim.theta*3.14/180);
                            poseaim.y=yINcol;
                            poseaim.theta=thetaINcol;
                            SetAimPose(poseaim);
                            break;
                        }
                        usleep(20000);
                    }
                    ////num++;
                    cout<<"4_1_2"<<endl;
                }
            }
            cout << "Local Planning :: Next flag = " << flag << endl;
        }
        else//若flag不等于4，则说明进入了沿边状态，Alongplanning中的2表示右边沿边，0表示左边沿边
        {
            if(right_or_left==RIGHT)
            {
                 Alongplanning(posetake,obsttake,cam_mask,flag,2);
            }
            else
            {
                 Alongplanning(posetake,obsttake,cam_mask,flag,0);
            } 
        }
        cout<<"cam_mask="<<cam_mask<<endl;
        pthread_mutex_unlock(&mutex_GPLP);
        //AlongplanningL(posetake,obsttake,cam_mask,flag,num);
        usleep(50000);
    }
    return 0;
}

/****************************************************/
void* pThread_COM_Node2( void *argv )
{
    int fd_shm12 = shm_open( shm_msg12, O_RDWR, FILE_MODE );
    if ( fd_shm12==-1 )
    {
        perror( "Error-Level-2: Failed to Open the shm_msg12--/shm_node12: " );
        exit(-1);
    }
    Robot_msg_node12_t (*msg12_tmp) = (Robot_msg_node12_t*)mmap( NULL, sizeof(Robot_msg_node12_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd_shm12, 0 );
    close( fd_shm12 );
    sem_t *mutex_msg12;
    mutex_msg12 = sem_open( sem_msg12, 0 );
    while( true )
    {
        // Get the Message from Level-1
        sem_wait( mutex_msg12 );
        SetPose( (*msg12_tmp).RobotPose );
        SetGP2Y0A( (*msg12_tmp).GP2Y0A_L, (*msg12_tmp).GP2Y0A_R );
        SetMotionRes( (*msg12_tmp).MotionRes );
        SetSEN1( (*msg12_tmp).SEN1 );
        // if Debug
        //cout << GetGP2Y0A_L() << "--" << GetGP2Y0A_R() << endl;
        //cout << GetMotionRes() << endl;
        sem_post( mutex_msg12 );
    }
}


int  BypassOrAround(float y,float x,int &flag)
{
    if(y>=yINcol+300 || ( y<yINcol && (x-xINcol)*(right_or_left-1)>340 ) || ( yINcol-y>50 && (x-xINcol)*(1-right_or_left)>20 ) )
    {
        preflag=flag;
        cam_mask=1;
        edgemask=0;
        SetAimPose(GetPose());//停止
        usleep(20000);
        poseaim=GetPose();
        if(y>=yINcol+300)//到达下一列
        {
            poseaim.theta=thetaINcol;//转到下一列的位姿角
            xScan1=poseaim.x;
            cout<<"fxz's Cmd_Move_TurnLeft ="<<poseaim<<endl;
            SetAimPose(poseaim);
            while( !IsAimPoseReached() )
            {
                //cout << "Approaching " << tmp << endl;
                usleep(20000);
            }
            cout << "BypassOrAround::Cmd_Move_TurnLeft Reached!" << GetPose() << endl;
            cout<<"BypassOrAround::zfx2 flag=4"<<endl;
            takeImmediately();
            yINcol=GetPose().y;//更新下一列的位姿y
            flag=4;
            cout<<"BypassOrAround::zfx flag=4"<<endl;
        }
        else if((x-xINcol)*(right_or_left-1)>340)
        {
            poseaim.theta=thetaINcol-180;//转回当前列的位姿角
            cout<<"fxz's Cmd_Move_TurnLeft ="<<poseaim<<endl;
            SetAimPose(poseaim);
            xScan1=poseaim.x;
            while(true)
            {
                if(IsAimPoseReached())
                {
                    takeImmediately();
                    yINcol=GetPose().y;
                    thetaINcol-=180;
                    flag=4;
                    break;
                }
                usleep(20000);
            }
        }
        else
        {
            poseaim=GetPose();
            SetAimPose(poseaim);

            // check to Global Planning
            cout<<"need global planning"<<endl;
            pthread_cond_signal(&cond_GPLP);
            pthread_mutex_unlock(&mutex_GPLP);

            usleep(20000);
            pthread_mutex_lock(&mutex_GPLP);
            cout << "Global Planning has Done" << endl;
            vector<pose_t> newGlobalPath = GetGlobalPath();
            cout << "Global Path is: ";

            for( vector<pose_t>::iterator iter = newGlobalPath.begin(); iter != newGlobalPath.end(); iter++ )
            {
                cout << *iter << "-->";
            }
            cout << endl;
            for( vector<pose_t>::iterator iter = newGlobalPath.begin(); iter != newGlobalPath.end(); iter++ )
            {
                pose_t aim = *iter;
                SetAimPose(aim);
                cout << "Approaching " << aim << endl;
                while( !IsAimPoseReached() )
                {
                    //cout << "Approaching " << tmp << endl;
                    usleep(20000);
                }
                cout << aim << " Approached" << endl;
            }
            newGlobalPath.clear();
            SetGlobalPath( newGlobalPath ); // aim pose has reached!

            while(true)
            {
                usleep(20000);
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}


static int outrange(pose_t poseout,int &flag)
{
    float xout=poseout.x-xWHENalong;
    float yout=poseout.y-yWHENalong;
    float disout=xout*xout+yout*yout;
    if(disout>=constDIS*constDIS)
    {
        poseaim=GetPose();
        poseaim.theta=thetaWHENalong;
        SetAimPose(poseaim);
        while(true)
        {
            if(IsAimPoseReached())
            {
                flag=0;
                break;
            }
            usleep(20000);
        }
        cout<<"the pose is outrange"<<endl;
        return 1;
    }
    else
    {
        return 0;
    }
}

static int inrange(pose_t poseout)
{
    float xout=poseout.x-xWHENalong;
    float yout=poseout.y-yWHENalong;
    float disout=xout*xout+yout*yout;
    float constdis2;
    constdis2=constDIS-50>0? constDIS-50:0;
    if(disout<constdis2*constdis2)
    { 
        return 1;
    }
    else
    {
        cout<<"poseout="<<poseout<<endl;
        InRangeFlag=0;
        return 0;
    }
}


void Alongplanning(pose_t posetake ,pair<float,float> *obsttake ,int &cam_mask , int &flag ,int direction)//cleanDirection 0:LEFT 2:RIGHT
{
    if(direction!=0 && direction!=2)//输入检测，输入错误值则程序结束
    {
        cout<<"Alongplanning input error!"<<endl;
        exit(-1);
    }
    pose_t posenow;
    pose_t poseaim;
    pose_t poseturn;
    int crossflag;
    pair<float,float> obstturn[32];
    pair<float,float> obstnow[32];
    float frontnearest,extendnearest,extendfarthest;
    unsigned int frontnearestnum;
    float angle;
    vector<pair<float,float> >frontobst;
    switch(flag)
    {
        case 0: cout<<"now flag="<<flag<<endl;//沿边状态下的直行
                pthread_mutex_lock( &mutex_Take);
                posenow=GetPose();//得到当前位姿
                cout<<"posetake_when_cal="<<posetake<<endl;
                cout<<"pose_when_cal="<<posenow<<endl;
                obst_convert(posetake,posenow,obsttake,obstnow);//算出当前障碍物信息
                pthread_mutex_unlock( &mutex_Take);
                Frontobst(obstnow,frontobst,frontnearest,frontnearestnum,extendnearest,extendfarthest,direction);
                cout<<"frontnearest="<<frontnearest<<" extendnearest="<<extendnearest<<" extendfarthest="<<extendfarthest<<endl;
                if(cam_mask==2)
                {
                    cam_mask=0;
                }
                if(frontnearest<18)
                {
                    cam_mask=2;
                    angle=AngleANDLengthGet(frontobst,turnlength,frontnearestnum,2-direction,frontnearest);
                    turnlength+=1;
                    if(frontnearest-3<0)
                    {
                        frontnearest=3;
                    }
                    poseaim=GetPose();
                    if(needLookRound(poseaim,frontnearest*10-30,2-right_or_left))
                    {
                        cam_mask=1;
                        poseaim.theta=thetaWHENalong+(right_or_left-1)*45;
                        SetAimPose(poseaim);
                        while(true)
                        {
                            if(IsAimPoseReached())
                            {
                                cam_mask = 1;
                                takeImmediately();
                                cam_mask=2;
                                break;
                            }
                            usleep(20000);
                        }
                        poseaim.theta=thetaWHENalong;
                        SetAimPose(poseaim);
                        while(true)
                        {
                            if(IsAimPoseReached())
                            {
                                break;
                            }
                            usleep(20000);
                        }
                    }
                    poseaim.x+=(frontnearest*10-30)*cos(poseaim.theta*3.14/180);
                    poseaim.y+=(frontnearest*10-30)*sin(poseaim.theta*3.14/180);
                    SetAimPose(poseaim);
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            thetaWHENalong+=(direction-1)*angle;//转弯沿边位姿角改变
                            poseaim.theta=thetaWHENalong;
                            SetAimPose(poseaim);
                            //num++;
                            while(true)
                            {
                                if(IsAimPoseReached())
                                {
                                    if(turnlength<=15)
                                    {
                                        flag=0;
                                    }
                                    else
                                    {
                                        constDIS=(turnlength-15+3)*10;
                                        xWHENalong=poseaim.x;
                                        yWHENalong=poseaim.y;
                                        InRangeFlag=1;
                                        flag=1;
                                    }
                                    cout<<"0_1_1"<<endl;
                                    break;
                                }
                                usleep(20000);
                            }
                            break;
                        }
                        if(BypassOrAround(GetPose().y,GetPose().x,flag)==1)
                        {
                            cout<<"0_1_2"<<endl;
                            break;
                        }
                        usleep(20000);
                    }
                } 
                else if(frontnearest<=40 && frontnearest>=18)
                {
                    if(Infrared_decoder(GetGP2Y0A(direction))==1)
                    {
                        turnlength=15;
                        if(frontnearest-17<5)
                        {
                            poseaim=GetPose();
                            poseaim.x+=50*cos(poseaim.theta*3.14/180);
                            poseaim.y+=50*sin(poseaim.theta*3.14/180);
                            poseaim.theta=thetaWHENalong;//直行角度不变
                            SetAimPose(poseaim);
                        }
                        else
                        {
                            poseaim=GetPose();
                            poseaim.x+=((frontnearest-17)*10)*cos(poseaim.theta*3.14/180);
                            poseaim.y+=((frontnearest-17)*10)*sin(poseaim.theta*3.14/180);
                            poseaim.theta=thetaWHENalong;//直行角度不变
                            SetAimPose(poseaim);
                        }
                        //num++;
                        while(true)
                        {
                            if(Infrared_decoder(GetGP2Y0A(direction))==0)
                            {
                                poseaim=GetPose();
                                poseaim.theta=thetaWHENalong;//停止角度应为沿边位姿角
                                SetAimPose(poseaim);
                                while(true)
                                {
                                    if(IsAimPoseReached())
                                    {
                                        break;
                                    }
                                    usleep(20000);
                                }
                                if(sqrt((GetPose().x-posenow.x)*(GetPose().x-posenow.x)+(GetPose().y-posenow.y)*(GetPose().y-posenow.y))>=(frontnearest-17)*10)
                                {
                                    flag=0;
                                }
                                else
                                {
                                    if(Infrared_decoder(GetGP2Y0A(direction))==0)//两次检测，两次结果一样才正确
                                    {
                                        flag=2;
                                    }
                                    else
                                    {
                                        flag=0;
                                        turnlength=15;
                                    }
                                }
                                cout<<"0_2_1"<<endl;
                                break;    
                            }
                            if(IsAimPoseReached())
                            {
                                flag=0;
                                cout<<"0_2_2"<<endl;
                                break;
                            }
                            if(BypassOrAround(GetPose().y,GetPose().x,flag)==1)
                            {
                                cout<<"0_2_3"<<endl;
                                break;
                            }
                            usleep(20000);
                        }
                    }
                    else
                    {
                        flag=2;
                        cout<<"0_2_4"<<endl;
                    }
                }
                else
                {
                    if(Infrared_decoder(GetGP2Y0A(direction))==1)
                    {
                        turnlength=15;
                        pose_t poseaim=GetPose();
                        poseaim.x+=100*cos(poseaim.theta*3.14/180);
                        poseaim.y+=100*sin(poseaim.theta*3.14/180);
                        poseaim.theta=thetaWHENalong;//直行角度不变
                        SetAimPose(poseaim);
                        //num++;
                        while(true)
                        {
                            if(Infrared_decoder(GetGP2Y0A(direction))==0)
                            {
                                poseaim=GetPose();
                                poseaim.theta=thetaWHENalong;
                                SetAimPose(poseaim);//停止角度应为沿边位姿角
                                while(true)
                                {
                                    if(IsAimPoseReached())
                                    {
                                        if(Infrared_decoder(GetGP2Y0A(direction))==0)//两次检测，两次结果一样才正确
                                        {
                                            flag=2;
                                        }
                                        else
                                        {
                                            flag=0;
                                            turnlength=15;
                                        }
                                        break;
                                    }
                                    usleep(20000);
                                }
                                cout<<"0_3_2"<<endl;
                                break;
                            }
                            if(IsAimPoseReached())
                            {
                                flag=0;
                                cout<<"0_3_1"<<endl;
                                break;
                            }
                            if(BypassOrAround(GetPose().y,GetPose().x,flag)==1)
                            {
                                cout<<"0_3_3"<<endl;
                                break;
                            }
                            usleep(20000);
                        }
                    }
                    else
                    {
                        flag=2;
                        cout<<"0_3_4"<<endl;
                        //break;     
                    }
                }
                cout<<"next flag="<<flag<<endl;
                break; 
        case 1: cout<<"now flag="<<flag<<endl;//沿边状态下的直行
                pthread_mutex_lock( &mutex_Take);
                posenow=GetPose();
                cout<<"posetake_when_cal="<<posetake<<endl;
                cout<<"pose_when_cal="<<posenow<<endl;
                obst_convert(posetake,posenow,obsttake,obstnow);
                pthread_mutex_unlock( &mutex_Take);
                edgemask=0;
                Frontobst(obstnow,frontobst,frontnearest,frontnearestnum,extendnearest,extendfarthest,direction);
                cout<<"frontnearest="<<frontnearest<<" extendnearest="<<extendnearest<<" extendfarthest="<<extendfarthest<<endl;
                if(cam_mask==2)
                {
                    cam_mask=0;
                }
                cout<<"constDIS="<<constDIS<<endl;
                if(frontnearest<18)
                {
                    cam_mask=2;
                    angle=AngleANDLengthGet(frontobst,turnlength,frontnearestnum,2-direction,frontnearest);
                    turnlength+=1;
                    if(frontnearest-3<0)
                    {
                        frontnearest=3;
                    }
                    poseaim=GetPose();
                    if(needLookRound(poseaim,frontnearest*10-30,2-right_or_left))
                    {
                        cam_mask=1;
                        poseaim.theta=thetaWHENalong+(right_or_left-1)*45;
                        SetAimPose(poseaim);
                        while(true)
                        {
                            if(IsAimPoseReached())
                            {
                                cam_mask = 1;
                                takeImmediately();
                                cam_mask=2;
                                break;
                            }
                            usleep(20000);
                        }
                        poseaim.theta=thetaWHENalong;
                        SetAimPose(poseaim);
                        while(true)
                        {
                            if(IsAimPoseReached())
                            {
                                break;
                            }
                            usleep(20000);
                        }
                    }
                    poseaim.x+=(frontnearest*10-30)*cos(poseaim.theta*3.14/180);
                    poseaim.y+=(frontnearest*10-30)*sin(poseaim.theta*3.14/180);
                    SetAimPose(poseaim);
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            thetaWHENalong+=(direction-1)*angle;
                            poseaim.theta=thetaWHENalong;//转弯改变沿边位姿角
                            SetAimPose(poseaim);
                            //num++;
                            while(true)
                            {
                                if(IsAimPoseReached())
                                {
                                    if(turnlength<=16)
                                    {
                                        flag=0;
                                    }
                                    else
                                    {
                                        constDIS=(turnlength-15+3)*10;
                                        xWHENalong=poseaim.x;
                                        yWHENalong=poseaim.y;
                                        InRangeFlag=1;
                                        flag=1;
                                    }
                                    cout<<"1_1_1"<<endl;
                                    break;
                                }
                                usleep(20000);
                            }
                            break;
                        }
                        if(BypassOrAround(GetPose().y,GetPose().x,flag)==1)
                        {
                            cout<<"1_1_2"<<endl;
                            break;
                        }
                        /*if(outrange(GetPose(),flag)==1)
                        {
                            cout<<"1_1_3"<<endl;
                            break;
                        }*/
                        usleep(20000);
                    }
                } 
                else if(frontnearest<=40 && frontnearest>=18)
                {
                    if(frontnearest-17<5)
                    {
                        pose_t poseaim=GetPose();
                        poseaim.x+=50*cos(poseaim.theta*3.14/180);
                        poseaim.y+=50*sin(poseaim.theta*3.14/180);
                        poseaim.theta=thetaWHENalong;//直行角度不变
                        SetAimPose(poseaim);
                    }
                    else
                    {
                        pose_t poseaim=GetPose();
                        poseaim.x+=((frontnearest-17)*10)*cos(poseaim.theta*3.14/180);
                        poseaim.y+=((frontnearest-17)*10)*sin(poseaim.theta*3.14/180);
                        poseaim.theta=thetaWHENalong;//直行角度不变
                        SetAimPose(poseaim);
                    }
                    //num++;
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            flag=1;
                            cout<<"1_2_2"<<endl;
                            break;
                        }
                        if(BypassOrAround(GetPose().y,GetPose().x,flag)==1)
                        {
                            cout<<"1_2_3"<<endl;
                            break;
                        }
                        if(InRangeFlag==1 && inrange(GetPose())==1)
                        {
                            continue;
                        }
                        if(Infrared_decoder(GetGP2Y0A(direction))==1)
                        {
                            poseaim=GetPose();
                            poseaim.theta=thetaWHENalong;//停止角度应为沿边位姿角
                            SetAimPose(poseaim);
                            while(true)
                            {
                                //cout<<"isaimposereached="<<IsAimPoseReached()<<endl;
                                if(IsAimPoseReached())
                                {
                                    if(Infrared_decoder(GetGP2Y0A(direction))==1)//两次检测
                                    {
                                        flag=0;
                                    }
                                    else
                                    {
                                        flag=1;
                                    }
                                    break;
                                }
                                usleep(20000);
                            }
                            cout<<poseaim<<endl;
                            cout<<"1_2_1"<<endl;
                            break;    
                        }
                        if(outrange(GetPose(),flag)==1)
                        {
                            cout<<"1_2_4"<<endl;
                            break;
                        }
                        usleep(20000);
                    }
                }
                else
                {
                    //usleep(20000);
                    pose_t poseaim=GetPose();
                    poseaim.x+=100*cos(poseaim.theta*3.14/180);
                    poseaim.y+=100*sin(poseaim.theta*3.14/180);
                    poseaim.theta=thetaWHENalong;//直行角度不变
                    SetAimPose(poseaim);
                    //num++;
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            flag=1;
                            cout<<"1_3_1"<<endl;
                            break;
                        }
                        if(BypassOrAround(GetPose().y,GetPose().x,flag)==1)
                        {
                            cout<<"1_3_3"<<endl;
                            break;
                        }
                        if(InRangeFlag==1 && inrange(GetPose())==1)
                        {
                            continue;
                        }
                        if(Infrared_decoder(GetGP2Y0A(direction))==1)
                        {
                            poseaim=GetPose();
                            poseaim.theta=thetaWHENalong;
                            SetAimPose(poseaim);//停止角度应为沿边位姿角
                            while(true)
                            {
                                if(IsAimPoseReached())
                                {
                                    if(Infrared_decoder(GetGP2Y0A(direction))==1)//两次检测
                                    {
                                        flag=0;
                                    }
                                    else
                                    {
                                        flag=1;
                                    }
                                    break;
                                }
                                usleep(20000);
                            }
                            cout<<"1_3_2"<<endl;
                            break;
                        }
                        if(outrange(GetPose(),flag)==1)
                        {
                            cout<<"1_3_4"<<endl;
                            break;
                        }
                        usleep(20000);
                    }
                }
                cout<<"next flag="<<flag<<endl;
                break;
        case 2: cout<<"now flag="<<flag<<endl;//沿边状态下的绕行
                cout<<"turnlength="<<turnlength<<endl;
                crossflag=0;
                posenow=GetPose();
                poseaim=posenow;
                poseaim.theta=thetaWHENalong+(1-direction)*45;
                SetAimPose(poseaim);//往可能存在的绕行方向转45度
                if(turnlength>18)
                {
                    turnlength=18;
                }
                if(turnlength<0)
                {
                    turnlength=0;
                }
                cam_mask=1;
                while(true)
                {
                    if(IsAimPoseReached())
                    {
                        takeImmediately();
                        poseturn=poseaim;
                        for(int i=0;i<32;i++)
                        {
                            obstturn[i]=obsttake[i];
                        }
                        
                        break;
                    }
                    usleep(20000);
                }
                posenow.theta=thetaWHENalong;
                SetAimPose(posenow);//转回当前位姿
                obst_convert2(poseturn,posenow,obstturn,obstnow,1);
                Frontobst(obstnow,frontobst,frontnearest,frontnearestnum,extendnearest,extendfarthest,direction);
                cout<<"frontnearest="<<frontnearest<<" extendnearest="<<extendnearest<<" extendfarthest="<<extendfarthest<<endl;
                while(true)
                {
                    if(IsAimPoseReached())
                    {
                        if(extendnearest<turnlength+2)
                        {
                            cout<<"2_1_1"<<endl;
                            constDIS=(17+extendnearest+3)*10;
                            InRangeFlag=1;
                            xWHENalong=posenow.x;
                            yWHENalong=posenow.y;
                            flag=1;
                            turnlength=15;
                        }
                        else
                        {
                            crossflag=1;
                        }
                        break;
                    }
                    usleep(20000);
                }
                if(crossflag==1)
                {
                    pose_t poseaim=GetPose();
                    poseaim.x+=(turnlength*10)*cos(poseaim.theta*3.14/180);
                    poseaim.y+=(turnlength*10)*sin(poseaim.theta*3.14/180);
                    poseaim.theta=thetaWHENalong;//直行角度不变
                    SetAimPose(poseaim);
                    while(true)
                    {
                        if(IsAimPoseReached())
                        {
                            cam_mask=1;
                            cout<<"cam mask!"<<endl;
                            thetaWHENalong+=(1-direction)*90;//可绕行，往绕行方向转90度，沿边位姿角改变
                            poseaim.theta=thetaWHENalong;
                            SetAimPose(poseaim);
                            //num++;
                            while(true)
                            {
                                if(IsAimPoseReached())
                                {
                                    takeImmediately();
                                    xWHENalong=poseaim.x;
                                    yWHENalong=poseaim.y;
                                    constDIS=220;
                                    InRangeFlag=1;
                                    flag=1;
                                    break;
                                }
                                usleep(20000);
                            }
                            break;
                        }
                        if(Infrared_decoder(GetGP2Y0A(direction))==1)//不能绕行
                        {
                            poseaim=GetPose();
                            poseaim.theta=thetaWHENalong;
                            SetAimPose(poseaim);//停止角度应为沿边位姿角
                            while(true)
                            {
                                if(IsAimPoseReached())
                                {
                                    break;
                                }
                                usleep(20000);
                            }
                            //num++;
                            edgemask=0;
                            flag=0;
                            turnlength=15;
                            cout<<"2_2_2"<<endl;
                            break;
                        }
                        if(GetGP2Y0A(direction)>=1800 && GetGP2Y0A(direction)<=2100)//侧边障碍物较近
                        {
                            edgemask=1;//屏蔽边缘检测
                        }
                        if(BypassOrAround(GetPose().y,GetPose().x,flag)==1)
                        {
                            cout<<"2_2_3"<<endl;
                            break;
                        }
                        usleep(20000);
                    }
                }
                turnlength=15;
                cout<<"next flag="<<flag<<endl;
                break;
    }
}

/**********************************************************************************/
/**************************************************************/
 // @Module Name       : Mapping
 // @Module Author     : LiMin
 // @Module History    : 
 //     1. Created By LiMin @ 2017-03-22.
 //     2. Modified By LiMin @ 2017-04012:
 //         1. Check the work-flow of the mapping module;
 //         2. Correct the map update models( compact/infrade/camera )
 // 
 // @Module Description: 
 //     This module is used to build the grid map of the robot workspace.
 // 
 //     
 //
/**************************************************************/
vector<Point> GetInfradeObstacles( pose_t currPose, int gridSize )
{
    int disL = GetGP2Y0A_L();
    int disR = GetGP2Y0A_R();
    const int threshold = 2000;
    vector<Point> Res;
    if( disL < threshold && disR < threshold )
    {
        // No Infrade detected
        Res.clear();
        return Res; 
    }
    else if( disL >= threshold && disR < threshold )
    {
        // Lefe Infrade detected
        Res.clear();
        //cout << "Left Infrade!" << endl;
        Point tmpL1 = GridLocaltoMapIndex( Point(0, 5), currPose, gridSize );
        Point tmpL2 = GridLocaltoMapIndex( Point(0, 6), currPose, gridSize );
        Res.push_back(tmpL1);
        Res.push_back(tmpL2);
        return Res;
    }
    else if( disL < threshold && disR >= threshold )
    {
        // Right Infrade detected
        Res.clear();
        //cout << "Right Infrade!" << endl;
        Point tmpL1 = GridLocaltoMapIndex( Point(0, -5), currPose, gridSize );
        Point tmpL2 = GridLocaltoMapIndex( Point(0, -6), currPose, gridSize );
        Res.push_back(tmpL1);
        Res.push_back(tmpL2);
        return Res; 
    }
    else
    {
        // Both Infrade detected
        Res.clear();
        //cout << "Both Infrade!" << endl;
        Point tmpL1 = GridLocaltoMapIndex( Point(0, 5), currPose, gridSize );
        Point tmpL2 = GridLocaltoMapIndex( Point(0, 6), currPose, gridSize );
        Point tmpL3 = GridLocaltoMapIndex( Point(0, -5), currPose, gridSize );
        Point tmpL4 = GridLocaltoMapIndex( Point(0, -6), currPose, gridSize );
        Res.push_back(tmpL1);
        Res.push_back(tmpL2);
        Res.push_back(tmpL3);
        Res.push_back(tmpL4);
        return Res; 
    }
}

vector<Point> CompactObstaclesLeft = {Point(2,4), Point(3,4), Point(4,3), Point(4,2), Point(5,2)};
vector<Point> CompactObstaclesRight = {Point(2,-4), Point(3,-4), Point(4,-3), Point(4,-2), Point(5,-2)};
vector<Point> CompactObstaclesBoth = {Point(5,1), Point(5,0), Point(5,-1)};
vector<Point> GetCompactObstacles( pose_t currPose, int gridSize )
{
    unsigned char sen1 = GetSEN1() & 0xc0;
    vector<Point> Res;
    if( sen1 == 0x80 )
    {
        // Left Compact
        vector<Point>::const_iterator iter;
        for( iter = CompactObstaclesLeft.begin(); iter != CompactObstaclesLeft.end(); iter++ )
        {
            Res.push_back( GridLocaltoMapIndex( *iter, currPose, gridSize ) );
        }
        return Res;
    }
    else if( sen1 == 0x40 )
    {
        // Right Compact
        vector<Point>::iterator iter;
        for( iter = CompactObstaclesRight.begin(); iter != CompactObstaclesRight.end(); iter++ )
        {
            Res.push_back( GridLocaltoMapIndex( *iter, currPose, gridSize ) );
        }
        return Res;
    }
    else if( sen1 == 0xc0 )
    {
        // Both Compact
        vector<Point>::iterator iter;
        for( iter = CompactObstaclesBoth.begin(); iter != CompactObstaclesBoth.end(); iter++ )
        {
            Res.push_back( GridLocaltoMapIndex( *iter, currPose, gridSize ) );
        }
        return Res;
    }
    else
    {
        // No Compact
        Res.clear();
        return Res;
    }
}

CameraMapModel_t GetFrontCameraMap(int gridSize )
{
    CameraMapModel_t Res;
    vector<Point> Ocp;
    vector<Point> Free;
    cout << "Get Front Camera map update model..." << endl;
    pthread_mutex_lock( &mutex_Take );
    pose_t currPose = posetake;
    cout << "mapping--Pose" << currPose << endl;
    for (unsigned int i=0; i<32; i++)
    {
        if( obsttake[i].first<=50 && obsttake[i].first>=0 )
        {
            // Local Position temp
            Point PhyLocation( 10*(obsttake[i].first+15), 10*obsttake[i].second );
            Point obst_Grid = toGrid( PhyLocation, gridSize );
            //Ocp.push_back( obst_Grid );
            if( Ocp.empty() )
            {
                cout << "Ocp Grid in Robot Coordinate: " << obst_Grid << endl;
                Ocp.push_back(obst_Grid);
            }
            else
            {
                if( obst_Grid != Ocp.back() )
                {
                    cout << "Ocp Grid in Robot Coordinate: " << obst_Grid << endl;
                    Ocp.push_back(obst_Grid);
                }
            }

        }
    }
    pthread_mutex_unlock( &mutex_Take);
    //cout << "mapping--Total Ocp Girds: " << Ocp.size() << endl;

    if( Ocp.empty() )
    {
        // Front Camera obstacles detected may failed, abound this frame
        Ocp.clear();
        Free.clear();
        Res.OcpGrid = Ocp;
        Res.FreeGrid = Free;
        return Res;
    }
    else
    {
        // This frame is valid
        vector<float> angleSegment;
        vector<int> lenThreshold;
        // grid is used to store the ocp state
        int grid[12][15];
        for( int i = 0; i < 12; i++ )
        {
            for( int j = 0; j < 15; j++ )
            {
                grid[i][j] = 0;
            }
        }

        // Search all the OCP grids: get the angle segment
        int minLength = 225;
        for( int i = 0; i<Ocp.size(); i++ )
        {
            if( Ocp.size() == 1 )
            {
                Point cur = Ocp.at(i);
                float angle1 = atan2f(cur.y-0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle1);
                minLength = 225;

                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                minLength = minLength <= len ? minLength : len;
                
                //cout << minLength << endl;

                float angle2 = atan2f(cur.y+0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle2);
                lenThreshold.push_back( minLength );
                break;
            }

            if( i == 0 )
            {
                Point cur = Ocp.at(i);
                float angle1 = atan2f(cur.y-0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle1);
                minLength = 225;
                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                minLength = minLength <= len ? minLength : len;
                
                //cout << minLength << endl;
            }
            else if( i == Ocp.size()-1 )
            {
                Point cur = Ocp.at(i);
                float angle2 = atan2f(cur.y+0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle2);
                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                minLength = minLength <= len ? minLength : len;
                //cout << minLength << endl;
                lenThreshold.push_back( minLength );
            }
            else
            {
                Point cur = Ocp.at(i);
                Point next = Ocp.at(i+1);
                float x = next.x - cur.x;
                float y = next.y - cur.y;
                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                if( x*x+y*y > 2 )
                {
                    // Not Border Upon
                    float angle2 = atan2f(cur.y+0.5, cur.x-4) * 180/3.14;
                    int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                    minLength = minLength <= len ? minLength : len;
                    //cout << minLength << endl;

                    angleSegment.push_back(angle2);
                    lenThreshold.push_back( minLength );

                    float angle1 = atan2f(next.y-0.5, next.x-4) * 180/3.14;
                    angleSegment.push_back(angle1);
                    minLength = 225;
                }
                else
                {
                    minLength = minLength <= len ? minLength : len;
                    //cout << minLength << endl;
                }
            }
        }

        //cout << "segment size: " << angleSegment.size() << endl;
        //cout << "len size: " << lenThreshold.size() << endl;
        //for( int k=0; k<angleSegment.size()/2; k++)
        //{
        //    cout << "len:" << lenThreshold.at(k) << angleSegment.at(2*k) << "~" << angleSegment.at(2*k+1) << endl;
        //}

        for( int i = 5; i <= 15; i++ )
        {
            int Maxj = i<=11 ? i-4 : 19-i;
            for( int j = -Maxj; j <= Maxj; j++ )
            {
                //cout << i << "--" << j << "=" << 180/3.14*atan2f(j, i-4) << endl;
                float angleTest = atan2f(j, i-4) * 180/3.14;
                int len = j*j + (i-4)*(i-4);
                for( int k=0; k<angleSegment.size()/2; k++)
                {
                    //cout << angles.at(2*i) << "~" << angles.at(2*i+1) << endl;
                    if( angleTest >= angleSegment.at(2*k) && angleTest <= angleSegment.at(2*k+1))
                    {
                        if( len > lenThreshold.at(k) )
                        {
                            grid[i-4][j+7] = 3;
                        }
                    }
                }
            }
        }

        // Add the obstacle grids
        for( int i = 0; i<Ocp.size(); i++ )
        {
            Point cur = Ocp.at(i);
            grid[cur.x-4][cur.y+7] = 1;
        }

        //for( int i = 11; i >=0; i-- )
        //{
        //    for( int j = 0; j < 15; j++ )
        //    {
        //        cout << grid[i][j];
        //    }
        //    cout << endl;
        //}
        
        vector<Point> FreeGrids;
        vector<Point> ObstGrids;
        for( int i = 5; i <= 15; i++ )
        {
            int Maxj = i<=11 ? i-4 : 19-i;
            for( int j = -Maxj; j <= Maxj; j++ )
            {
                if( grid[i-4][j+7] == 0 )
                {
                    FreeGrids.push_back( GridLocaltoMapIndex( Point(i,-j), currPose, gridSize ) );
                }
                else if( grid[i-4][j+7] == 1 )
                {
                    ObstGrids.push_back( GridLocaltoMapIndex( Point(i,-j), currPose, gridSize ) );
                }
            }
        }
        Res.OcpGrid = ObstGrids;
        Res.FreeGrid = FreeGrids;
    }
    return Res;
}

void* pThread_MapUpdate( void*argv )
{
    // Global Grid Map Initialization: Load and Set the Map Attributes
    // Robot related const values
    const int Robot_Radius_g = 4; // 4 Grids

    // Mapping thread logger 
    log_t log( "./logs/MapUpdate"+time_filename_str(), "Grid Map Update Module By LiMin" );
    log.fs(INFO) << "mapping thread Initializing... " << endl;
    // Mapping Module Initialization
    // Create a Grid Map object, the map size is define by (GridMapSizeX, GridMapSizeY)
    //unsigned int GridMapSizeX = 500;
    //unsigned int GridMapSizeY = 500;
    //Grid_Map_t mapData( GridMapSizeX, GridMapSizeY );
    Map_Attr_t mapAttr = mapData.GetAttr();
    log.fs(INFO) << "grid map object created with size: " << Size( GridMapSizeX, GridMapSizeY ) << endl;
    
    // Occupied stat map filename format: ./GridMapHis/ocpMap_<time_stamp>.jpg
    // Scan count map filename format: ./GridMapHis/cntMap_<time_stamp>.jpg
    // Note-1: the prefix--<ocp_/cnt_> and suffix--<.jpg> will be auto added while using Save() function
    // Note-2: <time_stamp> can be generated with function string time_stamp_str(void);
    // Check subdirectory "./GridMapHis" whether exist, if not create it while mode 777
    string path_str = "MapSnapShoots";
    if( DeleteDir( path_str.c_str() )!=0 )
    {
        log.fs(ERROR) << "Failed to delete the old map files!" << endl;
        log.fs(FATAL) << "mapping thread will not work!!!" << endl;
        // cancel the thread
    }
    if( !CreateDir( path_str.c_str() ) )
    {
        log.fs(ERROR) << "Failed to create the map store directory!" << endl;
        log.fs(FATAL) << "mapping thread will not work!!!" << endl;
        // cancel the thread
    }
    log.fs(INFO) << "\n Map Snap shoot images stored in directory : " << path_str << endl;

    // Robot path history will be recored in value vector<Point> pathHis in the format of grid map position
    // Note-1: gird map position can be transformed from robot pose through function Point pose2grid( pose_t, Map_Attr_t )
    vector<Point> pathHis;
    vector<pose_t> poseHis;
    // Robot current position in the grid map
    Point currPosition;
    pose_t currPose;
    Point lastConfirmedPosition;
    pose_t lastConfirmedPose;
    // Obstacle's position around the robot
    vector<Point> ObstacleCompact;
    vector<Point> ObstacleInfrade; 
    vector<Point> ObstacleFrontCamera;
    vector<Point> FrontCameraFreeGrid;

    bool flag_map_adjust_request = false;

    log.fs(INFO) << "mapping module start to work!" << endl;

    unsigned int cnt_Front = 0;
    double Start_Runtime = (double)cv::getTickCount()/cv::getTickFrequency();
    double Total_Runtime = 0;
    int tickCNT = 0;
    while( true )
    {

        mapAttr = mapData.GetAttr();

        ObstacleCompact.clear();
        ObstacleInfrade.clear();
        ObstacleFrontCamera.clear();
        FrontCameraFreeGrid.clear();
        // Step-1: Update robot current position
        currPose = GetPose();
        currPosition = pose2grid( currPose, mapAttr );

        pathHis.push_back( currPosition ); // Record the path history
        poseHis.push_back( currPose );     // Record the pose history

        // Step-0: If IMU Location Accumulative Error if big enough to Adjust the Old Path Map
        if( flag_map_adjust_request )
        {
            log.fs(WARNING) << "Adjusting map data for history localization error detected!" << endl;
            // Adjust the map ROI:
            // Search the pathHis to get the path between currPosition and lastConfirmedPosition
            // Adjust the map in the path
            lastConfirmedPosition = currPosition;
            lastConfirmedPose = currPose;
            log.fs(WARNING) << "Modify the Grid map at "
                            << "Physical Pose: " << lastConfirmedPose
                            << "Map Position: "  << lastConfirmedPosition
                            << endl;
            continue;
        }
    /***************************************************/
    //--*Start*-- Prepare the obstacles data
        // Get the Obstacles if compact detected
        ObstacleCompact = GetCompactObstacles(currPose, mapAttr.map_grid_size);
        log.fs(INFO) << "Compact Grids: " << ObstacleCompact.size() << endl;
        // Get the Obstacles if infraded detect obstacles
        ObstacleInfrade = GetInfradeObstacles(currPose, mapAttr.map_grid_size);
        log.fs(INFO) << "Infrade Grids: " << ObstacleCompact.size() << endl;
        // Get the Obstacles if front Camera detect obstacles
        if( flagFrontImageUpdate )
        {
            CameraMapModel_t cameraMap = GetFrontCameraMap(mapAttr.map_grid_size);
            ObstacleFrontCamera = cameraMap.OcpGrid;
            FrontCameraFreeGrid = cameraMap.FreeGrid;
            log.fs(INFO) << "Camera obstacles Grids: " << ObstacleCompact.size() << endl;
            flagFrontImageUpdate = false;
            cnt_Front++;
        }
            
    //--*End*-- Prepare the obstacles data
    /***************************************************/

    /***************************************************/
    //--*Start*-- Update the Grid Map
        // update the area inner the robot body : update both occupied map and scan map
        mapData.fill_circle( currPosition, Robot_Radius_g, CellUnknown+100, 1 );

        // update the area outside the robot body : Only update the occupied map
        // Version 1: violence update
        mapData.fill( ObstacleCompact, CellUnknown-100, 0 );
        mapData.fill( ObstacleInfrade, CellUnknown-100, 0 );
        if( !ObstacleFrontCamera.empty() )
        {
            mapData.fill( ObstacleFrontCamera, CellUnknown-100, 0 );
            if( !FrontCameraFreeGrid.empty() )
            {
                // fill the freedom area front of the robot
                mapData.fill( FrontCameraFreeGrid, CellUnknown+100, 0 );
            }
            /*
            cout << "Map Update at Physical Pose: " << currPose << "--Grid Position: " << currPosition << endl;
            vector<Point>::iterator iter;
            for( iter=ObstacleFrontCamera.begin(); iter!=ObstacleFrontCamera.end(); iter++ )
            {
                cout << *iter << endl;
            }*/
        }
    //--*End*-- Update the Grid Map
    /***************************************************/

    /***************************************************/        
    //--*Start*-- log the mapping module statistic information
        /*
        log.fs(INFO) << "Map Update at Physical Pose: " << currPose << "--Grid Position: " << currPosition
                     << "\n\t Compact Obstacle Count: " << ObstacleCompact.size()
                     << "\n\t Infrade Obstacle Count: " << ObstacleInfrade.size()
                     << "\n\t Front Obstacle Count  : " << ObstacleFrontCamera.size()
                     << endl;
        */
        Total_Runtime = (double)cv::getTickCount()/cv::getTickFrequency() - Start_Runtime;        
        tickCNT++;
        if(tickCNT%50 == 0 )
        {
            log.fs(INFO) << "Mapping Module statistic information: " 
                         << "\n\t Map Update Frequency(Hz): " << tickCNT/Total_Runtime
                         << "\n\t Front Obstacles Update Frequency(Hz): " << cnt_Front/Total_Runtime
                         << endl;
            /*log.fs(ORI) << "\n\tPath history information: "
                        << "\n\t poseHis size: " << poseHis.size();
            vector<pose_t>::iterator iter;
            for(iter = poseHis.begin(); iter != poseHis.end(); iter++ )
            {
                if( iter==poseHis.begin() )
                    log.fs(ORI) << "\n\t Start: " << *iter << "-->";
                else if(iter==poseHis.end()-1)
                    log.fs(ORI) << *iter << endl;
                else
                    log.fs(ORI) << *iter << "-->";
            }
            */

            // Save the map snap shoot images
            string filename = time_filename_str();
            double t1=(double)getTickCount();
            mapData.Save( path_str, filename );
            double t2=(double)getTickCount();
            double time = (t2-t1)/getTickFrequency();
            log.fs(ORI) << "\n\t Save Map Time Usage: " << time << "s."
                                << "\n map name: " << filename
                                << endl;
        }

    //--*End*-- log the mapping module statistic information
    /***************************************************/        
        usleep(20000);
    } // --*while*--
    return NULL;
}
// This is the end of Module Grid Map update 
// --*END*--
/*****************************************************************************/


/**********************************************************************************/
/**************************************************************/
 // @Module Name       : Front Camera capture
 // @Module Author     : LiMin & FangXiazhang
 // @Module History    : 
 //     1. Created By FangXiazhang;
 //     2. Modified By LiMin @ 2017-03-22, add camera synchronization; Add log files
 //     3. Modified By LiMin @ 2017-03-27, add statistic information
 // 
 // @Module Description: 
 //     This thread is used to capture photos of front camera.
 // 
 //     
 //
/**************************************************************/

void* pThread_TAKE_Photo( void *argv )
{
    log_t log("./logs/Level2_take_photo"+time_filename_str(), "Fang Xiazhang");

    string path_str = "frontImages";
    if( DeleteDir( path_str.c_str() )!=0 )
    {
        log.fs(ERROR) << "Failed to delete the old frontImages files!" << endl;
        // cancel the thread
    }
    if( !CreateDir( path_str.c_str() ) )
    {
        log.fs(ERROR) << "Failed to create the frontImages store directory!" << endl;
        // cancel the thread
    }
    Mat image;
    float distance[32];
    vector<pair<float,float> >frontobst;

    mutex_takephoto = sem_open( Sem_Name_takephoto, 0 );
    
    log.fs(INFO) << "Checking whether the video device initialized of not..." << endl;
    if(getframefxz.hasinit==0)
    {
        getframefxz.init();
        log.fs(WARNING) << "Initializing the video device..." << endl;
    }
    else
    {
        log.fs(WARNING) << "video device has been initialized by others!!!" << endl;
    }

    log.fs(INFO) << "take photo thread start to work..." << endl;

    unsigned int cnt_TotalFrames = 0;
    double Start_Runtime = (double)cv::getTickCount()/cv::getTickFrequency();
    double Total_Runtime = 0;
    double Taking_time = 0;
    int tickCNT = 0;

    while(true)
    {
        if(cam_mask==2)
        {
            continue;
        }
        if(cam_mask==1)
        {
            pthread_mutex_lock(&mutex1);
            if(signaled1==0)
            {
                pthread_cond_wait(&cond1,&mutex1);//等待拍照信号
            }
            cam_mask=0;
            takeok=1;
            pthread_mutex_unlock(&mutex1);
            cout<<"pThread_TAKE_Photo::cond1 received!"<<endl;
            image = GetFrontFrame();
            grayaver=aver(image);
            getframefxz.changeExposureValue(setExposureValue(getframefxz.getExposureValue(),grayaver));
            cout<<"grayaver="<<grayaver<<" exposure value="<<getframefxz.getExposureValue()<<endl;
        }
        if(cam_mask==0)
        {   
            cout<<"pThread_TAKE_Photo::takeok="<<takeok<<endl;
            // Use semaphore to synchronize the two cameras
            // Modified by limin @ 2017-03-08
            double t1=(double)getTickCount();
            image = GetFrontFrame();
            double t2=(double)getTickCount();
            double time = (t2-t1)/getTickFrequency();
            cnt_TotalFrames++;
            Taking_time += time;

            Mat image_clone = image.clone();
            
            pthread_mutex_lock( &mutex_Take );
            posetake=GetPose();
            //cout<<"posetake"<<posetake<<endl;
            grayaver=distance_measure(image, distance,edgemask);
            getframefxz.changeExposureValue(setExposureValue(getframefxz.getExposureValue(),grayaver));
            cout<<"grayaver="<<grayaver<<" exposure value="<<getframefxz.getExposureValue()<<endl;
            distance_decoder(distance,obsttake);
            flagFrontImageUpdate = true; 
            pthread_mutex_unlock( &mutex_Take);

            // If debug
            string time_stamp = "./frontImages/" + time_filename_str();
            imwrite( time_stamp+".jpg" , image_clone );
            log.fs(INFO) << "filename: " << time_stamp+".jpg" << posetake << endl;
        }
        if(takeok==1)
        {
            pthread_mutex_lock(&mutex2);
            takeok=0;
            signaled2=1;
            pthread_mutex_unlock(&mutex2);
            pthread_cond_signal(&cond2);//发送拍照完成信号
            cout<<"pThread_TAKE_Photo::cond2 sent!"<<endl;
        }

        tickCNT++;
        Total_Runtime = (double)cv::getTickCount()/cv::getTickFrequency() - Start_Runtime;        
        if( tickCNT%25 == 0 )
        {
            log.fs(INFO) << "Front Camera statistic information: "
                         << "\n\t Total Frame Count : " << cnt_TotalFrames
                         << "\n\t Take Frequency(Hz): " << cnt_TotalFrames/Total_Runtime
                         << "\n\t Average take time(s): " << Taking_time/cnt_TotalFrames
                         << "\n\t "
                         << endl << endl;
        }
        usleep(50000);
    }
}
// This is the end of front camera pre-handle function
// --*END*--
/*****************************************************************************/

/**********************************************************************************/
/**************************************************************/
 // @Module Name       : Global Planning
 // @Module Author     : LiMin
 // @Module History    : 
 //     1. Created By LiMin @ 2017-04-15
 // 
 // @Module Description: 
 //     This module is used to calculate the global path for Robot
 // 
 //     
 //
/**************************************************************/
void *pThread_GP(void* param)
{
    log_t log( "./logs/GlobalPlanning"+time_filename_str(), "Global Planning Module By LiMin" );

    log.fs(INFO) << "Global Planning Start to Work..." << endl;

    vector<Point> Res; // the result of the aim position search and path planning
    vector<pose_t> Res_divided; // divided global path
    pose_t currPose;   // start point of search the aim position and path planning
    float direction = 90.0;

    Grid_Map_t dilateMap;
    Grid_Map_t mapSnap;
    Map_Attr_t mapAttr;

    while(true)
    {
        log.fs(INFO) << "Waiting for active signal from Local Planning Module..." << endl;
        pthread_mutex_lock(&mutex_GPLP);
        pthread_cond_wait(&cond_GPLP, &mutex_GPLP);

        log.fs(INFO) << "Active signal captured! Global Planning is executing..." << endl;

        currPose = GetPose();
        log.fs(INFO) << "Getting the map snap shoot..." << endl;
        pthread_mutex_lock( &mutex_mapData );
        //mapSnap = mapData.clone();
        mapData.copyto( mapSnap );
        pthread_mutex_unlock( &mutex_mapData );
        mapAttr = mapSnap.GetAttr();
        log.fs(INFO) << "Saving Map Snap shoot..." << endl;
        mapSnap.Save(".", "GP_MapSnap");

        log.fs(INFO) << "Dilating the map snap shoot..." << endl;
        mapSnap.copyto( dilateMap );
        mapSnap.dilate( &dilateMap );
        dilateMap.Save(".", "GP_DilateMap");

        log.fs(INFO) << "Global Path planning..." << endl;
        Res = PathPlanning_CRT( toGrid(currPose, mapAttr.map_grid_size), &dilateMap );
        
        if( !Res.empty() )
        {
            Res_divided = PathSegmentePoseV2(Res, mapAttr.map_grid_size);

            log.fs(INFO) << "Global Path: ";
            for( vector<pose_t>::iterator iter = Res_divided.begin(); iter != Res_divided.end(); iter++ )
            {
                log.fs(ORI) << *iter << "->";
            }
            log.fs(ORI) << endl;

            SetGlobalPath( Res_divided );
            SetCleanDirection( direction );
            log.fs(INFO) << "Global Planning has Done! " << endl;
        }
        else
        {
            log.fs(INFO) << "Global Planning failed to find a path!" << endl;
        }
        pthread_mutex_unlock(&mutex_GPLP);
        //printf_globalPath( Res_divided );
        usleep(20000);
    }
}
// This is the end of Global Path planning 
// --*END*--
/*****************************************************************************/