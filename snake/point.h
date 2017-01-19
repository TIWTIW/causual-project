#ifndef _POINT_H
#define _POINT_H

#include "canvas.h"
#include "common.h"
#include <time.h>
#include <cstdlib>

class point
{
public:
    point() = default;
    point(unsigned int sz) : size(sz) { }
    std::pair<int, int> GetPT();
    unsigned int GetSZ();
    int RandomPosition(cv::Mat&, canvas&);
    int SetPosition(int, int);
    ~point() = default;
private:
    std::pair<int, int> pposition;
    unsigned int size;

};

#endif
