#include "common.h"
#include "obstacle.h"
#include "box.h"
#include "target.h"
#include "func.h"

using namespace cv;
using namespace std;

int main(void)
{
    Mat Image = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
    box box;     //实例物体
    target target;   //实例目标
   // myCircle circle;
//    myRect rect;
   // myTriangle triangle;

    initial(box, target);  //初始化物体大小与位置，初始化目标点位置
    
    obstacleInitial(Image, 3);
//    rect.setRect(Image, 300, 300, 20);

   // circle.setCircle(Image);

   // triangle.setTriangle(Image);

    box.initial(Image);   //初始显现

    imshow(WINDOW_NAME, Image);

    int err_x, err_y;
    calRoute(box, target, err_x, err_y);  //计算移动路径
    moveToTarget(Image, box, err_x, err_y);  //实现移动
    
    waitKey(0);
    return(0);
}
