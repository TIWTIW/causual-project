#include <iostream>

using namespace std;

int main()
{
    int a[10] = {2};

    for( size_t i = 0; i < 9; ++i )
        a[i] = 0;

    for( auto &c : a )
        cout << c << " ";

    cout << endl;

    return 0;
}
