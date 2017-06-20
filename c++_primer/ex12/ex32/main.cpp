#include "TextQuery.h"
#include "QueryResult.h"

using namespace std;

ostream & print( ostream & os, const QueryResult & qr )
{
    os << qr.sought << " occurs " << qr.lines->size() << " " << endl;
    for( auto num : *qr.lines )
        os << "\t(line " << num + 1 << ") "
            << *( qr.file.begin_s() + num ) << endl;
    return os;
}

void runQueries( ifstream & infile )
{
    TextQuery tq( infile );
    while( true )
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if( !( cin >> s ) || s == "q" )
            break;
        print( cout, tq.query( s ) ) << endl;
    }
}


int main( int argc, char *argv[] )
{
    string s = argv[1];
    ifstream in( s );
    runQueries( in );

    return 0;

}
