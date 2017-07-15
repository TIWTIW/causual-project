#include <memory>
#include <iostream>
#include <typeinfo>

using namespace std;

struct A
{
    A() {}
    virtual void x() {}
    virtual ~A() {}
};

struct B : public A
{
    B() : A() {}
    virtual void x() {}
    virtual ~B() {}
};

int main()
{
    A *a = new A;
    if( dynamic_cast<B *>( a ) != NULL )
    {
        cout << "success!" << endl;
    }
    else
    {
        cout << "fail!" << endl;
    }

    B *b = new B;
    A &ra = *b;
    cout << typeid( ra ).name() << endl;
}
