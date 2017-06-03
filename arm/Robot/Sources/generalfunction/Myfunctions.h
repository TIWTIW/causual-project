
#ifndef _Myfunction_H_
#define _Myfunction_H_

#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <stdio.h>

using namespace std;
int is_dir( const char *filename );
bool CreateDir( const char *dir_path );
int DeleteDir( const char *dir_path );

string time_stamp_str( void );
string time_filename_str( void );
#endif // _Myfunction_H_
