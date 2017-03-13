#include "AVLTree.h"

using namespace std;

int main()
{
    AVLTree AVLT;

    AVLT.insert( 3 );
    AVLT.insert( 2 );
    AVLT.insert( 1 );

    AVLT.insert( 4 );
    AVLT.insert( 5 );
    AVLT.insert( 6 );
    AVLT.insert( 7 );
    AVLT.insert( 16 );
    AVLT.insert( 15);
    AVLT.insert( 14 );

    AVLT.printTree(cout);

    return 0;
}
