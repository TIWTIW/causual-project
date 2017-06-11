#include <iostream>
#include <string>
#include <list>

using namespace std;

int main()
{
    string s;
    list<string> ds;

    while( cin >> s )
        ds.push_back( s );

    for( auto it = ds.cbegin(); it != ds.cend(); ++it )
        cout << *it << endl;

    return 0;
}
