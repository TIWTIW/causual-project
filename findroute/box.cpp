#include "box.h"

using namespace cv;
using namespace std;

box::box()
{
    cout << "物体初始化" << endl;
}

void box::setSize(int r)
{
    size = r;  //设定物体大小
}

void box::setPosition(int x, int y)
{
    position_x = x; //设定物体位置
    position_y = y;
}

void box::initial(Mat Image)
{
    //初始化显示物体
    circle(Image, Point(position_x, position_y), size, Scalar(255, 255, 0));

}

void box::move(Mat Image, int x, int y)  //实现物体的移动
{
     //首先取消之前的物体显示
     circle(Image, Point(position_x, position_y), size, Scalar(0, 0, 0));
     
     position_x += x;
     position_y += y;

     circle(Image, Point(position_x, position_y), size, Scalar(255, 255, 0));
}

box::~box()
{
    ;
}
