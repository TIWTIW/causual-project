
#ifndef _LogModule_HPP_
#define _LogModule_HPP_

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

enum log_level_t{ORI, INFO, WARNING, ERROR, FATAL};

using namespace std;

string _timestamp( void );

class log_t
{
public:
	log_t();
	log_t( string filename, string modulename=_timestamp() );
	~log_t();
private:
	ofstream m_cout;
public:

	ofstream& fs( log_level_t messagelevel );
};

#endif // _LogModule_HPP_