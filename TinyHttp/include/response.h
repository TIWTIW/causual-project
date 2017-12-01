#ifndef _RESPONSE_H
#define _RESPONSE_H

#include "common_include.h"

namespace myServer
{:
class response
{
//constructor & des
public:
    response() : responseBuf( NULL ) {}
    response( char *buf ) : responseBuf( buf );
    ~response();

//function
public:


//private ptr
private:
    std::shared_ptr<char> responseBuf;
}
}

#endif
