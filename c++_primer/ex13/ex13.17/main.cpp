/***********拷贝构造函数的重要性*********
 * function:存在拷贝构造函数时可以分配不同
 * 值，否则分配值相同
 * Name:zft
 * Time:2017.3.28
 * *************************************/

#include <iostream>

using namespace std;

int i = 0;

class numbered
{
public:
    numbered() : mysn( ++i ) {}
    numbered ( numbered &r_number ) { mysn = ++i; }
    int mysn;
};

void f( const numbered &s )
{
    cout << s.mysn << endl;
}

int main( int argc, char *argv[] )
{
    numbered a, b = a, c = b;
    f( a );
    f( b );
    f( c );
}
