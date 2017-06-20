#include "StrBlob.h"

using namespace std;


void StrBlob::check( size_type i, const std::string &msg ) const
{
    if( i >= data->size() )
        throw std::out_of_range(msg);
}

std::string &StrBlob::front()
{
    check( 0, "front on empty StrBlob" );
    return data->front();
}

std::string &StrBlob::back()
{
    check( 0, "back on empty StrBlob" );
    return data->back();
}

void StrBlob::pop_back()
{
    check( 0, "pop_back on empty StrBlob" );
    return data->pop_back();
}
