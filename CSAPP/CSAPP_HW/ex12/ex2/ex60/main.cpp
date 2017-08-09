#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

unsigned replace_byte( unsigned x, unsigned char b, int i )
{
    unsigned mask = 0xff;

    if( i > 4 )
    {
        cout << "out of range!" << endl;
        return 0;
    }

    mask = mask << ( i * 8 );
    mask = ~mask;

    x = x & mask;
    x = x | ( b << (i * 8) );

    return x;
}

int main()
{
    unsigned x = 0x12345678;
    unsigned char c = 0xAB;
    
    printf( "%x\n", replace_byte( x, c, 0 ) );
    printf( "%x\n", replace_byte( x, c, 2 ) );

}
