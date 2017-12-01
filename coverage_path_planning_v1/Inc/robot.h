#ifndef _ROBOT_H
#define _ROBOT_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "map.h"

class robot
{
public:
    robot(int x, int y, int sz) : px(x), py(y), window_size(sz)
    { cleanDirection = right;upDirection = up;}

    void move(map &);

private:
    enum directionLeftOrRight
    {
        left = 0,
        right = 1,
    };
    enum directionUpOrDown
    {
        up = 0,
        down = 1,
    };

    int px;
    int py;
    int window_size;
    directionLeftOrRight cleanDirection;
    directionUpOrDown upDirection;

private:
    bool noObstacle(map &data);
    void localPlanning();

};

#endif
