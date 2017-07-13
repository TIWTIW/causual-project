#include "record.h"

using namespace std;

int main()
{
    bitset<8> bc( 0x12 );

    record<8> A1( 0x12 );

    cout << A1.score( bc ) << endl;
}
