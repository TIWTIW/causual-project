#include <iostream>

using std::cout;
using std::endl;

int is_little_endian()
{
    int x = 0x1234;

    if( *(char *)(&x) == 0x12 )
        return 0;

    return 1;
}

int main()
{
    cout << is_little_endian() << endl;
}
