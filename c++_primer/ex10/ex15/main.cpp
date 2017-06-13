#include <iostream>

using namespace std;

int main()
{
    int a = 2, b = 3;
    auto f = [a]( int x ) -> int { return x + a; };

    cout << f( b ) << endl;
}
