#include <iostream>

using namespace std;

struct Base
{
    Base() : mem( 0 ) {}
protected:
    int mem;
};

struct Derived : Base
{
    int get_base_mem() { return Base::mem; }

    Derived( int i ) : mem( i ) {}
    int get_mem() { return mem; }

protected:
    int mem;
};

int main()
{
    Derived d( 42 );

    cout << d.get_mem() << endl;
}
