#include "sorting.h"
#include <iostream>

using namespace std;

int main()
{
    vector<int> a = {1, 3, 4, 5, 2, 6, 8, 7};

    //bubble_sort( a );
    //select_sort( a );
   // insert_sort( a );
    //merge_sort( a, 0, a.size() - 1 );
    //count_sort( a );
    quick_sort( a, 0, a.size() - 1 );
    for( auto & c : a )
     cout << c << " ";

    cout << endl;
}
