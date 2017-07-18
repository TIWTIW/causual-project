#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int target;

    cout << "input search number:";
    cin >> target;

    cout << endl;

    int low = 0, high = a.size() - 1;
    int mid = 0;
    bool flag = false;

    while( low <= high )
    {
        mid = ( low + high ) >> 1;
        if( a[mid] == target )
        {
            flag = true;
            break;
        }
        else if( a[mid] > target )
            high = mid - 1;
        else
            low = mid + 1;
    }

    if( flag )
        cout << "find!" << endl;
    else
        cout << "not find!" << endl;
}
