#include "WrapFunction.h"
#include <unistd.h>

int Readn( int &fd, char *buf, int size )
{
    int nleft = size;
    int nread = 0;
    int nReadTemp = 0;

    while( nleft > 0 )
    {
        if( ( nReadTemp = read( fd, buf + nread, nleft ) ) < 0 )
        {
            return -1;
        }
        else if( nReadTemp == 0 )
        {
            return 0;
        }

        nleft -= nReadTemp;
        nread += nReadTemp;
    }

    return size;
}

int Writen( int &fd, char *buf, int size )
{
    int nleft = size;
    int nwrite = 0;
    int nWriteTemp = 0;

    while( nleft > 0 )
    {
        if( ( nWriteTemp = write( fd, buf + nwrite, nleft ) ) < 0 )
        {
            return -1;
        }

        nleft -= nWriteTemp;
        nwrite += nWriteTemp;
    }

    return size;
}
