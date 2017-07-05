#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "Map.h"
#include <queue>
#include <set>
#include "ETree.h"

std::vector<std::vector<Cell>> CellVectorToMap( std::vector<Cell>& );
std::vector<Cell> A_Star_FindPath( std::vector<std::vector<Cell>>&, std::pair<int, int>, std::pair<int, int> );
void RRT_Find_Path( cv::Mat &, cv::Point, cv::Point );

#endif
