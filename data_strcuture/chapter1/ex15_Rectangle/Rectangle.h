#ifndef _RECT_H
#define _RECT_H

#include <iostream>

class Rectangle
{
public:
    Rectangle( unsigned len = 0, unsigned wid = 0 ) : length( len ), width( wid ) {}
    unsigned getLength() { return length; }
    unsigned getWidth() { return width; }

private:
    unsigned length, width;
};

#endif
