#include <iostream>

using namespace std;

int main()
{
    int x = 1, y = 2;

    auto f = []( int a, int b ) -> int { return a + b; };
    cout << f( x, y ) << endl;
}
