#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<string> vs{ "asd", "fef", "asd", "qwe", "fef" };

    sort( vs.begin(), vs.end() );

    for( auto &s : vs )
        cout << s << " ";

    cout << endl;

    auto end_unique = unique( vs.begin(), vs.end() );

    for( auto &s : vs )
        cout << s << " ";

    cout << endl;

    vs.erase( end_unique, vs.end() );


    for( auto &s : vs )
        cout << s << " ";

    cout << endl;
}
