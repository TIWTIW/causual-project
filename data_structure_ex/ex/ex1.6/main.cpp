/*************************************
 * function:显示所有字符串可能的排列
 * notes:使用递归,将原来的const删除了
 * Name:zft
 * Time:2017.3.27
 * **********************************/

#include <iostream>
#include <string>

using namespace std;

void Swap( char & a, char & b )
{
    char tmp = b;
    b = a;
    a = tmp;
}

void permute( string & str, int low, int high )
{
    if( low == high )
    {
        cout << str << endl;
    }
    else
    {
        for( int i = low; i < high; ++i)
        {
            Swap( str[low], str[i] );
            permute( str, low + 1, high );
            Swap( str[low], str[i] );
        }
    }
}

void permute( string & str )
{
    permute( str, 0, str.size() );
}

int main( int argc, char *argv[] )
{
    string s{"abcd"};

    permute( s );

    return 0;
}
