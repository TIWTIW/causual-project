#ifndef _SERVER_H
#define _SERVER_H

#include "common_include.h"
#include "../source/proto/build/request.pb.h"

#define LISTEN_BACKLOG 10
#define BUFSIZE 8192

namespace myHttp
{

enum serverMode{
    SINGLE,
    MULTI_PROCESS,
    MULTI_THREAD,
    IO_MULTIPLEX
};

class httpServer
{
//constructor & deconstructor
public:
    httpServer();
    httpServer(const int port, const std::string &ip, serverMode mode = SINGLE);
    ~httpServer();
    httpServer( const httpServer& ) = delete;
    httpServer &operator=( const httpServer& ) = delete;

//get & set
public:
    int getPort();
    int setPort( const int port );
    std::string getIp();
    int setIp( const std::string &ip );
    int setMode( serverMode mode );
    serverMode getMode();

//function
public:
    int start();

//private function
private:
    int checkValidIpAndPort();
    int processSingle( int fd);
    int processMultiProcess( int fd);
    int processMultiThread( int fd);
    int processMultiplex( int fd);

    int parseAndResponse( networkLearn::Request &request );
    int charToInt( char buf[], int size );

//private debug
private:
    void showInfo( networkLearn::Request &request );


//wrap function
private:
    int Socket( int domain, int type, int protocol );
    int Bind( int sockfd, const struct sockaddr *addr, socklen_t addrlen );
    int Listen( int sockfd, int backlog );
    int Accept( int sockfd, struct sockaddr *addr, socklen_t *addrlen );
    int Inet_pton( int af, const char *src, void *dst );
    int Readn( int fd, char buf[], size_t num );

//private
private:
    int _port;
    std::string _ip;
    serverMode _mode;
};
}

#endif
