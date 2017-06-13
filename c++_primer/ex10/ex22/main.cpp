#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool smallerThanSix( const string &s )
{
    return s.size() < 6;
}

int main()
{
    vector<string> vs{"asffas", "as", "a", "asfasfggas", "dffafadf"};

    cout << count_if( vs.cbegin(), vs.cend(), smallerThanSix ) << endl;

}
