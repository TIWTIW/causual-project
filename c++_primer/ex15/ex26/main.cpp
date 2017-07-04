#include "Bulk_quote.h"
#include <iostream>

using namespace std;

double print_total( ostream & os, const Quote & item, size_t n )
{
    double ret = item.net_price( n );
    os << "ISBN: " << item.isbn()
       << " # sold: " << n << " total due: " << ret << endl;

    return ret;
}

int main( int argc, char *argv[] )
{
    Quote Q( "123", 15 );
    Bulk_quote Bq( "234", 15, 10, 0.2 );

    print_total( cout, Q, 10 );
    print_total( cout, Bq, 10 );

    Quote c( Q );
    c = Q;

    Q.debug();
    Bq.debug();

    return 0;
}
