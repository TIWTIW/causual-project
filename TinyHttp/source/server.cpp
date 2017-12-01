#include "server.h"

using namespace std;

namespace myHttp
{

/*****constructor & desconstructor******/
httpServer::httpServer() : _port( 0 ), _ip( "0" ), _mode( SINGLE )
{

}

httpServer::httpServer(int port, string &ip, serverMode mode) : _port( port ), _ip( ip ), _mode( mode )
{

}

httpServer::~httpServer()
{

}

/*******get & set*****************/
int httpServer::getPort()
{
    return _port;
}

int httpServer::setPort( int port )
{
    _port = port;
    return 0;
}

string httpServer::getIp()
{
    return _ip;
}

int httpServer::setIp( string &ip )
{
    _ip = ip;
    return 0;
}

int httpServer::setMode( serverMode mode )
{
    _mode = mode;
    return 0;
}

serverMode httpServer::getMode()
{
    return _mode;
}

/*********wrap function*****/
int httpServer::Socket( int domain, int type, int protocol )
{
    int sock_fd = socket(domain, type, protocol);
    if( sock_fd < 0 )
        perror( "Server: socket failed!" );

    return sock_fd;
}

int httpServer::Bind( int sockfd, const struct sockaddr *addr, socklen_t addrlen )
{
    int res = bind( sockfd, addr, addrlen );
    if( res == 0 )
    {
        return 0;
    }
    else
    {
        perror( "Server: Bind error " );
        return -1;
    }
}

int httpServer::Inet_pton( int af, const char *src, void *dst )
{
    int res = inet_pton( af, src, dst );

    if( res == 1 )
        return 0;

    if( res == 0 )
    {
        cout << "Server: Invalid ip " << src << endl;
        return -1;
    }

    if( res == -1 )
    {
        perror( "Server: Transfer ip failed" );
        return -1;
    }

    return 0;
}

int httpServer::Listen( int sockfd, int backlog )
{
    int res = listen( sockfd, backlog );
    if( res == 0 )
    {
        return 0;
    }
    else
    {
        perror( "Server: Listen failed " );
        return -1;
    }
}

int httpServer::Accept( int sockfd, struct sockaddr *addr, socklen_t *addrlen )
{
    int connfd = accept( sockfd, addr, addrlen );
    if( connfd < 0 )
    {
        perror( "Server: accept faild " );
        return -1;
    }
    else
    {
        return connfd;
    }
}

int httpServer::Readn( int fd, char buf[], size_t num )
{
    size_t numRead = 0, currRead = 0;
    while( numRead < num )
    {
        currRead = read( fd, buf + numRead, num - numRead );
        if( currRead < 0  )
        {
            perror( "Server: read error!" );
            return -1;
        }
        numRead += currRead;
    }

    return num;
}

/*********private function****/
int httpServer::checkValidIpAndPort()
{
    if( _port == 0 )
    {
        cout << "Server: Invalid port " << _port << endl;
        return -1;
    }

    if( _ip == "0" )
    {
        cout << "Server: Invalid ip " << _ip << endl;
        return -1;
    }

    return 0;
}

//Didn't consider overflow & other corner cases
int httpServer::charToInt( char buf[], int size )
{
    int res = 0;
    for( int i = 0; i < size; ++i )
        res = res * 10 + buf[i] - '0';

    return res;
}

int httpServer::processMultiProcess( int fd )
{

}

int httpServer::processMultiThread( int fd )
{

}

int httpServer::processMultiplex( int fd )
{

}

int httpServer::processSingle( int fd )
{
    int connfd = Accept( fd, NULL, NULL );

    if( connfd < 0 )
        return -1;

    //read how many?
    char lengthBuf[4];
    Readn( connfd, lengthBuf, sizeof( lengthBuf ) );

    int length = charToInt( lengthBuf, sizeof( lengthBuf ) );

    char *contentBuf = new char[length];

    Readn( connfd, contentBuf, sizeof( contentBuf ) );

    networkLearn::Request request;
    request.ParseFromArray( contentBuf, length );

    parseAndResponse( request );

    close( connfd );

    delete [] contentBuf;

    return 0;

}


int httpServer::parseAndResponse( networkLearn::Request &request )
{
    //debug
    showInfo( request );

    return 0;

}

/*********private debug*****/
void httpServer::showInfo( networkLearn::Request &request )
{
    cout << "version number: " << request.version() << endl;
    cout << "http method: " << request.content().resline().method() << endl;
}

/*********function**********/
int httpServer::start()
{
    if( checkValidIpAndPort() == -1 )
        return -1;

    int sock_fd = Socket(AF_INET, SOCK_STREAM, 0);

    //Initial sockaddr
    struct sockaddr_in serverAddr;
    bzero( &serverAddr, sizeof( serverAddr ) );
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons( _port );
    Inet_pton( AF_INET, _ip.c_str(), &serverAddr.sin_addr );

    //bind socket
    Bind( sock_fd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in) );
    Listen( sock_fd, LISTEN_BACKLOG );

    while( true )
    {
        switch (_mode){
            case SINGLE:
                processSingle( sock_fd );
                break;
            case MULTI_PROCESS:
                processMultiProcess( sock_fd );
                break;
            case MULTI_THREAD:
                processMultiThread( sock_fd );
                break;
            case IO_MULTIPLEX:
                processMultiplex( sock_fd );
                break;
            default:
                cout << "Server error: no mode!" << endl;
                exit( -1 );
        }
    }
}

}
