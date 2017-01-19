#ifndef _SNAKE_H
#define _SNAKE_H

#include "common.h"
#include "point.h"

class Snake
{
public:
    Snake();
    int SnakeInitial(cv::Mat&);
    void Move(cv::Mat&);
    int SetState(const std::string&);
    std::pair<int, int> GetPosition();
    int SAdd(point);
    ~Snake() = default;
private:
    int size;
    std::vector<point> ObSnake;
    std::string state;
};

#endif
