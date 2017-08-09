#include "show_bytes.h"

int main()
{
    int x = 0x123456;
    long l = 0x1234567890;
    double d = 1.123456789;


    show_int( x );
    show_long( l );
    show_double( d );
}
