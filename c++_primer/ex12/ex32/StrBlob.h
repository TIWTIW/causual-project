/***************StrBlob类****************
 * function:主要是为了练习智能指针
 * Name:zft
 * Time:2017.3.29
 * ************************************/
#ifndef _SB_H
#define _SB_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob() : data( std::make_shared<std::vector<std::string>>() ) {}
    StrBlob( std::initializer_list<std::string> i1 ) : data( std::make_shared<std::vector<std::string>>(i1) ) {}
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    void push_back( const std::string &t ) { data->push_back(t); }
    void pop_back();
    std::string &front();
    std::string &back();
 //   StrBlobPtr begin();// { return StrBlobPtr( *this ); }
   // StrBlobPtr end() ;//{ return StrBlobPtr( *this, data->size() ); }
    const std::vector<std::string>::iterator begin_s()  const { return data->begin(); }
    const std::vector<std::string>::iterator end_s()  const { return data->end(); }
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check( size_type i, const std::string &msg ) const;
};

/*class StrBlobPtr
{
public:
    StrBlobPtr() : curr( 0 ) {  }
    StrBlobPtr( StrBlob& a, size_t sz = 0 ) :
                wptr( a.data ), curr( sz ) {  }
    string& deref() const;
    StrBlobPtr& incr();
private:
    shared_ptr<vector<string>> check( size_t i, const string& msg) const;
    weak_ptr<vector<string>> wptr;
    size_t curr;
};

shared_ptr<vector<string>> StrBlobPtr::check( size_t i, const string& msg ) const
{
    auto ret = wptr.lock();
    if( !ret )
        throw runtime_error( "unbound StrBlobPtr" );
    if( i >= ret->size() )
        throw out_of_range( msg );
    return ret;
}

string& StrBlobPtr::deref() const
{
    auto p = check( curr, "dereference past end" );
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
    check( curr, "increment past end of StrBlobPtr" );
    ++curr;
    return *this;
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr( *this );
}

StrBlobPtr StrBlob::end()
{
    auto ret = StrBlobPtr( *this, data->size() );
    return ret;
}
*/
/*void StrBlob::check( size_type i, const std::string &msg ) const
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
}*/

#endif
