#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main()
{
    string s;
    deque<string> ds;

    while( cin >> s )
        ds.push_back( s );

    for( auto it = ds.cbegin(); it != ds.cend(); ++it )
        cout << *it << endl;

    return 0;
}
