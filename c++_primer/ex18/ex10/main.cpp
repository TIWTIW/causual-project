#include <iostream>
#include "Sales_data.h"

using namespace std;

int main()
{
    Sales_data total( 1 );
/*
    if( read( cin, total ) )
    {
        Sales_data trans;
        while( read( cin, total ) )
        {
            if( total.isbn() == trans.isbn() )
            {
                total.combine( trans );
            }
            else
            {
                print( cout, total ) << endl;
                total = trans;
            }
        }
        print( cout, total ) << endl;
    }
    else
    {
        cerr << "No data?!" << endl;
    }*/
    Sales_data item1, item2, sum;
    while( cin >> item1 >> item2 )
    {
        try
        {
            sum += item1;
        }
        catch ( const isbn_mismatch &e )
        {
            cerr << e.what() << ":left isbn(" << e.left
                 << ")rught isbn(" << e.right << ")" << endl;
        }
            
    }
    return 0;
}
