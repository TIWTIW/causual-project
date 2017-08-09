#ifndef _SHOW_H
#define _SHOW_H

#include <cstdio>

typedef unsigned char *byte_pointer;

void show_bytes( byte_pointer, int );
void show_int( int );
void show_float( float );
void show_pointer( void * );
void show_short( short );
void show_long( long );
void show_double( double );

#endif
