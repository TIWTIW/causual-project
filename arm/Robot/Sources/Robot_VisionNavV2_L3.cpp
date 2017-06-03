#include "Robot_VisionNavV2.h"

static pid_t L0_pid;
static pid_t L1_pid;
static pid_t L2_pid;

int Level3_GlobalPlanning( pid_t pidnum0, pid_t pidnum1 )
{
    sleep(3);
    while( true )
    {
        //cout << "Level3 is Working..." << endl;
        sleep(10);
    }
}