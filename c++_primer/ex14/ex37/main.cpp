#include <iostream>
#include <algorithm>

using namespace std;

class Equal
{
public:
    Equal( int i = 0 ) : val( i ) {}
    bool operator()( int i1 ) { return i1 == val; }
private:
    int val;
};

int main()
{
    vector<int> a{1, 2, 3, 3, 4, 3, 3, 3};

    Equal e(3);
    replace_if( a.begin(), a.end(), e, 5 );

    for( auto &c : a )
        cout << c << " ";

    cout << endl;
}
