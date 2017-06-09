#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int num;
    vector<int> vc;

    while( cin >> num )
    {
        vc.push_back( num );
    }

    for( auto &c : vc )
        cout << c << " ";

    cout << endl;
    return 0;
}
