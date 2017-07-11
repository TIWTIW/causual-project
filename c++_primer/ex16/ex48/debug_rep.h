#ifndef _DR_H
#define _DR_H

#include <sstream>
#include <string>

using std::string;
using std::ostringstream;

template <typename T>
string debug_rep( const T &t )
{
    ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
string debug_rep( T *p )
{
    ostringstream ret;
    ret << "pointer:" << p;

    if( p )
        ret << " " << debug_rep( *p );
    else
        ret << " null pointer ";

    return ret.str();
}

string debug_rep( const string &s )
{
    return '"' + s + '"';
}


#endif
