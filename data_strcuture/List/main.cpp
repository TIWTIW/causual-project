#include <iostream>
#include "List.h"

using namespace std;

int main()
{
    List<int> l;
    l.push_back( 1 );
    l.push_front( 2 );

    cout << *l.begin() << endl;
}
