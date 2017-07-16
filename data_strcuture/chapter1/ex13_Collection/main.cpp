#include "Collection.h"

using namespace std;

int main()
{
    Collection<int> c;

    if( c.isEmpty() )
        cout << "empty!" << endl;

    c.insert( 2 );


}
