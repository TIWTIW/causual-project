#ifndef _CANVAS_H
#define _CANVAS_H

#include "common.h"

class canvas
{
friend class point;
public:
    canvas() = default;
    canvas(int ht, int wd, std::pair<int, int> pt) :
           height(ht), width(wd) , position(pt){ }
    void SetSP(int, int, int, int);
    int initial(cv::Mat&);
    void GetSP(int&, int&, std::pair<int, int>&);
    int clear(cv::Mat&);
    ~canvas() = default;
private:
    int height, width;
    std::pair<int, int> position;
};

#endif
