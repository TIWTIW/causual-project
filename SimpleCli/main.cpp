#include <sys/socket.h>
#include <iostream>
#include <sys/syscall.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include "test_ToClient.pb.h"

using namespace std;

int main( int argc, char **argv )
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket( AF_INET, SOCK_STREAM, 0 );

    char ip[] = "127.0.0.1";

    bzero( &servaddr, sizeof( servaddr ) );
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons( 8080 );
    inet_pton( AF_INET, ip, &servaddr.sin_addr );

    if( connect( sockfd, (struct sockaddr *)&servaddr, sizeof( servaddr ) ) < 0 )
    {
        perror( "connect failed: " );
        return -1;
    }

    char buf[4096];

    while( true )
    {
        if( read( sockfd, buf, sizeof( buf ) ) < 0 )
        {
            perror( "read failed: " );
            return -1;
        }

        test::ToClient message;
        message.ParseFromArray( buf, sizeof( buf ) );

        cout << message.head() << endl;
        cout << message.tail() << endl;
    }

    return 0;

    
}
