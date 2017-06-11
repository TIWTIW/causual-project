#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void read( ifstream &ifs, vector<string> &vs )
{
    string s;
    while( getline( ifs, s ) )
    {
        vs.push_back( s );
    }
}

int main()
{
    ifstream x( "infile" );
    vector<string> vs;

    read( x, vs );

    for( auto &s : vs )
    {
        cout << s << endl;
    }

    return 0;
}
