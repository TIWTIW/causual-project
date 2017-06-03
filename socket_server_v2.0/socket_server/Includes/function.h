#include <sys/socket.h>
#include <cerrno>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

#define MAXLINE 4096    //send size

#define MAX_EVENTS 20   //max number of events

//about read
int readMsg( int );

//about write
void intToChar( long, char * );
int writeMsg( int );
int writeMsg_Mat( cv::Mat, int );

//about thread
static void* manageThread( void* );
int createManageThread();

//about initial
int initialListen( int &, int port = 8010 );

