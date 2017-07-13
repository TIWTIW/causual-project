#include <iostream>
#include <bitset>

using namespace std;

int main()
{
    unsigned x = 2 | (1 << 2) | (1 << 3) | (1 << 5) | (1 << 8) | (1 << 13) | ( 1 << 21 );

    bitset<24> bc( x );

    bitset<24> bc2;
    bc2.flip( 1 );
    bc2.flip( 2 );
    bc2.flip( 3 );
    bc2.flip( 5 );
    bc2.flip( 8 );
    bc2.flip( 13 );
    bc2.flip( 21 );

    cout << bc << endl;
    cout << bc2 << endl;
}
