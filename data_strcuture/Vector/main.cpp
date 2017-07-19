#include <iostream>
#include "Vector.h"

int main()
{
    Vector<int> V( 1 );

    V.push_back( 2 );

    std::cout << V.back() << std::endl;
}
