
#include "grid_map_coordinate.h"

double round(double val)
{
    return (val> 0.0) ? floor(val+ 0.5) : ceil(val- 0.5);
}

/************************************************************************/
// --*Start*--: Old interfaces, not recommend to use
Point pose2grid( pose_t pose, Map_Attr_t mapAttr )
{
	Point gridPose;
    int gridSize = mapAttr.map_grid_size;

	gridPose.x = (int)( pose.x/gridSize );
	gridPose.y = (int)( pose.y/gridSize );
	return gridPose;
}
Point  Phy_to_Grid( Point phy, Map_Attr_t mapAttr )
{
    Point gridPose;
    int gridSize = mapAttr.map_grid_size;

    gridPose.x = (int)( phy.x/gridSize );
    gridPose.y = (int)( phy.y/gridSize );

    //cout << "Phy to Grid" << gridPose << "-->" << gridPose << endl;
    return gridPose;
}
Point Map_Global_to_Local( Point global, location_t pose )
{
    // translate the physical global location to local location
    Point local;
    // Translation Transformation
    float tmpx = global.x - pose.x;
    float tmpy = global.y - pose.y;
    // Rotation Transformation
    local.x = tmpx * cos(pose.theta/_180_D_PI) + tmpy * sin(pose.theta/_180_D_PI);
    local.y = -tmpx * sin(pose.theta/_180_D_PI) + tmpy * sin(pose.theta/_180_D_PI);
    return local;
}
Point Map_Local_to_Global( Point local,  location_t pose )
{
    // translate the physical local location to global location
    Point global;
    global.x = local.x * cos(pose.theta/_180_D_PI) - local.y * sin(pose.theta/_180_D_PI) + pose.x;
    global.y = local.x * sin(pose.theta/_180_D_PI) + local.y * cos(pose.theta/_180_D_PI) + pose.y;
    return global;
}
// --*END*--: Old interfaces, not recommend to use
/************************************************************************/
Point toGrid( pose_t pose, int map_grid_size )
{
// This function is used to get the Robot location in grid map according the Robot Pose
    int offset = map_grid_size/2;
    int gx = int( ( pose.x - offset )/map_grid_size );
    int gy = int( ( pose.y - offset )/map_grid_size );
    return Point(gx, gy);
}
Point toGrid( Point P_phy, int map_grid_size )
{
// This function is used to get the grid location according to physical location
    int offset = map_grid_size/2;
    int gx = int( ( P_phy.x - offset )/map_grid_size );
    int gy = int( ( P_phy.y - offset )/map_grid_size );
    return Point(gx, gy);
}
Point toPhy( Point P_grid, int map_grid_size )
{
// This function is used to get physical location according to the grid location 
    int offset = map_grid_size/2;
    float gx = P_grid.x * map_grid_size + offset;
    float gy = P_grid.y * map_grid_size + offset;
    return Point(gx, gy);

}
Point PhyLocaltoMapIndex( Point local, location_t pose, int map_grid_size )
{
// This function is used to get the location in grid map according the physical location in Robot Coordinate and Robot Pose
    Point gridGlobal;
    Point girdLocal = toGrid( local, map_grid_size );
    Point gridPose = toGrid( pose, map_grid_size );
    //cout << "gridPose = " << gridPose << endl;
    //cout << "girdLocal = " << girdLocal << endl;
    float theta = pose.theta * degree2radian;
    float x = girdLocal.x*cos(theta) - girdLocal.y*sin(theta) + gridPose.x;
    float y = girdLocal.x*sin(theta) + girdLocal.y*cos(theta) + gridPose.y;
    //cout << x <<", " << y << endl;
    gridGlobal.x = x>0? ceil(x) : floor(x);
    gridGlobal.y = y>0? ceil(y) : floor(y);
    //cout << gridGlobal << endl;
    gridGlobal.x = abs(gridGlobal.x - x) < 0.5? gridGlobal.x : int(x);
    gridGlobal.y = abs(gridGlobal.y - y) < 0.5? gridGlobal.y : int(y);
    //cout << gridGlobal << endl;
    return gridGlobal;
}
Point GridLocaltoMapIndex( Point girdLocal, location_t pose, int map_grid_size )
{
// This function is used to get the location in grid map according the grid location in Robot Coordinate and Robot Pose
    Point gridGlobal;
    Point gridPose = toGrid( pose, map_grid_size );
    //cout << "gridPose = " << gridPose << endl;
    //cout << "girdLocal = " << girdLocal << endl;
    float theta = pose.theta * degree2radian;
    float x = girdLocal.x*cos(theta) - girdLocal.y*sin(theta) + gridPose.x;
    float y = girdLocal.x*sin(theta) + girdLocal.y*cos(theta) + gridPose.y;
    //cout << x <<", " << y << endl;
    gridGlobal.x = x>0? ceil(x) : floor(x);
    gridGlobal.y = y>0? ceil(y) : floor(y);
    //cout << gridGlobal << endl;
    gridGlobal.x = abs(gridGlobal.x - x) < 0.5? gridGlobal.x : int(x);
    gridGlobal.y = abs(gridGlobal.y - y) < 0.5? gridGlobal.y : int(y);
    //cout << gridGlobal << endl;
    return gridGlobal;
}
