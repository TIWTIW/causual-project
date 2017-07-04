#ifndef _QUOTE_H
#define _QUOTE_H

#include <string>
#include <iostream>
#include <utility>

class Quote
{
public:
    Quote() = default;
    Quote( const std::string &book, double sales_price ):
                      bookNo( book ), price( sales_price ) {  }
    //copy constructor
    Quote( const Quote &rhs ) { bookNo = rhs.bookNo; price = rhs.price; std::cout << "Quote copy!" << std::endl; }

    //move constructor
    Quote( Quote &&rhs ) { bookNo = std::move( rhs.bookNo ); price = std::move( rhs.price ); std::cout << "Quote move!" << std::endl; }
    //operator=
    Quote  &operator=( const Quote &rhs ) { bookNo = rhs.bookNo; price = rhs.price; std::cout << "= in Quote!" << std::endl; return *this; }
    
    std::string isbn() const { return bookNo; }

    virtual double net_price( std::size_t n ) const
                    { return n * price; }

    virtual ~Quote() = default;

    virtual void debug() const { std::cout << bookNo << " " << price << std::endl;  }
private:
    std::string bookNo;
protected:
    double price = 0.0;
};

#endif
