#include <stdio.h>
#include <memory.h>

void swap( void *vp1, void *vp2, int size )
{

    char temp[size];

    memcpy( temp, vp1, size );
    memcpy( vp1, vp2, size );
    memcpy( vp2, temp, size );
}

int main( int argc, char *argv[] )
{
    int a = 0, b = 1;

    swap( &a, &b, sizeof( int ) );

    printf( "%d, %d\n", a, b );

    return 0;
}
