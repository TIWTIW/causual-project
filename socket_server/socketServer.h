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

#define MAXLINE 4096

class socketServer
{
public:
    socketServer( int port = 8010 );
    void waiting();
    void show();

private:
    int listenfd;
    int connfd;
    char recBuf[4096];
    char sendBuf[4096];
    struct sockaddr_in servaddr;

private:
    void writeMsg();
    void readMsg(void *);        
    void readThread();
};
#endif
