#include <iostream>
#include <vector>
#include <iterator>
#include <list>

using namespace std;

int main()
{
    vector<int> vc{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> i, bi;

    list<int> li;

    copy( vc.begin(), vc.end(), inserter( i, i.begin() ) );
    copy( vc.begin(), vc.end(), back_inserter( bi ) );
    copy( vc.begin(), vc.end(), front_inserter( li ) );

    for( auto &c : i )
        cout << c << " ";
    cout << endl;

    for( auto &c : bi )
        cout << c << " ";
    cout << endl;
    
    for( auto &c : li )
        cout << c << " ";
    cout << endl;
}
