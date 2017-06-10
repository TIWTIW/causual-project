#include "Person.h"

using namespace std;

istream &read( istream &is, Person &rhs )
{
    is >> rhs.name >> rhs.address;

    return is;
}

ostream &print( ostream &os, const Person &rhs )
{
    os << rhs.get_name() << " " << rhs.get_address();

    return os;
}
