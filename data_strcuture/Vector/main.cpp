#include <iostream>
#include "Vector.h"

int main()
{
    Vector<int> V( 1 );

    V.push_back( 2 );

    auto it = V.end();
    V.insert( it, 4 );

    V.erase( V.begin() );
    std::cout << *V.begin() << std::endl;
}
