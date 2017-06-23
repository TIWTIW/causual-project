#ifndef _SALES_DATA
#define _SALES_DATA

#include <string>
#include <iostream>

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
Sales_data &operator+=( Sales_data&, const Sales_data& );
std::istream &operator>>( std::istream&, Sales_data& );
std::ostream &operator<<( std::ostream&, const Sales_data& );

#endif
