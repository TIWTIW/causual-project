#include "Bulk_quote.h"
#include <iostream>
#include <vector>
#include <memory>
#include "Basket.h"
#include "common.h"

using namespace std;

int main( int argc, char *argv[] )
{
   // Quote Q( "123", 15 );
    Bulk_quote Bq( "234", 15, 10, 0.2 );
    Bulk_quote Bq2( "213", 12, 13, 0.2 );
    Basket B;

    vector<Quote> vQ;
    vector<shared_ptr<Quote>> vsQ;

    vQ.push_back( Bq );
    vQ.push_back( Bq2 );

    vsQ.push_back( make_shared<Bulk_quote>( Bq ) );
    vsQ.push_back( make_shared<Bulk_quote>( Bq2 ) );
    B.add_item( Bq );
    B.add_item( Bq2 );
    //print_total( cout, Q, 10 );
    double total_price = 0;
    double total_price2 = 0;

    for( auto &c : vQ )
    {
        total_price +=  c.net_price( 1 );
    }

    for( auto &c : vsQ )
    {
        total_price2 +=  c->net_price( 1 );
    }

    cout << total_price << endl;
    cout << total_price2 << endl;
    
    B.total_receipt( cout );

    return 0;
}
