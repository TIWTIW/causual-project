#include "stackTwo.h"

using namespace std;

int main()
{
    stackTwo<int> sti;

    sti.stackOnePush( 1 );
    sti.stackOnePush( 2 );

    sti.stackTwoPush( 4 );

    cout << sti.stackOnePop() << endl;
    cout << sti.stackTwoPop() << endl;
}
