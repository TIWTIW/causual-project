#include "Myfunctions.h"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	if( argc != 2 )
	{
		cout << "Usage: test_myfunctions <filepath>." << endl;
		return -1;
	}

	string path_str = argv[1];

	if( !CreateDir( path_str.c_str() ) )
	{
		perror( "Create directory failed: " );
		return -1;
	}

	DeleteDir( path_str.c_str() );

	return 0;
}