#include "sorting.h"

using namespace std;

void swap( int *x, int *y )
{
    int temp = *x;
    *x = *y;
    *y = temp;

}

int bubble_sort( vector<int> &array )
{
    vector<int>::size_type size = array.size();
    vector<int>::size_type index_i = 0;
    vector<int>::size_type index_j = array.size();

    for( index_i = 0; index_i <= size; ++index_i )
    {
        for( index_j = array.size(); index_j > index_i; --index_j )
        {
            if( array[index_i] > array[index_j] )
            {
                swap( &array[index_i], &array[index_j] );
            }
        }
    }

    return 0;
}

int select_sort( vector<int> &array )
{
    
    vector<int>::size_type size = array.size();
    vector<int>::size_type index_i = 0;
    vector<int>::size_type index_j = 0;
    int min = INT_MAX;


    for( index_i = 0; index_i < size; ++index_i )
    {
        min = index_i;
        for( index_j = index_i; index_j < size; ++index_j )
        {
            if( array[index_j] <= array[min] )
            {
                min = index_j;
            }
        }

        swap( &array[index_i], &array[min] );
    }
}
