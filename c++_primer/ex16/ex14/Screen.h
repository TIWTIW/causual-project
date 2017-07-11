#ifndef _SCREEN_H
#define _SCREEN_H

#include <iostream>
#include <string>

class Window_mgr;

template <int N, int M> 
class Screen
{
friend class Window_mgr;
public:
    typedef std::string::size_type pos;
    Screen &set( char );
    Screen &set( pos, pos, char );
    Screen &display( std::ostream &os )
                   { do_display( os ); return *this; }
    const Screen &display( std::ostream &os ) const
                   { do_display( os ); return *this; }
    Screen() : contents( N * M, ' ' ) { }
    Screen( char c ) : contents( N * M, c ) { }
    char get() const { return contents[cursor]; }
    inline char get( pos ht, pos wd ) const;
    Screen &move( pos r, pos c );
    Screen &clear( char = bkground );
private:
    static const char bkground = ' ';

private:
    
    void do_display( std::ostream &os ) const { os << contents; }

    pos cursor = 0;
    std::string contents;
};

template <int N, int M>
inline Screen<N, M> &Screen<N, M>::clear( char c )
{
    contents = std::string( N * M, c );
    return *this;
}

template <int N, int M>
inline Screen<N, M> &Screen<N, M>::set( char c )
{
    contents[cursor] = c;
    return *this;
}

template <int N, int M>
inline Screen<N, M> &Screen<N, M>::set( pos r, pos col, char ch )
{
    contents[r * M + col] = ch;
    return *this;
}

template <int N, int M>
inline
Screen<N, M> &Screen<N, M>::move( pos r, pos c )
{
    pos row = r * M;
    cursor = row + c;
    return *this;
}

template <int N, int M>
char Screen<N, M>::get( pos r, pos c ) const
{
    pos row = r * M;
    return contents[row + c];
}

#endif
