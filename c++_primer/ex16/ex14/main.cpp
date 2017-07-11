#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "Screen.h"

int main()
{
    Screen<5, 3> myScreen;
    myScreen.display( cout );
    myScreen.move( 4, 0 ).set( '#' );

    Screen<5, 5> nextScreen( 'X' );
    nextScreen.move( 4, 0 ).set( '#' ).display( cout );
    cout << "\n";
    nextScreen.display( cout );
    cout << endl;

    const Screen<5, 3> blank;
    myScreen.set( '#' ).display( cout );
    cout << endl;
    blank.display( cout );
    cout << endl;

    myScreen.clear( 'Z' ).display( cout );
    cout << endl;
    myScreen.move( 4, 0 );
    myScreen.set( '#' );
    myScreen.display( cout );
    cout << endl;
    myScreen.clear( 'Z' ).display( cout );
    cout << endl;

    Screen<5, 3> temp = myScreen.move( 4, 0 );
    temp.set( '#' );
    myScreen.display( cout );
    cout << endl;

    return 0;
}
