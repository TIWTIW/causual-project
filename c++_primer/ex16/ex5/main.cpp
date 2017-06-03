#include <iostream>

using namespace std;

template<typename T, const int N>
void print( const T (&arr)[N] )
{
    for( int i = 0; i < N; ++i )
        cout << arr[i] << endl;
}

int main( int argc, char *argv[] )
{
    int abc[5] = {1, 2, 3, 4, 5};
    char as[3] = {'a', 'b', 'c'};

    print( abc );
    print( as );
}
