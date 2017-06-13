#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    vector<int> vc{1, 2, 3, 4};

    cout << accumulate( vc.cbegin(), vc.cend(), 0 ) << endl;

    return 0;
}
