#include <iostream>
#include <initializer_list>

using namespace std;

int sum( initializer_list<int> intList )
{
    int x = 0;

    for( const auto &i : intList )
        x += i;

    return x;
}

int main()
{
    cout << sum( {1, 2, 3, 4} ) << endl;

    return 0;
}
