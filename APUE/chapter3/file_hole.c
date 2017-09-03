#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main( void )
{
    int fd;

    if( (fd = creat( "file.hole", 766 )) < 0 )
    {
        perror( "creat error" );
    }

    if( write( fd, buf1, 10 ) != 10 )
    {
        perror( "buf1 write error" );
    }

    if( lseek( fd, 16384, SEEK_SET ) == -1 )
    {
        perror( "lseek error" );
    }

    if( write( fd, buf2, 10 ) < 0 )
        perror( "buf2 write error" );

    exit( 0 );
}
