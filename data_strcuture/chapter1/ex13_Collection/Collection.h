#ifndef _COLLECTION_H
#define _COLLECTION_H

#include <vector>
#include <iostream>
#include <utility>

//The Object should have operator=
template <typename Object>
class Collection
{
public:
    bool isEmpty();
    void makeEmpty();

    void insert( Object & );
    void insert( Object && );

    void remove( Object & );
    bool contains( Object & );

private:
    std::vector<Object> vO;
};

template <typename Object>
bool Collection<Object>::isEmpty()
{
    if( vO.empty() )
        return true;

    return false;
}

template <typename Object>
void Collection<Object>::makeEmpty()
{
    vO.clear();
}

template <typename Object>
void Collection<Object>::insert( Object &obj )
{
    vO.push_back( obj );
}

template <typename Object>
void Collection<Object>::insert( Object &&obj )
{
    vO.push_back( std::move( obj ) );
}


template <typename Object>
bool Collection<Object>::contains( Object &obj )
{
    if( vO.find( obj ) != vO.end() )
        return true;

    return false;
}

template <typename Object>
void Collection<Object>::remove( Object &obj )
{
    if( contains( obj ) )
    {
        vO.erase( vO.find( obj ) );
    }
    else
    {
        std::cout << "There is no obj in the Collection to be removed!" << std::endl;
    }
}

#endif
