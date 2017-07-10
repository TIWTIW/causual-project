#include "sorting.h"
#include <iostream>

using namespace std;

int main()
{
    vector<int> a = {1, 3, 4, 5, 2, 4, 3};

    //bubble_sort( a );
    select_sort( a );

    for( auto & c : a )
     cout << c << " ";

    cout << endl;
}
