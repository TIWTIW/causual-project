#ifndef _SALES_DATA
#define _SALES_DATA

#include <string>
#include <iostream>
#include <stdexcept>

class out_of_stock : public std::runtime_error 
{
public:
    explicit out_of_stock( const std::string &s ) : std::runtime_error( s ) {}
};

class isbn_mismatch : public std::logic_error
{
public:
    explicit isbn_mismatch( const std::string &s ) : std::logic_error( s ) {}
    isbn_mismatch( const std::string &s, const std::string &lhs, const std::string &rhs ) : std::logic_error( s ), left( lhs ), right( rhs ) {}
    const std::string left, right;
};

class Sales_data
{
friend Sales_data add( const Sales_data&, const Sales_data& );
friend std::istream &read( std::istream&, Sales_data& );
friend std::ostream &print( std::ostream&, const Sales_data& );
friend std::istream &operator>>( std::istream&, Sales_data& );
friend std::ostream &operator<<( std::ostream&, const Sales_data& );

public:
    Sales_data() = default;
    Sales_data( const std::string &s ) : bookNo( s ) { }
    Sales_data( const std::string &s, unsigned n, double p ) :
                bookNo( s ), units_sold( n ), revenue( p * n ){ std::cout << "This is 3 para" << std::endl; }
    Sales_data( std::istream & );
    Sales_data( unsigned n ) : Sales_data( "", n, 0 ) {  std::cout << "This is one para" << std::endl; }

    std::string isbn() const { return bookNo; }
    Sales_data &combine( const Sales_data& );
    Sales_data &operator+= ( const Sales_data &rhs );

private:
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data add( const Sales_data&, const Sales_data& );
std::ostream &print( std::ostream&, const Sales_data& );
std::istream &read( std::istream&, Sales_data& );
Sales_data &operator+( Sales_data&, const Sales_data& );
//Sales_data &operator+=( Sales_data&, const Sales_data& );
std::istream &operator>>( std::istream&, Sales_data& );
std::ostream &operator<<( std::ostream&, const Sales_data& );

#endif
