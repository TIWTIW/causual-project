#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template<typename It, typename type>
int find( const It &begin, const It &end, const type &val )
{
    for( It it = begin; it != end; ++it )
    {
        if( *it == val )
            return 1;
    }

    return -1;
}

int main( int argc, char *argv[] )
{
    vector<int> vc{ 1, 2, 3, 4 };
    list<string> ls{ "as", "ds" };

    if( find( vc.begin(), vc.end(), 2 ) >= 0 )
        cout << "find int" << endl;

    if( find( ls.begin(), ls.end(), "as" ) >= 0 )
    cout << "find string" << endl;

    return 0;

    
}
