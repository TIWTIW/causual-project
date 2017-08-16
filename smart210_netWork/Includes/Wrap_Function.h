#ifndef _WRAP_FUNC
#define _WRAP_FUNC

#include <unistd.h>
#include <errno.h>

//wrap function of read
//return number of bytes read
ssize_t readn( int fd, void *vptr, size_t n );

//wrap function of write
//return number of bytes written
ssize_t writen( int fd, const void *vptr, size_t n );


#endif
