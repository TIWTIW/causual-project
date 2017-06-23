#include "Sales_data.h"

using namespace std;

Sales_data& Sales_data::combine( const Sales_data &rhs )
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

istream &read( istream &is, Sales_data &item )
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;

    return is;
}

ostream &print( ostream &os, const Sales_data &item )
{
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();

    return os;
}

Sales_data add( const Sales_data &lhs, const Sales_data &rhs )
{
    Sales_data sum = lhs;
    sum.combine( rhs );

    return sum;
}

Sales_data& operator+( Sales_data& lhs, const Sales_data &rhs )
{
    lhs.combine( rhs );

    return lhs;
}


Sales_data& operator+=( Sales_data& lhs, const Sales_data &rhs )
{
    lhs.combine( rhs );

    return lhs;
}

istream &operator>>( istream &is, Sales_data &rhs )
{
    double price;
    is >> rhs.bookNo >> rhs.units_sold >> price;

    if( is )
    {
        rhs.revenue = price * rhs.units_sold;
    }
    else
    {
        rhs = Sales_data();
    }

    return is;
}

ostream &operator<<( ostream &os, const Sales_data &rhs )
{
    os << rhs.bookNo << rhs.units_sold << rhs.revenue;

    return os;
}
double Sales_data::avg_price() const 
{
    if( units_sold )
        return revenue / units_sold;
    else
        return 0;
}

Sales_data::Sales_data( istream &is )
{
    read( is, *this );
}
