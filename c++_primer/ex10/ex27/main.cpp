#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

int main()
{
    vector<int> vc{1, 1, 2, 2, 3, 4, 1, 2};
    list<int> li;

    unique_copy( vc.begin(), vc.end(), back_inserter( li ) );

    for( auto &c : li )
        cout << c << " ";

    cout << endl;
}
