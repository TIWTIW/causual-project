#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main()
{
    vector<pair<string, int>> vp;

    string s;
    int temp;

    while( cin >> s )
    {
        cin.clear();
        cin >> temp;

        pair<string, int> p( s, temp );
        vp.push_back( p );
    }

    for( auto &p : vp )
    {
        cout << p.first << ":" << p.second << endl;
    }
}
