#include <iostream>

using namespace std;

class Random
{
public:
    int operator()( int i1, int i2, int i3 ){ return i1 ? i2 : i3; }
};

int main()
{
    Random r;
    cout << r( 1, 2, 3 ) << endl;
    cout << r( 0, 1, 2 ) << endl;

    return 0;
}
