#include <iostream>
#include <random>

using namespace std;

unsigned RandomNum( long seed = -1, long min = 1, long max = 0 )
{
    static default_random_engine e;

    if( seed > 0 )
        e.seed( seed );

    static uniform_int_distribution<unsigned> u(0, 9999);
    
    if( min <= max )
        u = uniform_int_distribution<unsigned>( min, max );

    return u( e );
}

int main()
{
    unsigned i;
    vector<unsigned> vu;

    RandomNum( 2000 );
    for( size_t j = 0; j < 10; ++j )
        vu.push_back( RandomNum() );

    for( auto &c : vu )
        cout << c << " ";

    cout << endl;


}
