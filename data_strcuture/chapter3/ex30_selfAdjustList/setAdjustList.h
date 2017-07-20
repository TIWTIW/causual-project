#ifndef SELF_ADJUST_H
#define SELF_ADJUST_H

#include <iostream>

template <typename Object>
class SelfAdjustList
{
public:
    SelfAdjustList( int size = 20 ) : theCapacity( size ) 
    {
        theSize = 0;
        objects = new Object[theCapacity];
    }
    ~SelfAdjustList()
    {
        delete [] objects;
    }

    void insert( const Object &x  )
    {
        if( theSize == 0 )
        {
            objects[theSize++] = x;
            return;
        }
        theSize++;
        for( int i = theSize; i > 0; --i )
        {
            objects[i] = objects[i-1];
        }
        objects[0] = x;
    }

    void find( const Object &x )
    {
        int position = 0;
        for( ; position < theSize; ++position )
            if( objects[position] == x )
                break;

        if( position == theSize )
        {
            std::cout << "not find!" << std::endl;
        }

        Object temp = x;
        for( ; position > 0; --position )
        {
            objects[position] = objects[position - 1];
        }
        objects[0] = temp;
    }

    void print()
    {
        for( int i = 0; i < theSize; ++i )
        {
            std::cout << objects[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    Object *objects;
    int theSize;
    int theCapacity;
};

#endif
