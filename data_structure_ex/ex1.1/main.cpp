#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int SelectionSolution(vector<int> Array, int k)
{
    vector<int> array_tmp;
    for(int i=0; i<k; ++i)
    {
        array_tmp.push_back(Array[i]);
    }

    sort(array_tmp.begin(), array_tmp.end());

    for(vector<int>::size_type i=k; i<Array.size(); ++i)
    {
        if(Array[i] <= array_tmp[k-1])
        {
            array_tmp[k-1] = Array[i];
        }
    }

    return array_tmp[k-1];
}

int main()
{
    vector<int> num{7,2,5,4,3,6};

    int result = SelectionSolution(num, 3);

    cout << result << endl;
    return 0;
}
