#ifndef _MappingModule_H_
#define _MappingModule_H_

/* This head file is a collection of all the map module  */
// You can import map module through include this file in you project

#include "grid_map_core.h"
#include "grid_map_coordinate.h"
#include "GlobalPlanning.h"

struct CameraMapModel_t
{
    vector<Point> OcpGrid;
    vector<Point> FreeGrid;
};

#endif // _MappingModule_H_