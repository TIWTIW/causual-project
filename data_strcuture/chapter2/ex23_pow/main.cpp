#include <iostream>

using namespace std;

int pow( int x, int n )
{
    int res = 1;
    int now = x;
    while( n != 0 )
    {
        if( n & 1 == 1 )
            res *= now;
        now *= now;
        n = n >> 1;
    }

    return res;
}

int main()
{
    cout << pow( 2, 10 ) << endl;
}
