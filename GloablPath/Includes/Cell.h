#ifndef CELL_H
#define CELL_H

#include "common.h"

class Cell
{
public:
    Cell( int x = 5, int y = 5 ) : size( Cell_Size ), position_x( x ), position_y( y ), g( 0 ), h ( 0 ), f( 0 ), parent( nullptr ) { haveObstacle = false; }

public:
    std::pair<int, int> getPosition() const { return { position_x, position_y }; }
    void setObstacle( bool flag ) { haveObstacle = flag; }
    bool getObstacle() const { return haveObstacle; }

public:
    //operator overload for sort
    bool operator<( const Cell &rhs ) const { return f < rhs.f; }
    //void operator=( const Cell &rhs ) { position_x = rhs.getPosition().first; position_y = rhs.getPosition().second; g = rhs.g; h = rhs.h; f = rhs = f; }
    bool operator==( const Cell &rhs )  const { return position_x == rhs.getPosition().first && position_y == rhs.getPosition().second; }
    bool operator!=( const Cell &rhs )  const { return position_x != rhs.getPosition().first || position_y != rhs.getPosition().second; }

private:
    //general property
    unsigned size;
    int position_x, position_y;
    bool haveObstacle;

public:
    //properties for path finding
    Cell *parent;
    int g, h, f;
};

#endif
