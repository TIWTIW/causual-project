#include <iostream>

using namespace std;

int numberOfOne( int N )
{
    if( N == 0 )
        return 0;

    if( N % 2 )
        return numberOfOne( N >> 1  ) + 1;

    return numberOfOne( N >> 1 );
}

int main()
{
    cout << numberOfOne( 65530 ) << endl;
}
