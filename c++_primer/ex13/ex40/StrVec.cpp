#include "StrVec.h"

using namespace std;

void StrVec::push_back( const string &s )
{
    chk_n_alloc();
    alloc.construct( first_free++, s );
}

pair<string*, string*> 
StrVec::alloc_n_copy( const string *b, const string *e )
{
    auto data = alloc.allocate( e - b );
    return { data, uninitialized_copy( b, e, data ) };
}

void StrVec::free()
{
/*    if( elements )
    {
        for( auto p = first_free; p != elements; )
            alloc.destroy( --p );
        alloc.deallocate( elements, cap - elements );
    }*/

    //for_each
    if( elements )
    {
        for_each( first_free, elements, []( string &s ){ alloc.destroy( &s ); } );
    }
}

StrVec::StrVec( const StrVec &s )
{
    auto newdata = alloc_n_copy( s.begin(), s.end() );
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec &StrVec::operator=( const StrVec &rhs )
{
    auto data = alloc_n_copy( rhs.begin(), rhs.end() );
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate( newcapacity );
    auto dest = newdata;
    auto elem = elements;
    for( size_t i = 0; i != size(); ++i )
        alloc.construct( dest++, std::move( *elem++ ) );
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reallocate( size_t newcapacity )
{
    auto newdata = alloc.allocate( newcapacity );
    auto dest = newdata;
    auto elem = elements;
    for( size_t i = 0; i != size(); ++i )
        alloc.construct( dest++, std::move( *elem++ ) );
    free();
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}

void StrVec::reserve( size_t newcapacity )
{
    if( newcapacity <= capacity() )
        return ;
    reallocate( newcapacity );
}

void StrVec::resize( size_t newsize )
{
    if( newsize > size()  )
    {
        while( size() < newsize )
            push_back( "" );
    }
    else if( newsize < size() )
    {
        while( size() > newsize )
            alloc.destroy( --first_free );
    }
}

StrVec::StrVec( initializer_list<string> &list_string )
{
    auto newdata = alloc_n_copy( list_string.begin(), list_string.end() );
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec( StrVec &&SV ) noexcept : elements( SV.elements ), first_free( SV.first_free ), cap( SV.cap )
{   
    SV.elements = SV.first_free = SV.cap = nullptr;
}

StrVec &StrVec::operator=( StrVec &&s ) noexcept
{
    if( &s != this )
    {
        free();
        elements = s.elements;
        first_free = s.first_free;
        cap = s.cap;
        s.elements = s.first_free = s.cap = nullptr;
    }

    return *this;
}
