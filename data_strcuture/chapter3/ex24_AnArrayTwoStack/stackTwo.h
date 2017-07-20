#ifndef _STACK_TWO_H
#define _STACK_TWO_H

#include <iostream>
#include <algorithm>

template <typename Object>
class stackTwo
{
public:
    stackTwo( int size = 20 ) 
    {
        theSize = size;
        obejcts = new Object[theSize];
        leftStackSize = 0;
        rightStackSize = 0;
    }

    ~stackTwo()
    {
        delete [] obejcts;
    }

    void stackOnePush( const Object &x )
    {
        if( leftStackSize + rightStackSize == theSize )
        {
            std::cout << "full!" << std::endl;
            return ;
        }

        obejcts[leftStackSize++] = x;
    }

    void stackTwoPush( const Object &x )
    {
        if( leftStackSize + rightStackSize == theSize )
        {
            std::cout << " full! " << std::endl;
            return;
        }
        obejcts[theSize-rightStackSize-1] = x;
        rightStackSize++;
    }
    
    Object stackOnePop()
    {
        if( leftStackSize == 0 )
        {
            std::cout << "stack one empty!" << std::endl;
            return Object{};
        }
       Object result = obejcts[leftStackSize-1];
       leftStackSize--;
        return result;
    }

    Object stackTwoPop()
    {
        if( rightStackSize == 0 )
        {
            std::cout << "stack two empty!" << std::endl;
            return Object{};
        }

        Object result = obejcts[theSize-rightStackSize];
        rightStackSize--;
        return result;
    }
private:
    Object *obejcts;
    int theSize;
    int leftStackSize;
    int rightStackSize;
};


#endif
