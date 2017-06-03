
#include "test_unit.h"

#include "COMUART.h"

using namespace std;


void CMD_Test( void )
{
    
}



void COM_UART_test( void )
{
    cout << " Robot Test Unit -- COM UART "
         << " LogFile: "
         << endl;

    // Construct the Default UART ttySAC1
    //COM_UART ttySAC1("/dev/ttyS1");
    COM_UART ttySAC1;
    // Initialize the ttySAC1
    if ( ttySAC1.COM_UART_Init() != 0 )
    {
        // Failed to initialize the UART
        cout << "Error: Failed to initialize the serial port ttySAC1! " << endl;
        cout << "Program terminated!" << endl;
        exit(-1);
    }
    // Succeed to Initialize UART
    cout << "Serial port ttySAC1 Initialized!" << endl;

    // Start to Communicate with the STM32 serial port

    // Serial Port ttySAC1 Test
    // Step 1: Prepare Motion Command Data
    MCB_t MoveStop;
    MoveStop.serialnum = 1;
    MoveStop.priority  = 0;
    MoveStop.cmd_move  = CMD_MOVE_Stop;

    MCB_t MoveF;
    MoveF.serialnum = 2;
    MoveF.priority  = 0;
    MoveF.cmd_move  = CMD_MOVE_Forward;
    MoveF.SetSpeed  = 200; // 200 mm/s
    MoveF.SetDis    = 911; // 911 mm
    MoveF.SetAngSpeed = 15; // 15 degree/s
    MoveF.SetAngle  = 180;  // 180 degree

    MCB_t MoveB;
    MoveB.serialnum = 3;
    MoveB.priority  = 0;
    MoveB.cmd_move  = CMD_MOVE_Backward;
    MoveB.SetSpeed  = 200; // 200 mm/s
    MoveB.SetDis    = 911; // 911 mm
    MoveB.SetAngSpeed = 15; // 15 degree/s
    MoveB.SetAngle  = 180;  // 180 degree

    MCB_t MoveTL;
    MoveTL.serialnum = 4;
    MoveTL.priority  = 0;
    MoveTL.cmd_move  = CMD_MOVE_TurnLeft;
    MoveTL.SetSpeed  = 200; // 200 mm/s
    MoveTL.SetDis    = 911; // 911 mm
    MoveTL.SetAngSpeed = 15; // 15 degree/s
    MoveTL.SetAngle  = 180;  // 180 degree

    MCB_t MoveTR;
    MoveTR.serialnum = 5;
    MoveTR.priority  = 0;
    MoveTR.cmd_move  = CMD_MOVE_TurnRight;
    MoveTR.SetSpeed  = 200; // 200 mm/s
    MoveTR.SetDis    = 911; // 911 mm
    MoveTR.SetAngSpeed = 15; // 15 degree/s
    MoveTR.SetAngle  = 180;  // 180 degree

    MCB_t MoveFF;
    MoveFF.serialnum = 6;
    MoveFF.priority  = 0;
    MoveFF.cmd_move  = CMD_MOVE_Forward_Free;

    MCB_t MoveBF;
    MoveBF.serialnum = 7;
    MoveBF.priority  = 0;
    MoveBF.cmd_move  = CMD_MOVE_Backward_Free;

    MCB_t MoveTLF;
    MoveTLF.serialnum = 8;
    MoveTLF.priority  = 0;
    MoveTLF.cmd_move  = CMD_MOVE_TurnLeft_Free;

    MCB_t MoveTRF;
    MoveTRF.serialnum = 9;
    MoveTRF.priority  = 0;
    MoveTRF.cmd_move  = CMD_MOVE_TurnRight_Free;

    int SleepTimer = 10000;

    // Step 2 Send the command
    int cnt_sys_init_err = 0;
    int cnt_sys_sleep_err = 0;
    int cnt_sys_shut_err = 0;
    int cnt_motion_err = 0;

/*
    for (int i = 0; i < 200; ++i)
    {
        // Send Test count: 100
        // Step 1: Send System Command Test
        // Total Commands: 3 System Command +
        // CMD_SYS_Init

        if( ttySAC1.COM_System( CMD_SYS_Init ) != 0 )
        {
            cout << "Send System Initialize command error!" << endl;
            cnt_sys_init_err++;
        }
        cout << i << endl;
        usleep(SleepTimer);
        // CMD_SYS_Sleep
        if( ttySAC1.COM_System( CMD_SYS_Sleep ) != 0 )
        {
            cout << "Send System Sleep Command error!" << endl;
            cnt_sys_sleep_err++;
        }
        usleep(SleepTimer);
        // CMD_SYS_Shut
        if( ttySAC1.COM_System( CMD_SYS_Shut ) != 0 )
        {
            cout << "Send System Shut Command error!" << endl;
            cnt_sys_shut_err++;
        }
        usleep(SleepTimer);
        // Step 2: Send Motion Control Command
        if ( ttySAC1.COM_Motion( MoveStop ) != 0 )
        {
            cout << "Send Motion Stop Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveF ) != 0 )
        {
            cout << "Send Motion Forward Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveB ) != 0 )
        {
            cout << "Send Motion Backward Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveTL ) != 0 )
        {
            cout << "Send Motion TurnLeft Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveTR ) != 0 )
        {
            cout << "Send Motion TurnRight Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveFF ) != 0 )
        {
            cout << "Send Motion Forward Free Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveBF ) != 0 )
        {
            cout << "Send Motion Backward Free Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveTLF ) != 0 )
        {
            cout << "Send Motion TurnLeft Free Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);
        if ( ttySAC1.COM_Motion( MoveTRF ) != 0 )
        {
            cout << "Send Motion TurnRight Free Command error!" << endl;
            cnt_motion_err ++;
        }
        usleep(SleepTimer);


    }
*/
    cout << "Command Send Information: "
         << "\n\t sys_init_err cnt: " << cnt_sys_init_err
         << "\n\t sys_sleep_err cnt: " << cnt_sys_sleep_err
         << "\n\t sys_shut_err cnt: " << cnt_sys_shut_err
         << "\n\t motion_cmd_err cnt: " << cnt_motion_err
         << endl;
    // Send Test End!

    // Step 3: Receive STM Data Frame
    // Prepare data type to buffer the receive the frame from STM
    Hall_t data_hall;
    data_hall.cntL = 0;
    data_hall.cntR = 0;
    MPU_t data_mpu;
    unsigned char data_sen1;
    unsigned char data_sen2;
    Dis_t data_dis;
    MotionStat_t data_motionstat;
    MotionRes_t data_motionres;
    int i = 0;
    int cnt_recv_err = 0;
    while(i<5000)
    {
        if ( ttySAC1.Recv(data_hall, data_mpu, data_sen1, data_sen2, data_dis, data_motionstat, data_motionres) == -1 )
        {
            cnt_recv_err++;
            cout << "Failed to Receive!" << endl;
        }
        usleep(8000);
        i++;
        cout << data_hall << endl;
    }

    cout << "Receive Error Count: " << cnt_recv_err << endl;


}