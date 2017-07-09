#include <iostream>

using namespace std;

template<typename T, unsigned N>
const T my_begin( const T (&a)[N] )
{
    return a[0];
}

template<typename T, unsigned N>
const T my_end( const T (&a)[N] )
{
    return a[N-1];
}

int main()
{
    int a[] = {1, 2, 4 ,5 ,6};
    char v[2] = {'c', 'a'};

    cout << my_begin( a ) << endl;
    cout << my_end( a ) << endl;
    cout << my_begin( v ) << endl;
    cout << my_end( v ) << endl;
}


