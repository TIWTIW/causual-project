#include <iostream>
#include <vector>

using namespace std;

int minSum( vector<int> &array )
{
    int currentSum = 0;
    int min = array[0];

    for( auto &i : array )
    {
        if( i > 0 )
            currentSum = 0;
        else
            currentSum += i;

        if( currentSum < min )
            min = currentSum;
    }

    return min;
}

int maxThree( int i, int j, int k )
{
    int temp = max( i, j );
    temp = max( temp, k );
    return temp;
}

int minThree( int i, int j, int k )
{
    int temp = min( i, j );
    temp = min( temp, k );
    return temp;
}

int maxTime( vector<int> &array )
{
    int maxNow = array[0], minNow = array[0];
    int result = 0;

    for( int i = 1; i < array.size(); ++i )
    {
        maxNow = maxThree( array[i], maxNow * array[i], minNow * array[i] );
        minNow = minThree( array[i], maxNow * array[i], minNow * array[i] );
        if( maxNow > result )
            result = maxNow;
    }

    return result;
}

int main()
{
    vector<int> a{1, 2, -3, -1, 5, 8};

    cout << minSum( a ) << endl;
    cout << maxTime( a ) << endl;
}
