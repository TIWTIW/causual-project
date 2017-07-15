#include <cstdlib>
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace std;

void *operator new( size_t size )
{
    if( void *mem = malloc( size ) )
        return mem;
    else
        throw bad_alloc{};
}

void operator delete( void *mem ) noexcept
{
    free( mem );
}

int main()
{
    int *a = new int{ 4 };
    
    cout << *a << endl;

    delete a;
}
