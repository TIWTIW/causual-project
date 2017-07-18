#include <iostream>
#include <algorithm>

using namespace std;

int gcd( int a, int b )
{
    if( a < b )
        swap( a, b );

    if( (a == 0 && b == 0) || ((a % 2) && (b == 0)))
        return a;

    if( !(a % 2) && !(b % 2) )
        return 2 * gcd( a >> 1, b >> 1 );
    else if( !(a % 2) && (b % 2) )
        return gcd( a >> 1, b );
    else if( (a % 2) && !(b % 2))
        return gcd( a, b >> 1 );
    else
        return gcd( (a + b) >> 1, (a - b) >> 1 );
}

int main()
{
    cout << "input two numbers: ";
    int a, b;
    cin >> a >> b;

    cout << endl;
    cout << "Their gcd is:" << gcd( a, b ) << endl;

    return 0;
}
