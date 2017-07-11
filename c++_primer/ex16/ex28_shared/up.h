#ifndef _UP_H
#define _UP_H

#include <memory>

template <typename T>
class UP
{
public:
    //construct
    UP() : p( nullptr ) { }
    explicit UP( T *d ) : p( d ) { }
    ~UP() { if( p ) delete p; }

    //operator
    UP &operator=( const UP &rhs ) = delete;

    T &operator*() { if( p ) return *p; }
    T &operator*() const { if( p ) return *p; }

    //function
    T *release();
    void reset( T *new_p );
private:
    T *p;
};

template <typename T>
T *UP<T>::release()
{
    T *q = p;
    p = nullptr;

    return q;
}

template <typename T>
void UP<T>::reset( T *new_p )
{
    if( p )
        delete p;

    p = new_p;
}

#endif
