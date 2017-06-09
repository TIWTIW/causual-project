#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int num;
    vector<int> vc;

    while( cin >> num )
        vc.push_back( num );

    for( decltype( vc.size() ) i = 0; i != vc.size(); i = i + 2 )
        cout << vc[i] + vc[i+1] << endl;

    return 0;
}

