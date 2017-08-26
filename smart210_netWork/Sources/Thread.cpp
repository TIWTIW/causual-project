#include "Thread.h"

using namespace std;

Thread::Thread( int newfd ) : connfd( newfd )
{
    
    if( pthread_create( &receive_thread_tid, NULL, receiveThread, (void *)connfd ) )
    {
        cout << "Create reveive thread failed! connfd:" << connfd << endl;
        pthread_exit( NULL );
    }

    if( pthread_create( &send_thread_tid, NULL, sendThread, (void *)connfd ) )
    {
        cout << "Create send thread failed! connfd:" << connfd << endl;
        pthread_exit( NULL );
    }
}

static void *Thread::sendThread( void *arg )
{
}

static void *Thread::receiveThread( void *arg )
{
    pthread_detach( pthread_self() );

    int *connfd = (int *)arg;

    while( true )
    {
        if( readMsg( *connfd ) )
        {
            //if read failed or, mostly, the client cut the connection
            cout << "Exit receive thread! connfd is:" << *connfd << endl;

            //close the connection
            close( *connfd );

            //reset status
            Need_Image = false;
            ControlMode = false;

            pthread_exit( NULL );
        }
    }
}
