#ifndef _MAP_H
#define _MAP_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "obstacle.h"

class map
{
public:
    map(int sz);
    void show();
    cv::Mat &getFrame();
    void setObstacle();

    void fillRect(int x, int y, int sz, CvScalar value);

private:
    int size;
    cv::Mat map_frame;

private:
    void drawWall();
};

#endif
