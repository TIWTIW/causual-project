#ifndef VEC_QUEUE_H
#define VEC_QUEUE_H

#include <iostream>
#include <vector>

template <typename Object>
class Vec_Queue
{
public:
    Vec_Queue() : sO( std::vector<Object>{} ), theCapacity( 20 ), theSize( 0 ), front( nullptr ), back( nullptr )
    {
        sO.resize( theCapacity );
    }
    ~Vec_Queue() {}

    void enqueue( const Object &x )
    {
        if( theSize == theCapacity )
        {
            std::cout << "full!" << std::endl;
            return ;
        }

        if( back == nullptr )
        {
            sO[theSize] = x;
            back = &sO[0];
            front = &sO[0];
            theSize++;
            return ;
        }
        if( back == &sO[theCapacity- 1 ] )
        {
            sO[0] = x;
            back = &sO[0];
        }
        sO[theSize] =  x;
        theSize++;
        back = back + 1;
    }

    Object dequeue()
    {
        Object result;
        if( theSize == 0 )
        {
            std::cout << "empty!" << std::endl;
            exit( -1 );
        }

        if( front == &sO[theCapacity - 1] )
        {
            result = *front;
            front = &sO[0];
            theSize--;
            return result;
        }
        result = *front;
        front = front + 1;
        theSize--;
        return result;
    }

    void print()
    {
        for( auto &c : sO )
            std::cout << c << " ";
        std::cout << std::endl;
    }
private:
    std::vector<Object> sO;
    int theCapacity;
    int theSize;
    Object *front;
    Object *back;
};


#endif
