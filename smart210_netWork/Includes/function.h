#ifndef _FUNCTION_H
#define _FUNCTION_H

#include <sys/socket.h>
#include <cerrno>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "Robot_Data.h"
#include "test_ToClient.pb.h"

/***************Macro******************************/
#define MAXLINE 4096    //send size

//default port
#define DEFAULT_PORT 15000

//max listen queue number
#define LISTENQ 10

//one frame's head and tail
#define FRAME_HEAD 0xa5a5
#define FRAME_TAIL 0xbeef

#define FRAME_LENGTH 25

//Frame's type
#define DATA_TYPE 0xda
#define CONTROL_TYPE 0Xca

//MAX CLI
#define MAXCLI 10

/**************Variable****************************/
//int Sen_data;
//int Image_data = 0;
//Pose Robot_Pose;

//serv->cilent message without Image data
//char SerToCilent[FRAME_LENGTH];
//pthread_mutex_t ToCilent_buffer_lock;

//communction frame type
/*typedef enum
{
    Data,
    Control
} TYPE;*/

//Thread Parameters
struct Thread_p
{
    //Need Image or not
    bool Need_Image;

    //Mode transfer
    bool ControlMode;

    //connection fd
    int connfd;

    //tid of receive thread and send thread
    pthread_t receive_thread_tid;
    pthread_t send_thread_tid;
};

/***************Function**************************/
//about read
int readMsg( int &fd, Thread_p * );

//about write
int writeMatMsg( int & );
int writeMsg_Mat( cv::Mat, int );
int WriteSimpleMessage( int &, char * );

//about thread
void* manageThread( void * );
int createManageThread();
void *sendThread( void * );
void *receiveThread( void * );

// Encode
int Encode( char *, int, Thread_p * );
int getFileSize();

//about initial
int initialListen( int &, int port = DEFAULT_PORT );

#endif
