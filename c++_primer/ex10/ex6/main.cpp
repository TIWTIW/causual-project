#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vc{1, 2, 3, 4};

    fill_n( vc.begin(), vc.size(), 0 );

    for( auto &i : vc ) 
    {
        cout << i << " ";
    }

    cout << endl;

    return 0;
}
