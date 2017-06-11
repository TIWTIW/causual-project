#include <iostream>
#include <string>

using namespace std;

void addSome( string &name, const string &forward, const string &back )
{
    name.insert( 0, forward );
    name.insert( name.size(), back );
}

int main()
{
    string name( "zft" );
    string f( "Mr." );
    string b( "II" );

    addSome( name, f, b );

    cout << name << endl;

    return 0;
}
