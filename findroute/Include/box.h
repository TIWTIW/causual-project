#ifndef _BOX_H
#define _BOX_H

#include "common.h"

class box
{
public:
    /***construction function*************/
    box( int sz = BOX_SIZE, int x = 20, int y = 20 ) : size( sz ), position_x( x ), position_y( y ) { }
    ~box();

public:
    /**********some function**********/
    void setSize( int );
    void setPosition( int, int );
    void initial( cv::Mat& );
    void move( cv::Mat&, int, int );
    int getSize() { return size; }
    std::pair<int, int> getPosition() { return {position_x, position_y}; }


private:
    int size;
    int position_x,position_y;
};

#endif
