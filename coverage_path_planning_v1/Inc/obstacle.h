#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define RECTANGLE 0
#define CIRCLE 1
#define TRIANGLE 2

class obstacle   //障碍物基类
{
public:
    obstacle();
    virtual ~obstacle();

public:
    void initial(int, int, int);
    virtual void setObstacle(cv::Mat &, int) = 0;

protected:
    int shape;
    int position_x, position_y, size;
};

/******派生类*******/
/******矩形********/
class myRect:public obstacle
{
public:
    myRect();
    void setRect(cv::Mat&, int, int, int size = 20);  //设定矩形位置
    virtual void setObstacle(cv::Mat &, int);
};

/*****圆形*******/
class myCircle:public obstacle
{
public:
    myCircle();
    void setCircle(cv::Mat&, int, int, int size = 20);  //设定圆形位置
    virtual void setObstacle(cv::Mat &, int);
};

/*****三角形*****/
class myTriangle:public obstacle
{
public:
    myTriangle();
    void setTriangle(cv::Mat&, int, int, int size = 20);  //设定圆形位置
    virtual void setObstacle(cv::Mat &, int);
};

#endif
