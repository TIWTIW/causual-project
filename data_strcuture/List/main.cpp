#include <iostream>
#include "List.h"

using namespace std;

int main()
{
    List<int> l;
    l.push_back( 1 );
    l.push_front( 2 );

    List<int> a;
    a.splice( a.begin(), l );
    a.print();
}
