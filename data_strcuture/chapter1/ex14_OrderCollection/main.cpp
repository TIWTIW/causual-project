#include "OrderCollection.h"

using namespace std;

int main()
{
    OrderCollection<int> c;

    if( c.isEmpty() )
        cout << "empty!" << endl;

    c.insert( 2 );
    c.insert( 5 );
    c.insert( 1 );

    c.findMax() = 10;
    cout << c.findMax() << endl;
    cout << c.findMin() << endl;


}
