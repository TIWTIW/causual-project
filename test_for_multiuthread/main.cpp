#include <iostream>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include "function.h"

using namespace std;

static void *Thread( void *arg )
{
    while( true )
    {
        hello();
        sleep( 1 );
    }
}

int main( int argc, char *argv[] )
{
    pthread_t thread;
    if( pthread_create( &thread, NULL, Thread, NULL ) == -1 )
    {
        cout << "create failed!" << endl;
        return 1;
    }
    while( true )
    {
        //
    }
}
