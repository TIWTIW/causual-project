#include "client.h"

using namespace std;

namespace myHttp
{
/*******construct & deconstruct*******/
httpClient::httpClient() : _port( 0 ), _ip( "0" )
{

}

httpClient::httpClient( const int port, const std::string ip ) : _port( port ), _ip( ip )
{

}

httpClient::~httpClient()
{

}

/*********get & set***************/
int httpClient::getPort()
{
    return _port;
}

int httpClient::setPort( const int port )
{
    _port = port;
    return 0;
}

string httpClient::getIp()
{
    return _ip;
}

int httpClient::setIp( const string &ip )
{
    _ip = ip;
    return 0;
}

/*******wrap function*********/
int httpClient::Socket( int domain, int type, int protocol )
{
    int sock_fd = socket(domain, type, protocol);
    if( sock_fd < 0 )
        perror( "Server: socket failed!" );

    return sock_fd;
}

int httpClient::Inet_pton( int af, const char *src, void *dst )
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

int httpClient::Readn( int fd, char buf[], size_t num )
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

int httpClient::Connect( int sockfd, const struct sockaddr *addr, socklen_t addrlen )
{
    int res = connect( sockfd, addr, addrlen );

    if( res < 0 )
    {
        perror( "Client: connect failed: " );
        return -1;
    }

    return 0;
}

/**********private function******/
int httpClient::intToChar( int num, char *buf, int size )
{
    for( int i = size - 1; i >= 0; --i)
    {
        buf[i] = num - num / 10 * 10 + '0';
        num = num / 10;
    }

    return 0;
}

/***********public function********/
int httpClient::connectToHost( string &ip, int port )
{
    int sockfd = Socket( AF_INET, SOCK_STREAM, 0 );

    struct sockaddr_in serverAddr;
    bzero( &serverAddr, sizeof( serverAddr ) );
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons( port );
    Inet_pton( AF_INET, ip.c_str(), &serverAddr.sin_addr );

    int res = 0;
    res = Connect( sockfd, (struct sockaddr*)&serverAddr, sizeof( struct sockaddr_in ) );

    if( res == 0 )
    {
        cout << "Client: connect to host success" << endl;
        return 0;
    }
    return -1;
}
}
