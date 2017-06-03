
#include "MyHeader.h"


#include "Robot_VisionNavV2.h"
#include "Robot_COM_NodeX.h"

int main(int argc, char const *argv[])
{
    pid_t L1_pid = fork();
    if ( L1_pid<0 )
    {
        perror("Error: Failed to Create Process L1");
        printf("Program Will exit with code -1\n");
        return -1;
    }
    else if( L1_pid == 0 )
    {
        // Level 1 Process
        sleep(1);
        Level1_Lacation_Trajectory();
    }
    // printf("Process Level 1 %d Created!\n", L1_pid );

    /*
    pthread_t pthread_pid_COM_Node0;
    if( pthread_create( &pthread_pid_COM_Node0, NULL, pThread_COM_Node0, &L1_pid ) != 0)
    {
        perror("Error: Failed to Create pThread COM_Node0!");
        printf("Killing Process %d for COM_Node0 failed!\n", L1_pid );
        kill(  L1_pid, SIGKILL );
        printf("Process Will exit with code -1\n");
        return(-1);
    }
    */

    int exitcode = P_COM_Node0( L1_pid );
    /*
    if ( exitcode == -1 )
    {
        printf("Main Program work Error, Killing all the Child Processes...\n");
        //kill( -L1_pid, SIGTERM ); // kill all the child processed
    }
    */

    printf("Program Exit Abnormally!\n");
    return -1;
}



