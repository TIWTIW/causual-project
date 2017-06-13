#include <iostream>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

int main()
{
    vector<int> vi{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    list<int> li( 5 );

    copy( vi.rbegin() + 3, vi.rbegin() + 7, li.begin() );

    for( auto &i : li )
        cout << i << " ";

    cout << endl;
}
