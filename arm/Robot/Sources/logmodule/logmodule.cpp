
#include "logmodule.hpp"

log_t::log_t()
{
	time_t utc_time = time( NULL );
	struct tm *local_time = localtime( &utc_time );
	char str_time[127] = {0};
	strftime( str_time, sizeof(str_time), "%Y%m%d--%H%M%S", local_time );
	string filename = str_time;

	if ( m_cout.is_open() )
	{
		m_cout.close();
	}
	m_cout.open( filename + ".log", ofstream::app );
	if ( !m_cout )
	{
		cout << "Error: Module log_t failed to open the file--" << filename+".log"
		     << ". Please check the permission Access!" << endl;
	}

	m_cout << "\n*************************************************"
		   << "\n      This is the log file of the Robot          "
		   << "\n*************************************************"
	       << endl;
}
log_t::log_t( string filename, string modulename )
{
	time_t utc_time = time( NULL );
	struct tm *local_time = localtime( &utc_time );
	char str_time[127] = {0};
	strftime( str_time, sizeof(str_time), "%Y%m%d--%H%M%S", local_time );
	string timestamp = str_time;

	if ( m_cout.is_open() )
	{
		m_cout.close();
	}
	m_cout.open( filename  + ".log", ofstream::app );
	if ( !m_cout )
	{
		cout << "Error: Module log_t failed to open the file--" << filename+".log"
		     << ". Please check the permission Access!" << endl;
	}

	time_t t = time(NULL);
	m_cout << "log file information :"
		   << "\n\t Title: " << filename
		   << "\n\t Recorder: " << modulename
		   << "\n\t Logging start Time: " << ctime( &t )
		   << endl;
}

log_t::~log_t()
{
	time_t t = time(NULL);
	m_cout << "\n\t Logging stop time: " << ctime( &t ) << endl;
	m_cout.close();
}

string _timestamp( void )
{
	time_t utc_time = time( NULL );
	struct tm *local_time = localtime( &utc_time );
	char str_time[127] = {0};
	strftime( str_time, sizeof(str_time), "%Y%m%d%H%M%S ", local_time );
	string timestamp = str_time;

	return timestamp;
}

ofstream& log_t::fs( log_level_t messagelevel )
{
	switch( messagelevel )
	{
		case INFO:
			m_cout << "Info    -" << _timestamp();
			break;
		case WARNING:
			m_cout << "Warning -" << _timestamp();
			break;
		case ERROR:
			m_cout << "Error   -" << _timestamp();
			break;
		case FATAL:
			m_cout << "Fatal   -" << _timestamp();
			break;
		case ORI:
			break;
	}
	return m_cout;
}
