#include <iostream>

using namespace std;

template<typename T, unsigned N> constexpr 
size_t SizeOfArray( const T (&a)[N] )
{
    return N;
}

int main()
{
    char a[20];
    int v[30];

    cout << SizeOfArray( a ) << endl;
    cout << SizeOfArray( v ) << endl;
}
