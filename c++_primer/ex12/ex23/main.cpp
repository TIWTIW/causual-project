#include <new>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    string s1( "a" );
    string s2( "b" );

    string s3 = s1 + s2;

    char *a = new char[s3.size()]();

    for( size_t i = 0; i < s3.size(); ++i )
    {
        a[i] = s3[i];
    }

    for( size_t i = 0; i < s3.size(); ++i )
    {
        cout << a[i] << " ";
    }

    delete [] a;
}
