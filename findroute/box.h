#ifndef _BOX_H
#define _BOX_H

#include "common.h"

class box
{
public:
    box();
    ~box();
    void setSize(int);
    void setPosition(int, int);
    void initial(cv::Mat);
    void move(cv::Mat, int, int);
    int size,position_x,position_y;
};

#endif
