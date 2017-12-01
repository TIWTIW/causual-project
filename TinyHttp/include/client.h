#ifndef _CLIENT_H
#define _CLIENT_H

#include "common_include.h"

namespace myHttp
{
class httpClient
{
//constructor & de
public:
    httpClient();
    httpClient( const int port, const std::string ip );
    ~httpClient();
    httpClient( const httpClient& ) = delete;
    httpClient &operator=( const httpClient& ) = delete;

//get & set
public:
    int getPort();
    int setPort( const int port );
    std::string getIp();
    int setIp( const std::string &ip );
//function
public:
    int connectToHost( std::string &ip, int port );
    int sendMsg( networkLearn::Request &request );

//wrap function
private:
    int Socket( int domain, int type, int protocol );
    int Inet_pton( int af, const char *src, void *dst );
    int Readn( int fd, char buf[], size_t num );
    int Connect( int sockfd, const struct sockaddr *addr, socklen_t addrlen );

//private function
private:
    int intToChar( int num, char *buf, int size );

//private thing
private:
    int _port;
    std::string _ip;
};
}

#endif
