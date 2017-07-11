#ifndef _SP_H
#define _SP_H

#include <memory>

template <typename T>
class SP
{
public:
    //construct and delete
    SP() : p( new T() ), use( new int( 1 ) ) { }
    SP( const SP &rhs );
    explicit SP( T *d ) : p( d ), use( new int( 1 ) ) { }
    ~SP();
    
    //operator
    SP &operator=( const SP &rhs );
    T &operator*() { return *p; }
    T &operator*() const { return *p; }

private:
    T *p;
    int *use;
};

template <typename T>
SP<T>::SP( const SP<T> &rhs )
{
    p = rhs.p;
    use = rhs.use;

    if( use )
        ++*use;
}
template <typename T>
SP<T>::~SP()
{
    if( use && --*use == 0 )
    {
        delete p;
        delete use;
    }
}
template <typename T>
SP<T> &SP<T>::operator=( const SP<T> &rhs )
{
    if( rhs.use )
        ++*rhs.use;

    if( use && --*use == 0 )
    {
        delete p;
        delete use;
    }

    p = rhs.p;
    use = rhs.use;

    return *this;
}

#endif
