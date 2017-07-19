#include <iostream>
#include <vector>

using namespace std;

int minA( vector<int> &array )
{
    vector<int> maxNow, minNow;

    int max = array[0], min = array[array.size() - 1];
    for( int i = 0; i < array.size(); ++i )
    {
        if( array[i] > max )
            max = array[i];
        maxNow.push_back( max );
    }

    for( int i = array.size() - 1; i >= 0; --i )
    {
        if( array[i] < min )
            min = array[i];
        minNow.push_back( min );
    }

    int result = 0;
    for( int i = 0; i < maxNow.size(); ++i )
    {
        if( maxNow[i] - minNow[i] > result )
            result = maxNow[i] - minNow[i];
    }

    return result;

}

int main()
{
    vector<int> array{1, 2, 3, 4, 5, 6};

    int res = minA( array );

    cout << res << endl;
}
