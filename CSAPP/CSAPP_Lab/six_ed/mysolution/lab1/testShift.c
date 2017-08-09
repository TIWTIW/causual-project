#include <stdio.h>

int main()
{
    int x = 0x80000000;
    printf( "%x\n", x >> 1 );
    printf( "%x\n", 0x80000000 >> 2 );
}
