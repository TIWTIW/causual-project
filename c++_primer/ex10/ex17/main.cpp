#include <iostream>
#include "Sales_data.h"
#include <vector>
#include <algorithm>

using namespace std;

bool compareIsbn( Sales_data &sd1, Sales_data &sd2 )
{
    return sd1.isbn() < sd2.isbn();
}

int main()
{
    vector<Sales_data> vsd{string("123"), string("234"), string("1235"), string("431")};

    sort( vsd.begin(), vsd.end(), []( const Sales_data &s1, const Sales_data &s2 ){ return s1.isbn() < s2.isbn(); } );

    for( auto &sd : vsd )
    {
        cout << sd.isbn() << " ";
    }

    cout << endl;

    return 0;
}
