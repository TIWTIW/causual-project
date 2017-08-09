#include <iostream>

using std::cout;
using std::endl;

int AllOne( int x )
{
    return !(~x);
}

int AllZero( int x )
{
    return !x;
}

int main()
{
    cout << AllOne( 0 ) << endl;
    cout << AllOne( 0xffffffff ) << endl;
    cout << AllZero( 0 ) << endl;
    cout << AllZero( 1 ) << endl;
}
