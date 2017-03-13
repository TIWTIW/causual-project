#include <iostream>

struct AVLNode
{
    int element;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode( const int & theElement, AVLNode *lt, AVLNode *rt, int h = 0 )
                    : element{ theElement }, left{ lt }, right{ rt }, height( h ) {  }
 };
class AVLTree
{
public:
    AVLTree(  );
    AVLTree( const AVLTree & rhs );
    ~AVLTree(  );

    const int & findMin( ) const;
    const int & findMax( ) const;
    bool contains( const int & x ) const;
    bool isEmpty(  ) const;
    void printTree( std::ostream & out = std::cout ) const;

    void makeEmpty(  );
    void insert( const int & x );
    void remove( const int & x );

    AVLTree & operator=( const AVLTree & rhs );

private:
    AVLNode *root;

    void rotateWithLeftChild( AVLNode * & K2 );
    void doubleWithLeftChild( AVLNode * & K3 );
    void rotateWithRightChild( AVLNode * & K2 );
    void doubleWithRightChild( AVLNode * & K3 );
    int height( AVLNode *t ) const;
    void balance( AVLNode * & t );
    void insert( const int & x,AVLNode * & t );
    void remove( const int & x, AVLNode * & t );
    AVLNode * findMin( AVLNode *t ) const;
    AVLNode * findMax( AVLNode *t ) const;
    bool contains( const int & x, AVLNode *t ) const;
    void makeEmpty( AVLNode * & t );
    void printTree( AVLNode *t, std::ostream & out) const;
    AVLNode * clone( AVLNode *t ) const;
};

