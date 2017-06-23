#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class compareLength
{
public:
    compareLength( size_t small, size_t big ) : min( small ), max( big ) {}
    bool operator()( size_t x )  const { return x > min && x < max; }
private:
    size_t min, max;
};

int main()
{
    ifstream infile( "abc" );

    string s;
    int num_of_upten = 0;
    int total_num = 0;
    compareLength cp( 1, 9 );
    while( infile >> s )
    {
        if( cp( s.size() ) )
        {
            num_of_upten++;
        }
        total_num++;
    }

    int num_of_less = total_num - num_of_upten;

    cout << num_of_less << num_of_upten << endl;
}
