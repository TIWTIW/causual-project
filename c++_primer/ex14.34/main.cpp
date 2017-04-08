/************函数对象类***************
 * function:定义一个函数对象类，执行
 * if-then-else操作，调用运算符重载
 * Name:zft
 * Time:2017.4.7
 * *********************************/
#include <iostream>

using namespace std;

class ite
{
public:
    int operator()( int a, int b, int c )
    { return a ? b : c; }
};

int main( int argc, char *argv[] )
{
    ite ite1;
    cout << ite1( 1, 2, 3 ) << endl;
}

