#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::size_type index;

int findMajorEle( vector<int> &arr, bool &flag , int &res )
{
    vector<int> temp;

    for( index i = 0; i < arr.size() - 1; i = i + 2 )
    {
        if( arr[i] == arr[i + 1] )
            temp.push_back( arr[i] );
    }

    if( temp.size() == 1 )
    {
        flag = true;
        res = temp[0];
        return 0;
    }

    if( temp.size() == 0 )
    {
        flag = false;
        return 1;
    }

    findMajorEle( temp, flag, res );
}

int main()
{
    vector<int> arr{3, 3, 4, 2, 4, 4, 2, 4, 1, 1, 1, 1};

    bool flag = false;
    int res = 0;

    findMajorEle( arr, flag, res );

    if( flag )
        cout << "The major element is " << res << endl;
    else
        cout << "There is no major element!" << endl;

    return 0;
}
