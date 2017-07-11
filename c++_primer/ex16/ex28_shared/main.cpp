#include "sp.h"
#include <iostream>

using namespace std;

int main()
{
    SP<int> a;
    SP<int> b;

    *a = ++*a;

    cout << *a << endl;

    a = b;

    ++*a;
    ++*a;
    cout << *a << endl;
    cout << *b << endl;


}
