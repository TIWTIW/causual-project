#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void printT( T &c )
{
    for( typename T::iterator it = c.begin(); it != c.end(); ++it )
        cout << *it << " ";
}

int main( int argc, char *argv[] )
{
    vector<int> vi{1, 2, 3, 4};

    printT( vi );

    cout << endl;

    return 0;
}
