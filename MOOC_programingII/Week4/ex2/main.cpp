/*****求排列的逆序数*********/

#include <iostream>
#include <vector>

using namespace std;

long long result;
vector<int> array_temp;

void mergeAndCount( vector<int> &array, int left, int right )
{
    int center = ( left + right ) / 2;

    if( center > left )
    {
        mergeAndCount( array, left, center );
        mergeAndCount( array, center + 1, right );
    }

    int i = left, j = center + 1;
    while( i <= center && j <= right )
    {
        if( array[i] > array[j] )
        {
            result += ( center - i + 1 );
            j++;
        }
        else
        {
            ++i;
        }
    }


    array_temp.clear();
    i = left;
    j = center + 1;
    while( i <= center && j <= right )
    {
        if( array[i] < array[j] )
        {
            array_temp.push_back( array[i] );
            ++i;
        }
        else if( array[i] > array[j] )
        {
            array_temp.push_back( array[j] );
            ++j;
        }  
    }

    while( i <= center )
        array_temp.push_back( array[i++] );
    while( j <= right )
        array_temp.push_back( array[j++] );

    for( int i = left; i <= right; ++i )
        array[i] = array_temp[i - left];
}

int main()
{
    vector<int> array;
    int size;

    cin >> size;
    while( size-- != 0 )
    {
        int tmp;
        cin >> tmp;
        array.push_back( tmp );
    }

    mergeAndCount( array, 0, array.size() - 1 );

    cout << result << endl;
}
