
#ifndef _grid_map_coordinate_H_
#define _grid_map_coordinate_H_

#include "grid_map_core.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// The angle unit in math function of C/C++ is radian system
// while angle used in our project is system of degree measure
// so we should transfer the degree to radian before we use math library
// to handle our degree, eg: sin(), cos(), atan() etc.
#define _180_D_PI 57.296       // degree = radian * 180/PI
#define degree2radian 0.01745  // radian = degree * Pi/180

/************************************************************************/
// --*Type definitions*--
// if pose_t has been defined in COM_UART_USERTYPES_H_
// then it should not be defined here to avoid type definition conflict
#ifndef COM_UART_USERTYPES_H_ 
typedef struct pose_t
{
	float x;
	float y;
	float theta;
} location_t;
#endif

double round(double val);

/************************************************************************/
// --*Start*--: Old interfaces, not recommend to use
Point  pose2grid( pose_t pose, Map_Attr_t mapAttr );
Point  Phy_to_Grid( Point phy, Map_Attr_t mapAttr );
Point  Map_Global_to_Local(Point global, location_t pose);
Point  Map_Local_to_Global(Point local,  location_t pose);
// --*END*--: Old interfaces, not recommend to use
/************************************************************************/

/************************************************************************/
// --*Start*--: New interfaces, Recommended!
//////////////////////////////////////////////////////////////////////////
// Theoretical Equations
// Robot Pose--(x, y, theta)
// Location in Robot Coordinate -- (xR, yR )
// Location in Global Coordinate -- (xI, yI )
//     1. Physical location to Grid location
//        gx = (int)( px-gridSize/2 )/gridSize. 
//		  gy = (int)( py-gridSize/2 )/gridSize.
//	      eg: if gridSize=40, (15,15)-->(0,0), (-35, 35)-->(-1, 1), (40,40)-->(1, 1)
//	   2. Local location to global location
//        xI = xR*cos(theta) - yR*sin(theta);
//        yI = xR*sin(theta) + yR*cos(theta);
//     3. Global location to local location
//        xR = xI*cos(theta) + yI*sin(theta);
//        yR = -xI*sin(theta) + yI*cos(theta);
//////////////////////////////////////////////////////////////////////////
// toGrid() : transfer physical location to grid location
Point toGrid( pose_t pose, int map_grid_size );
Point toGrid( Point P_phy, int map_grid_size );
Point toPhy( Point P_grid, int map_grid_size );
// PhyLocaltoMapIndex(): transfer physical location in Robot Coordinate to grid location in global grid map
Point GridLocaltoMapIndex( Point local, location_t pose, int map_grid_size );
// PhyLocaltoMapIndex(): transfer grid location in Robot Coordinate to grid location in global grid map
Point PhyLocaltoMapIndex( Point local, location_t pose, int map_grid_size );
// --*END*--: New interfaces, Recommended!
/************************************************************************/
#endif // _grid_map_coordinate_H_
