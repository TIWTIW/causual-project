#include <iostream>
#include <vector>

using namespace std;

bool isInMatrix( vector<vector<int>> &matrix, int target )
{  
    int row = 0, col = matrix.size() - 1 ;

    while( true )
    {
        if( row >= matrix.size() || col <= -1 )
            return false;

        int temp = matrix[row][col];
        if( temp > target )
            col--;
        else if( temp < target )
            row++;
        else
            return true;
    }
}

int main()
{
    vector<vector<int>> array{ {1, 2, 3, 4}, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, {13, 14, 15, 16} };
    int target = 0;

    if( isInMatrix( array, target ) )
        cout << target << " is in matrix!" << endl;
    else
        cout << target << " isn't in matrix!" << endl;

    return 0;
}
