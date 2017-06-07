#include <vector>
#include <iostream>

using namespace std;

template<typename T>
void printT( T &V )
{
    for( typename T::size_type i = 0; i < V.size(); ++i )
    {
        cout << V[i] << " ";
    }
}

int main( int argc, char *argv[] )
{
    vector<int> vc{1, 2, 3, 4};

    printT( vc );

    cout << endl;

    return 0;
}
