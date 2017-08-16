#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> capcity;
    vector<int> desire;

    int size;
    int maxCap;

    cin >> size;
    cin >> maxCap;

    while( size-- != 0 )
    {
        int tmp;
        cin >> tmp;
        capcity.push_back( tmp );
        cin >> tmp;
        desire.push_back( tmp );
    }

    vector<int> maxSum( maxCap + 1 );

    maxSum[0] = 0;

    for( int i = 1; i <= capcity.size(); ++i )
    {
        for( int j = maxCap; j >= capcity[i - 1]; --j )
        {
                if( maxSum[j - capcity[i - 1]] + desire[i - 1] > maxSum[j] )
                    maxSum[j] = maxSum[j - capcity[i - 1]] + desire[i - 1];
            
        }
    }

   /* for( auto &vc : maxSum )
    {
        for( auto &i : vc )
            cout << i << " ";
        cout << endl;
    }*/

    cout << maxSum[maxCap] << endl;

    return 0;
}
