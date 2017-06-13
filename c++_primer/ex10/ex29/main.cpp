#include <iterator>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    istream_iterator<string> it( cin ), eof;
    vector<string> vs;
    string s;

    while( it != eof )
        vs.push_back( *it++ );

    for( auto &c : vs )
        cout << c << endl;


}

