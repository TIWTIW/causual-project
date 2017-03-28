#include "Collection.h"

int main( int argc, char *argv[] )
{
    Collection<int> C;

    C.insert( 1 );

    if( C.isEmpty() )
        cout << "empty";
    else
        cout << "true";

    cout << endl;

    if( C.contains( 2 ) )
        cout << "true";
    else
        cout << "false";

    C.insert( 2 );

    if( C.contains( 2 ) )
        cout << "true";
    else
        cout << "false";
}
