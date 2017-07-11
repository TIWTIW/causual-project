#include <iostream>
#include <utility>

using namespace std;

template <typename F, typename T1, typename T2>
void func( F f, T1 &&t1, T2 &&t2 )
{
    f( std::forward<T2>(t2), std::forward<T1>(t1) );
}

void sum( int &a, int &&b )
{
    a += b;
}

int main()
{
    int i = 1, j = 2;
    func( sum, 2, j );

    cout << j << " " << i << endl;
}
