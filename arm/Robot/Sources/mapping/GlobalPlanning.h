
#ifndef _GLOBAL_PLANNING_H_
#define _GLOBAL_PLANNING_H_

#include "mapping.h"

vector<Point> PathPlanning_CRT(  Point startPoint, Grid_Map_t *mapdata );
vector<Point> GetPath( Point startPoint, Point endPoint , Grid_Map_t *mapdata, float *GridValue[] );

vector<Point> PathSegmente( vector<Point> globalPath );
vector<pose_t> PathSegmentePose( vector<Point> globalPath, int map_grid_size );
vector<pose_t> PathSegmentePoseV2( vector<Point> globalPath, int map_grid_size );
#endif // _GLOBAL_PLANNING_H_