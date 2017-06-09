#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string s;
    vector<string> vs;

    while( cin >> s )
    {
        vs.push_back( s );
    }

    for( auto &x : vs )
    {
        for( auto &c : x )
        {
            c = toupper( c );
        }
    }

    for( auto &x : vs )
        cout << x << endl;

    return 0;
}
