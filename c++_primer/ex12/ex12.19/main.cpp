/**********使用StrBlob类******
 * function:读入文件，用StrBlobPtr打印
 * Name:zft
 * Time:2017.3.30
 * ***************************/

#include "StrBlob.h"
#include <fstream>

int main( int argc, char *argv[] )
{
    ifstream input( argv[1] );
    StrBlob SB;

    string s_File;
    while( getline( input, s_File ) )
        SB.push_back( s_File );

    StrBlobPtr SBP( SB );
    size_t i = SB.size();
    while( i-- > 0 )
    {
        string result = SBP.deref();
        cout << result << endl;
        SBP.incr();
    }

    return 0;

}
