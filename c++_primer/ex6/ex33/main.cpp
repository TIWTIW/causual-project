#include <iostream>
#include <vector>

using namespace std;

void printVc( vector<int> &vc, vector<int>::size_type i )
{
    if( i < vc.size() - 1 )
        printVc( vc, i + 1 );

    cout << vc[i] << endl;
}

int main()
{
    vector<int> vc{1, 2, 3};

    printVc( vc, 0 );

    return 0;
}
