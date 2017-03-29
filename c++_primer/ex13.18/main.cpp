/***********Employee类*********
 * function:包含雇员姓名和唯一的雇员证号
 * Name:zft
 * Time:2017.3.28
 * *************************************/

#include <iostream>
#include <string>

using namespace std;


class Employee
{
public:
    Employee() : number( ++i ), name( " " ) {}
    Employee( string s ) : number( ++i ),name( s ) { }
    Employee( Employee & Ee ) : number( ++i ), name( Ee.name ) {}
    int number;
private:
    static int i;
    string name;
};

int Employee::i = 0;

void f( const Employee & Em )
{
    cout << Em.number << endl;
}

int main( int argc, char *argv[] )
{
    Employee a, b = a, c = b;
    f( a );
    f( b );
    f( c );
}
