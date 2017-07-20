#include "selfAdjustList.h"

using namespace std;

int main()
{
    SelfAdjustList<int> sal;

    sal.insert( 1 );
    sal.insert( 2 );

    sal.print();
    sal.find( 1 );
    sal.print();
}
