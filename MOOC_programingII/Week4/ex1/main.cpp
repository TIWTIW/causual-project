#include <iostream>
#include <vector>

using namespace std;

void findKth( vector<int> &array, int start, int end, int k )
{
    int num = array[start];
    while( start < end )
    {
        while( end > start && array[end] > num )
            end--;
        array[start] = array[end];
        while( end > start && array[start] < num )
            start++;
        array[end] = array[start];
    }

    array[start] = num;

    int size = array.size() - 1;
    if( start < k )
        findKth( array, start + 1, array.size() - 1, k - start - 1);
    else if( start > k )
        findKth( array, 0, start, k );
    else
        ;
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

    for( int i = 0; i < k; ++i )
        cout << array[i] << endl;

    return 0;

}
