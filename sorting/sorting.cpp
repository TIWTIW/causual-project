#include "sorting.h"

using namespace std;

void swap( int &x, int &y )
{
    int temp = x;
    x = y;
    y = temp;

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
                swap( array[index_i], array[index_j] );
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
    int min = 0;

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

        swap( array[index_i], array[min] );
    }
    return 0;
}

int insert_sort( vector<int> &array )
{
    using index = vector<int>::size_type;
    index end = array.size();
    int j = 0;

    for( index i = 1; i < end; ++i )
    {
        int temp = array[i];
        for( j = i - 1; j >= 0; --j )
        {
            if( temp < array[j] )
            {
                array[j + 1] = array[j];
            }
            else
            {
                break;
            }
        }
        array[j + 1] = temp;

    }

    return 0;
}

int merge_sort( vector<int> &array, vector<int>::size_type start, vector<int>::size_type end )
{
    if( start == end )     
        return 0;

    //divide
    merge_sort( array, start, (start + end) / 2 );
    merge_sort( array, (start + end) / 2 + 1, end );

    //conquer
    vector<int> temp( end - start + 1, 0 );

    typedef vector<int>::size_type index;
    index x = 0;
    index i = start, j = (start + end) / 2 + 1;
    for( ; ( i <=  (start + end) / 2 ) && ( j <= end ); )
    {
        if( array[i] < array[j] )
        {
            temp[x++] = array[i++];
        }
        else
        {
            temp[x++] = array[j++];
        }
    }

    while( i <= (start + end) / 2 )
    {
        temp[x++] = array[i++];
    }

    while( j <= end )
    {
        temp[x++] = array[j++];
    }

    for( index i = start, j = 0; i <= end; ++i )
        array[i] = temp[j++];

    return 0;

}

int count_sort( vector<int> &array )
{
    typedef vector<int>::size_type index;

    vector<int> number( 9 );

    for( index i = 0; i < array.size(); ++i )
        number[array[i]]++;

    index j = 0;
    for( index i = 0; i < number.size(); ++i )
    {
        while( number[i]-- > 0 )
            array[j++] = i;
    }
    return 0;
}

int quick_sort( vector<int> &array, int start, int end )
{
    if( start >= end )
        return 0;

    int pivot = array[start];
    int i = start, j = end;

    while( i < j )
    {
        while( array[j] > pivot && i < j )
        {
            --j;
        }

        array[i] = array[j];

        while( array[i] < pivot && i < j  )
        {
            ++i;
        }
        array[j] = array[i];
    }
    array[i] = pivot;
    quick_sort( array, start, i - 1 );
    quick_sort( array, i + 1, end );

    return 0;
}
