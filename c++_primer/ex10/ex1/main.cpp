#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> vc{1, 2, 3, 4, 5, 2, 3, 4, 1};

    int target = 2;

    cout << count( vc.begin(), vc.end(), target ) << endl;

    return 0;
}
