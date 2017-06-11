#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    string s;
    vector<string> vs;

    ifstream ifs( "infile" );

    while( getline( ifs, s ) )
        vs.push_back( s );

    for( auto &s : vs )
    {
        istringstream is( s );

        string word;
        while( is >> word )
            cout << word << ends;

        cout << endl;
    }

    return 0;
}
