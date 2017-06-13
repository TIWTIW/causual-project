#include <iostream>

using namespace std;

int main()
{
    int x = 4;

    auto f = [&x]() -> bool { if( x == 0 ) return true; --x; return false; };

    while( !f() )
        cout << x << endl;
}
