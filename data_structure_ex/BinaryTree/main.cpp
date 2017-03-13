#include "BinarySearchTree.h"

using namespace std;

int main()
{
    BinarySearchTree BST;

    BST.insert( 3 );
    BST.insert( 2 );
    BST.insert( 1 );
    BST.insert( 4 );

    BST.printTree(cout);

    return 0;
}
