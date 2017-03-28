/*************************************
 * function:见数据结构与算法分析 1.13
 * Name:zft
 * Time:2017.3.27
 * ***********************************/
#include <iostream>
#include <vector>

using namespace std;

template<typename Object>
class Collection
{
public:
    bool isEmpty()
    { if( vc.empty() )
        return true;
    else
        return false;
    }

    void makeEmpty()
    {
        vc.clean();
    }

    void insert( const Object x )
    {
        vc.insert( x );
    }

    void remove( Object & x )
    {
        vc.remove( x );
    }

    bool contains( const Object & x )
    {
        for( int i = 0; i < vc.size(); ++i )
        {
            if( vc[i] == x )
                return true;
        }

        return false;
    }
private:
    vector<Object> vc;
};
