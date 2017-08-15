#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition( vector<int> &array, int start, int end, int k )
{
    int num = array[start];
    int i = start, j = end;
    while( i < j ) 
    {
        while( j > i && array[j] < num )
            j--;
        array[i] = array[j];
        while( j > i && array[i] > num )
            i++;
        array[j] = array[i];
    }

    array[i] = num;

    return i - start;
}

void findKth( vector<int> &array, int start, int end, int k )
{
    if( k > end - start + 1 )
        return;
    int n = partition( array, start, end, k );

    if( n == k || n == k - 1 )
        return;

    if( n < k - 1 )
        findKth( array, start + n + 1, end, k - n - 1);
    else if( n > k )
        findKth( array, start, start + n - 1, k );
}

int main()
{
    int size;
    vector<int> array;
    int k;

    cin >> size;
    int tmp = size;
    while( tmp-- != 0 )
    {
        int num_tmp;
        cin >> num_tmp;
        array.push_back( num_tmp );
    }

    cin >> k;

    findKth( array, 0, array.size() - 1, k );

    sort( array.begin(), array.begin() + k, greater<int>() );

    for( int i = 0; i < k; ++i )
        cout << array[i] << endl;

    return 0;

}
