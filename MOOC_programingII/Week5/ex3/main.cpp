/**********拦截导弹************/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int MaxStop( vector<int> &array )
{
    vector<int> maxSum( array.size() );

    maxSum[0] = 1;
    for( int i = 1; i < array.size(); ++i )
    {
        int max = 0;
        for( int j = 0; j < i; ++j )
        {
            if( array[i] <= array[j] && max <= maxSum[j] )
                max = maxSum[j];
        }
        maxSum[i] = max + 1;
        
    }

    int result = 0;
    for( auto &c : maxSum )
    {
        if( c > result )
            result = c;
    }

    return result;
}

int main()
{
    int size;
    cin >> size;
    vector<int> array;

    while( size-- != 0 )
    {
        int tmp;
        cin >> tmp;
        array.push_back( tmp );
    }

    cout << MaxStop( array ) << endl;
}
