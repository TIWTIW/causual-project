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
    servaddr.sin_port = htons( 15000 );
    inet_pton( AF_INET, ip, &servaddr.sin_addr );

    if( connect( sockfd, (struct sockaddr *)&servaddr, sizeof( servaddr ) ) < 0 )
    {
        perror( "connect failed: " );
        return -1;
    }

    char buf[4096];

    int nread;

    while( true )
    {
        if( ( nread = read( sockfd, buf, sizeof( buf ) ) ) < 0 )
        {
            perror( "read failed: " );
            return -1;
        }

        /*while( true )
        {
            cout << nread << endl;
        }*/

        int i = 0;
        for( ; i < 4094; ++i )
        {
//            cout << buf[i] << endl;
            if( buf[i] == 'c' && buf[i + 1] == 'c' )
            {
//                cout << "found!" << endl;
                break;
            }
            
        }

        test::ToClient message;
        message.ParseFromArray( buf + i + 2, sizeof( buf ) );

        cout << message.sen_data() << endl;
        cout << message.pose_x() << endl;
        cout << message.image_length() << endl;

        if( message.HasImage )
        {
            char buf[message.image_length()];
            read( sockfd, buf, sizeof( buf ) );
        }
        
        //cout << buf[]
    }

    return 0;

    
}
