#include <memory>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    allocator<string> alloc;
    auto const p = alloc.allocate( 20 );

    string s;
    string *q = p;

    while( cin >> s && q != p + 20 )
    {
        alloc.construct( q++, s );
    }

    const size_t size = q - p;

    while( q != p )
    {
        cout << *--q << " ";
        alloc.destroy( q );
    }

    alloc.deallocate( p, 20 );

    cout << endl;


}
