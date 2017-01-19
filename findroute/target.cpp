#include "target.h"

using namespace std;

target::target()
{
    cout << "target初始化" << endl;
}

target::~target()
{
    ;
}

void target::setTarget(int x, int y)
{
    this->position_x = x;
    this->position_y = y;
}
