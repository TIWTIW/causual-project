#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

bool check_size( const string &s, string::size_type sz )
{
    return s.size() <= sz;
}

int main()
{
    string s( "gdsf" );

    vector<int> vc{1, 2, 3, 64};

    auto it = find_if( vc.begin(), vc.end(), bind( check_size, s, placeholders::_1 ) );

    if( it != vc.end() )
        cout << *it << endl;
}
