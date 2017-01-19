#include "func.h"

using namespace cv;
using namespace std;

/******障碍物初始化*****/
void obstacleInitial(Mat Image, int num)
{
    myRect rect;
    myCircle circle;
    myTriangle triangle;
    
    srand(unsigned(time(NULL)));
    int random;

    while(num > 0)
    {
        random = rand() % 3;
        if(random == 0)
        {
            rect.setRect(Image);
            cout << "rect:" << " " << rect.position_x << endl;
        }

        if(random == 1)
        {
            circle.setCircle(Image);
            cout << "circle!" << endl;
        }

        if(random == 2)
        {
            triangle.setTriangle(Image);
            cout << "triangle!" << endl;
        }

        --num;
    }
}

/*****物体初始化*****/
void initial(box &box, target &target) //初始化物体
{
    int size, init_x, init_y, tar_x, tar_y;

    cout << "输入物体大小:";
    if(cin >> size)
    {
        cout << size << endl;
    }
    box.setSize(size);

    cout << "输入物体位置:";
    if(cin >> init_x >> init_y)
    {
        cout << "x:" << init_x << " " << "y:" << init_y << endl;
    }
    box.setPosition(init_x, init_y);

    cout << endl;
    cout  << "输入目标位置:";
    if(cin >> tar_x >> tar_y)
    {
        cout << "x:" << tar_x << " " << "y:" << tar_y << endl;
    }
    target.setTarget(tar_x, tar_y);
}

/*****计算路径*****/
void calRoute(box box, target target,int &err_x, int &err_y)
{
    //计算物体需要移动的路径
    err_x = box.position_x - target.position_x;
    err_y = box.position_y - target.position_y;

    cout << "需要移动的x与y为" << err_x << " " << err_y << endl;
    cout << "calcute success!" << endl;
}

/*****实现物体的移动*******/
void moveToTarget(Mat Image, box box, int &err_x, int &err_y)
{
    //实现物体的移动
    while(err_x != 0)
    {
        if(err_x < 0)
        {
            box.move(Image, 1, 0);
            ++err_x;
            imshow(WINDOW_NAME, Image);
            waitKey(10);
        }
        else
        {
            box.move(Image , -1, 0);
            --err_x;
            imshow(WINDOW_NAME, Image);
            waitKey(10);
        }
    }

    while(err_y != 0)
    {
        if(err_y < 0)
        {
            box.move(Image, 0, 1);
            ++err_y;
            imshow(WINDOW_NAME, Image);
            waitKey(10);
        }
        else
        {
            box.move(Image , 0, -1);
            --err_y;
            imshow(WINDOW_NAME, Image);
            waitKey(10);
        }
    }

    cout << "move success!" << endl;
}
