#ifndef _ORDER_COLLECTION_H
#define _ORDER_COLLECTION_H

#include <vector>
#include <iostream>
#include <utility>

//The Comparable should have operator= operator< and operator>
template <typename Comparable>
class OrderCollection
{
public:
    bool isEmpty();
    void makeEmpty();

    void insert( const Comparable & );
    void insert( Comparable && );

    void remove( Comparable & );
    
    Comparable &findMin();
    Comparable &findMax();

private:
    std::vector<Comparable> vO;
};

template <typename Comparable>
bool OrderCollection<Comparable>::isEmpty()
{
    if( vO.empty() )
        return true;

    return false;
}

template <typename Comparable>
void OrderCollection<Comparable>::makeEmpty()
{
    vO.clear();
}

template <typename Comparable>
void OrderCollection<Comparable>::insert( const Comparable &obj )
{
    vO.push_back( obj );
}

template <typename Comparable>
void OrderCollection<Comparable>::insert( Comparable &&obj )
{
    vO.push_back( std::move( obj ) );
}


template <typename Comparable>
void OrderCollection<Comparable>::remove( Comparable &obj )
{
    if( vO.find( obj ) != vO.end() )
    {
        vO.erase( vO.find( obj ) );
    }
    else
    {
        std::cout << "There is no obj in the OrderCollection to be removed!" << std::endl;
    }
}

template <typename Comparable>
Comparable &OrderCollection<Comparable>::findMin()
{
    if( isEmpty() )
    {
        std::cout << "is empty! no FindMin! return an empty!" << std::endl;
        Comparable temp{};
        return temp;
    }

    int index = 0;
    for( int i = 0; i < vO.size(); ++i )
    {
        if( vO[index] > vO[i] )
            index = i;
    }
    return vO[index];
}

template <typename Comparable>
Comparable &OrderCollection<Comparable>::findMax()
{
    if( isEmpty() )
    {
        std::cout << "is empty! no FindMax! return an empty!" << std::endl;
        Comparable temp{};
        return temp;
    }

    int index = 0;
    for( int i = 0; i < vO.size(); ++i )
    {
        if( vO[index] < vO[i] )
            index = i;
    }
    return vO[index];
}
#endif
