#include "Snake.h"

using namespace std;
using namespace cv;

Snake::Snake()
{
    size = 3;
    state = "right";
    int x = 100, y = 100;
    while(size-- > 0)
    {
        point point(5);
        point.SetPosition(x, y);
        x = x + 5;
        ObSnake.push_back(point);
    }
}

int Snake::SnakeInitial(Mat &Image)
{
    for(auto &s : ObSnake)
    {
        auto x = s.GetPT().first, y = s.GetPT().second;
        auto sz = s.GetSZ();
        rectangle(Image, Point(x,y), Point(x+sz,y+sz), 
                   Scalar(255,0,0), -1);
    }

    return 0;
}

int Snake::SetState(const string &s)
{
    state = s;

    return 0;
}

int Snake::SAdd(point pt)
{
    ++size;
    ObSnake.push_back(pt);

    return 0;
}

pair<int, int> Snake::GetPosition()
{
    auto ie = ObSnake.end();
    return (*(--ie)).GetPT();    
}

void Snake::Move(Mat &Image)
{
    if(state == "right")
    {
        point point(5);
        auto it = ObSnake.begin(), ie = ObSnake.end();
        auto begin = *it, end = *(--ie);
        auto endx = end.GetPT().first, endy = end.GetPT().second;
        auto beginx = begin.GetPT().first, beginy = begin.GetPT().second;
        auto sz = point.GetSZ();
        point.SetPosition(endx + sz, endy);
        ObSnake.erase(it);
        ObSnake.push_back(point);
        rectangle(Image, Point(endx,endy), Point(endx+sz,endy+sz), 
                   Scalar(255,0,0), -1);
        rectangle(Image, Point(beginx,beginy), Point(beginx+sz,beginy+sz), 
                   Scalar(0,0,0), -1);
 
    }
    if(state == "up")
    {
        point point(5);
        auto it = ObSnake.begin(), ie = ObSnake.end();
        auto begin = *it, end = *(--ie);
        auto endx = end.GetPT().first, endy = end.GetPT().second;
        auto beginx = begin.GetPT().first, beginy = begin.GetPT().second;
        auto sz = point.GetSZ();
        point.SetPosition(endx, endy-sz);
        ObSnake.erase(it);
        ObSnake.push_back(point);
        rectangle(Image, Point(beginx,beginy), Point(beginx+sz,beginy+sz), 
                   Scalar(0,0,0), -1);
        rectangle(Image, Point(endx,endy-sz), Point(endx+sz,endy), 
                   Scalar(255,0,0), -1);
 
    }
    if(state == "left")
    {
        point point(5);
        auto it = ObSnake.begin(), ie = ObSnake.end();
        auto begin = *it, end = *(--ie);
        auto endx = end.GetPT().first, endy = end.GetPT().second;
        auto beginx = begin.GetPT().first, beginy = begin.GetPT().second;
        auto sz = point.GetSZ();
        point.SetPosition(endx-sz, endy);
        ObSnake.erase(it);
        ObSnake.push_back(point);
        rectangle(Image, Point(endx-sz,endy), Point(endx,endy+sz), 
                   Scalar(255,0,0), -1);
        rectangle(Image, Point(beginx,beginy), Point(beginx+sz,beginy+sz), 
                   Scalar(0,0,0), -1);
 
    }
    if(state == "down")
    {
        point point(5);
        auto it = ObSnake.begin(), ie = ObSnake.end();
        auto begin = *it, end = *(--ie);
        auto endx = end.GetPT().first, endy = end.GetPT().second;
        auto beginx = begin.GetPT().first, beginy = begin.GetPT().second;
        auto sz = point.GetSZ();
        point.SetPosition(endx, endy+sz);
        ObSnake.erase(it);
        ObSnake.push_back(point);
        rectangle(Image, Point(endx,endy+sz), Point(endx+sz,endy+2*sz), 
                   Scalar(255,0,0), -1);
        rectangle(Image, Point(beginx,beginy), Point(beginx+sz,beginy+sz), 
                   Scalar(0,0,0), -1);
 
    }
}

