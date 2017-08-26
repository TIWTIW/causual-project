#ifndef _THREAD_H
#define _THEAD_h

#include <pthread.h>

class Thread
{
public:
    Thread();
    ~Thread();


private:
    //tid of send thread and receive thread
    pthread_t send_thread_tid;
    pthread_t receive_thread_tid;

    //Need Image or not
    bool Need_Image;

    //Mode transfer
    bool ControlMode;

    //The connected fd
    int connfd;

//functions
private:
    static void *sendThread( void *arg );
    static void *receiveThread( void *arg );
};

#endif
