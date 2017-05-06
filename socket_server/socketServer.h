#ifndef _SOCKET_SEVER_H
#define _SOCKET_SEVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cerrno>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define MAXLINE 4096

class socketServer
{
public:
    socketServer( int port = 8010 );
    void waiting();

private:
    int listenfd;
    int connfd;
    char recBuf[MAXLINE];
    char sendBuf[MAXLINE];
    struct sockaddr_in servaddr;
    int exit_con_flag;
    
private:
    void writeMsg();
    static void* readMsg( void * );        
    void readThread();
    void intToChar( int, char * );
    static void* keyExit( void * );
    void keyThread();
};
#endif