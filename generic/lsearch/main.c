#include <stdio.h>
#include <memory.h>

int lsearch( void *base, void *target, int elemSize, int n )
{
    for( int i = 0; i < n; ++i )
    {
        void *addr = (char *)base + elemSize * i;
        if( ( memcmp( target, addr, elemSize ) == 0 ) ) 
            return 0;
    }

    return 1;
}

int main( int argc, char **argv )
{
    int a[10] = {1};
    int b = 2;

    if( lsearch( &a[0], &b, sizeof( int ), 10 ) )
    {
        printf( "unfind\n" );
    }
    else
    {
        printf( "find\n" );
    }

    return 0;
}
