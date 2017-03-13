#include "AVLTree.h"

using namespace std;

bool AVLTree::contains( const int & x, AVLNode *t ) const
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

int AVLTree::height( AVLNode *t ) const
{
    return t == nullptr ? -1:t->height;
}

void AVLTree::rotateWithLeftChild( AVLNode * & k2 )
{
    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

void AVLTree::doubleWithLeftChild( AVLNode * & k3 )
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

void AVLTree::rotateWithRightChild( AVLNode * & k2 )
{
    AVLNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max( height( k2->right ), height( k2->left ) ) + 1;
    k1->height = max( height( k1->right ), k2->height ) + 1;
    k2 = k1;
}

void AVLTree::doubleWithRightChild( AVLNode * & k3 )
{
    rotateWithLeftChild( k3->right );
    rotateWithRightChild( k3 );
}


static const int ALLOWED_IMBALANCE = 1;

void AVLTree::balance( AVLNode * & t )
{
    if( t == nullptr )
        return;

    if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
        if( height( t->left->left ) >= height( t->left->right ) )
            rotateWithLeftChild( t );
        else
            doubleWithLeftChild( t );
    else
    if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
        if( height( t->right->right ) >= height( t->right->left ) )
            rotateWithRightChild( t );
        else
            doubleWithRightChild( t );

    t->height = max( height( t->left ), height( t->right ) ) + 1;
}

AVLNode * AVLTree::findMin( AVLNode *t ) const
{
    if( t == nullptr )
        return nullptr;
    if( t->left == nullptr )
        return t;
    return findMin( t->left );
}

AVLNode * AVLTree::findMax( AVLNode *t ) const
{
    if( t != nullptr )
        while( t->right != nullptr )
            t = t->right;
    return t;
}

void AVLTree::insert( const int & x, AVLNode * & t )
{
    if( t == nullptr )
        t = new AVLNode{ x, nullptr, nullptr };
    else if( x < t-> element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );

    balance( t );
}

void AVLTree::remove( const int & x, AVLNode * & t )
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
        AVLNode *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->right;
        delete oldNode;
    }

    balance( t );
}

bool AVLTree::contains( const int & x ) const
{
    return contains( x, root );
}

void AVLTree::insert( const int & x )
{
    insert( x, root );
}

void AVLTree::remove( const int & x )
{
    remove( x, root );
}

void AVLTree::makeEmpty( AVLNode * & t )
{
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr;
}

AVLTree::~AVLTree(  )
{
    makeEmpty( root );
}

AVLTree::AVLTree( const AVLTree & rhs ) : root{ nullptr }
{
    root = clone( rhs.root );
}

AVLTree::AVLTree(  )
{
    cout << "construct.." << endl;
    root = new AVLNode{ 0, nullptr, nullptr };

    cout << "success" << endl;
}
AVLNode * AVLTree::clone( AVLNode *t ) const
{
    if( t == nullptr )
        return nullptr;
    else
        return new AVLNode{ t->element, clone( t->left ),
                               clone( t->right ) };
}

void AVLTree::printTree( AVLNode *t, ostream & out ) const
{
     if( t !=  nullptr )
     {
        printTree( t->left, out );
        out << t->element << endl;
        printTree( t->right,out );
    }
}

void AVLTree::printTree( ostream & out ) const
{
    printTree( root, out );
}
