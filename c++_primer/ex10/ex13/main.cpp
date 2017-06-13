#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool largerThanFive( string &s )
{
    return s.size() >= 5;
}

int main()
{
    vector<string> vs{"asdasd", "fas", "afasf", "1as"};

    auto ie = partition( vs.begin(), vs.end(), largerThanFive );

    for( auto it = vs.begin(); it != ie; ++it )
        cout << *it << " ";

    cout << endl;

}
