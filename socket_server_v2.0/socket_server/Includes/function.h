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

#define MAXLINE 4096
#define MAX_EVENTS 20

int readMsg( int );
void intToChar( long, char * );
int writeMsg( int );
static void* manageThread( void* );
int createManageThread();
int initialListen( int &, int port = 8010 );

