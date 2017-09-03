#include "OtherPro.h"
#include "function.h"
#include <iostream>
#include <unistd.h>
#include "Robot_Data.h"
#include <sys/mman.h>

using namespace std;

p_IPC *p_addr;

void createShm()
{
    p_addr = (p_IPC *)mmap( NULL, sizeof( p_IPC ), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0 );
    if( p_addr == MAP_FAILED )
    {
        perror( "mmap" );
        exit( 1 );
    }
}

void ChangeVariable()
{
    //++p_addr->Sen_data;
    ++((p_addr->p_RobotPose).x);
}

int main()
{

    createShm();

    if(fork() == 0)
    {
        createManageThread();
        printf( "child:%x\n", p_addr );

        while( true )
        {
            cout << "Child in main thread..." << endl;
            sleep( 500 );
        }

        cout << "Unexpectedly exit child process!" << endl;
        exit( 1 );
    }

    printf( "parent:%x\n", p_addr );
    while( true )
    {
        ChangeVariable();
        
        printf( "current sen data:%d\n", p_addr->Sen_data );
        usleep( 5000 );
    }
}
