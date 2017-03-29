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
#include "StrBlobPtr.h"

class StrBlobPtr;
class StrBlob
{
friend class StrBlobPtr;
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
    StrBlobPtr begin() { return StrBlobPtr( *this ); }
    StrBlobPtr end() { return StrBlobPtr( *this, data->size() ); }
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check( size_type i, const std::string &msg ) const;
};

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

#endif
