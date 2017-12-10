#include "memory/zft_default_alloc.h"
#include "memory/zft_simple_alloc.h"
#include <iostream>

int main()
{
    zft::simple_alloc<int, zft::alloc> int_alloc;

    int *p = int_alloc.allocate(120);
    int_alloc.deallocate(p, 20);

    std::cout << p << std::endl;

}
