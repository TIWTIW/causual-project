#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

/********打印出L中由P指定的元素******/
int printLots( const vector<int> L, const vector<int> P )
{
    if( *(P.end()-1 ) > L.size() )
    {
        cout << "error:out of range" << endl;
        return -1;
    }

    for ( auto &c : P )
        cout << L[ c ] << " ";
    return 0;

}

int main()
{
    clock_t start = clock();

    vector<int> list1{1,2,3,4,5,6,7,8,9}, list2{2,4,6,7};

    printLots( list1, list2 );

    clock_t ends = clock();
    cout << "Running time:" << (double)(ends - start) / CLOCKS_PER_SEC  <<endl;

    return 0;
}
