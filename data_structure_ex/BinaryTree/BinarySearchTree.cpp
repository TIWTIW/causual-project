#include "BinarySearchTree.h"

using namespace std;

bool BinarySearchTree::contains( const int & x, BinaryNode *t ) const
{
    if( t == nullptr )
        return false;
    else if( x < t->element )
        return contains( x, t->left );
    else if( x > t->element )
        return contains( x, t->right );
    else
        return true;
}

BinaryNode * BinarySearchTree::findMin( BinaryNode *t ) const
{
    if( t == nullptr )
        return nullptr;
    if( t->left == nullptr )
        return t;
    return findMin( t->left );
}

BinaryNode * BinarySearchTree::findMax( BinaryNode *t ) const
{
    if( t != nullptr )
        while( t->right != nullptr )
            t = t->right;
    return t;
}

void BinarySearchTree::insert( const int & x, BinaryNode * & t )
{
    static int i = 0;
    if( t == nullptr )
        t = new BinaryNode{ x, nullptr, nullptr };
    else if( x < t-> element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    else
        ;
}

void BinarySearchTree::remove( const int & x, BinaryNode * & t )
{
    if( t == nullptr )
        return ;
    if( x < t->element )
        remove( x, t->left );
    else if( x > t->element )
        remove( x, t->right );
    else if( t->left != nullptr && t->right != nullptr )
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else
    {
        BinaryNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }
}

bool BinarySearchTree::contains( const int & x ) const
{
    return contains( x, root );
}

void BinarySearchTree::insert( const int & x )
{
    insert( x, root );
}

void BinarySearchTree::remove( const int & x )
{
    remove( x, root );
}

void BinarySearchTree::makeEmpty( BinaryNode * & t )
{
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
}

BinarySearchTree::~BinarySearchTree(  )
{
    makeEmpty( root );
}

BinarySearchTree::BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
{
    root = clone( rhs.root );
}

BinarySearchTree::BinarySearchTree(  )
{
    cout << "construct.." << endl;
    root = new BinaryNode{ 0, nullptr, nullptr };

    cout << "success" << endl;
}
BinaryNode * BinarySearchTree::clone( BinaryNode *t ) const
{
    if( t == nullptr )
        return nullptr;
    else
        return new BinaryNode{ t->element, clone( t->left ),
                               clone( t->right ) };
}

void BinarySearchTree::printTree( BinaryNode *t, ostream & out ) const
{
     if( t !=  nullptr )
     {
        printTree( t->left, out );
        out << t->element << endl;
        printTree( t->right,out );
    }
}

void BinarySearchTree::printTree( ostream & out ) const
{
    printTree( root, out );
}
