#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

using namespace std;

int main( int argc, char *argv[] )
{
    ifstream file( argv[1] );
    ofstream odd_out_file( argv[2] ), even_out_file( argv[3]  );

    istream_iterator<int> it( file ), eof;
    ostream_iterator<int> odd( odd_out_file, " " ), even( even_out_file, "\n" );

    while( it != eof )
    {
        ( *it % 2 ) ? ( *odd++ = *it ) : ( *even++ = *it );
        ++it;
    }


}
