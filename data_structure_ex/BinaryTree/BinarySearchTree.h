#include <iostream>

struct BinaryNode
{
    int element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( const int & theElement, BinaryNode *lt, BinaryNode *rt )
                    : element{ theElement }, left{ lt }, right{ rt } {  }
 };
class BinarySearchTree
{
public:
    BinarySearchTree(  );
    BinarySearchTree( const BinarySearchTree & rhs );
    ~BinarySearchTree(  );

    const int & findMin( ) const;
    const int & findMax( ) const;
    bool contains( const int & x ) const;
    bool isEmpty(  ) const;
    void printTree( std::ostream & out = std::cout ) const;

    void makeEmpty(  );
    void insert( const int & x );
    void remove( const int & x );

    BinarySearchTree & operator=( const BinarySearchTree & rhs );

private:
    BinaryNode *root;

    void insert( const int & x,BinaryNode * & t );
    void remove( const int & x, BinaryNode * & t );
    BinaryNode * findMin( BinaryNode *t ) const;
    BinaryNode * findMax( BinaryNode *t ) const;
    bool contains( const int & x, BinaryNode *t ) const;
    void makeEmpty( BinaryNode * & t );
    void printTree( BinaryNode *t, std::ostream & out) const;
    BinaryNode * clone( BinaryNode *t ) const;
};

