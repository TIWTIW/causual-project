#include "SingleList.h"

using namespace std;

int main()
{
    SingleList<int> Sl;


    Sl.push_or_pop( 1 );

    Sl.push_or_pop( 2 );

    Sl.push_or_pop( -1 );
    Sl.print();
}
