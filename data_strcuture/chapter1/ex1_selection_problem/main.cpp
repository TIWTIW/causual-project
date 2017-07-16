#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::size_type index;

int partition( vector<int> &array, index start, index end )
{
    index i = start, j = end;
    int pivot = array[start];

    while( i < j )
    {
        while( array[j] > pivot && i < j )
        {
            j--;
        }

        array[i] = array[j];
        i++;

        while( array[i] < pivot && i < j )
        {
            i++;
        }

        array[j] = array[i];
        --j;
        
    }

    array[i] = pivot;

    return i;
}

int main()
{
    vector<int> vi = {10, 70, 21 ,20, 56, 13, 1, 90};
    index k = vi.size() / 2;

    int current = partition( vi, 0, vi.size() - 1 );
    while( true )
    {
        if( current > k )
        {
            current = partition( vi, 0, current - 1 );
        }
        else if( current < k )
        {
            current = partition( vi, current + 1, vi.size() - 1 );
        }
        else
            break;
    }

    cout << vi[current] << endl;
}
