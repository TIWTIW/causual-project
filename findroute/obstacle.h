#ifndef _OBSTACLE_H
#define _OBSTACLE_H

#include "common.h"
#include <time.h>

class obstacle   //障碍物基类
{
public:
    obstacle();
    ~obstacle();
    int position_x, position_y, size;
    void initial(int, int, int);
};

/******派生类*******/
/******矩形********/
class myRect:public obstacle
{
public:
    myRect();
    ~myRect();
    int position_x, position_y, size;
    void setRect(cv::Mat, int, int, int size = 20);  //设定矩形位置
    void setRect(cv::Mat, int size = 20);           //随机生成矩形
};

/*****圆形*******/
class myCircle:public obstacle
{
public:
    myCircle();
    ~myCircle();
    int position_x, position_y, size;
    void setCircle(cv::Mat, int, int, int size = 20);  //设定圆形位置
    void setCircle(cv::Mat, int size = 20);           //随机生成圆形
};

/*****三角形*****/
class myTriangle:public obstacle
{
public:
    myTriangle();
    ~myTriangle();
    int position_x, position_y, size;
    void setTriangle(cv::Mat, int, int, int size = 20);  //设定圆形位置
    void setTriangle(cv::Mat, int size = 20);           //随机生成圆形
};

#endif
