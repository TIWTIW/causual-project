#ifndef _TARGET_H
#define _TARGET_H

#include "common.h"

class target
{
public:
    target();
    ~target();
    void setTarget(int, int);
    int position_x, position_y;
};

#endif
