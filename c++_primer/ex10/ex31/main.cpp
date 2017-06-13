#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

int main()
{
    istream_iterator<int> it( cin ), eof;
    vector<int> vi( it, eof );

    sort( vi.begin(), vi.end() );

    ostream_iterator<int> ot( cout );

    unique_copy( vi.begin(), vi.end(), ot );
}

