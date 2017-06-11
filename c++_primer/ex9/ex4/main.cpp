#include <iostream>
#include <vector>

using namespace std;

bool find( vector<int>::iterator &beg, vector<int>::iterator &end, int target )
{
    while( beg != end )
    {
        if( *beg++ == target )
            return true;
    }

    return false;
}

int main()
{
    vector<int> vc{1, 2, 3 ,4, 5};

    auto it = vc.begin(), ie = vc.end();
    int tar = 3;

    if( ::find( it, ie, tar ) )
        cout << "find" << endl;
    else
        cout << "not find" << endl;

    return 0;
}
