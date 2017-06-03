#include "logmodule.hpp"

int main( void )
{
	log_t logger( "test_logmodule" );

	logger.fs( ORI ) << "This is a origin message!" << endl;
	logger.fs( INFO ) << "This is a INFO message!" << endl;
	logger.fs( WARNING ) << "This is a WARNING message!" << endl;
	logger.fs( ERROR ) << "This is a ERROR message!" << endl;
	logger.fs( FATAL ) << "This is a FATAL message!" << endl;

	return 0;
}