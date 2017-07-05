#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include "common.h"
#include <time.h>

class obstacle   //障碍物基类
{
public:
    obstacle();
    ~obstacle();

public:
    void initial(int, int, int);

private:
    int position_x, position_y, size;
};

/******派生类*******/
/******矩形********/
class myRect:public obstacle
{
public:
    void setRect(cv::Mat&, int, int, int size = 20);  //设定矩形位置
    void setRect(cv::Mat&, int size = 20);           //随机生成矩形
};

/*****圆形*******/
class myCircle:public obstacle
{
public:
    void setCircle(cv::Mat&, int, int, int size = 20);  //设定圆形位置
    void setCircle(cv::Mat&, int size = 20);           //随机生成圆形
};

/*****三角形*****/
class myTriangle:public obstacle
{
public:
    void setTriangle(cv::Mat&, int, int, int size = 20);  //设定圆形位置
    void setTriangle(cv::Mat&, int size = 20);           //随机生成圆形
};

#endif
