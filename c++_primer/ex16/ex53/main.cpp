#include <iostream>

using namespace std;

template <typename T>
ostream &print( ostream &os, const T &t )
{
    return os << t;
}

template <typename T, typename... Args>
ostream &print( ostream &os, const T &t, const Args&... rest )
{
    os << t << endl;
    return print( os, rest... );
}

int main()
{
    int i = 0;
    double x = 12.12;
    string ss = "asd";
    print( cout , i, x, ss );

}
