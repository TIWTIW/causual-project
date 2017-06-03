
#include "Myfunctions.h"

string time_stamp_str( void )
{
	time_t utc_time = time( NULL );
	struct tm *local_time = localtime( &utc_time );
	char str_time[127] = {0};
	strftime( str_time, sizeof(str_time), "%Y%m%d%H%M%S  ", local_time );
	string timestamp = str_time;
	return timestamp;
}
string time_filename_str( void )
{
	time_t utc_time = time( NULL );
	struct tm *local_time = localtime( &utc_time );
	char str_time[127] = {0};
	strftime( str_time, sizeof(str_time), "%Y%m%d_%H%M%S", local_time );
	string timestamp = str_time;
	return timestamp;
}

bool CreateDir( const char *dir_path )
{
	struct stat dirAttr;
	int res = stat( dir_path, &dirAttr );
	if( res < 0 )
	{
		if( errno == ENOENT )
		{
			if( mkdir( dir_path, 0755 ) < 0 )
			{
				return false;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	if( dirAttr.st_mode & S_IFDIR )
	{
		return true;
	}
	else
	{
		if( mkdir( dir_path, 0755 ) < 0 )
		{
			return false;
		}
		return true;
	}
}

int is_dir( const char *filename )
{
	struct stat fileAttr;
	if( stat( filename, &fileAttr )==0 )
	{
		if( fileAttr.st_mode & S_IFDIR )
			return 0; // folder
		else
			return 1; // file
	}
}

int DeleteDir( const char *dir_path )
{
	struct dirent *ptr;
	char buff[256];

	DIR *dir = NULL;
	dir = opendir( dir_path );
	if( dir==NULL )
		return -1;

	while( (ptr=readdir(dir)) != NULL )
	{
		if( strcmp( ptr->d_name, ".")==0 || strcmp( ptr->d_name, ".." )==0 )
			continue;
		snprintf( buff, 256, "%s/%s", dir_path, ptr->d_name );
		if( is_dir( buff ) )
		{
			if( DeleteDir( buff )!=0 )
				return -1;
		}
		else
		{
			if( remove( buff )!=0 )
				return -1;
		}
	}
	closedir( dir );
	if( remove(dir_path)!=0 )
		return -1;
	return 0;
}