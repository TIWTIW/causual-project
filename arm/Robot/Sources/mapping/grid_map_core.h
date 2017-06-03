#ifndef _GRID_MAP_CORE_H_
#define _GRID_MAP_CORE_H_

#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define Map_Default_GridSize 40 // 默认栅格大小，单位mm
#define Map_Default_SizeX 500   // 默认地图X轴向大小
#define Map_Default_SizeY 500   // 默认地图Y轴向大小
#define Map_Index_OffsetX (Map_Default_SizeX/2) // 默认地图坐标和存储索引偏移量--X
#define Map_Index_OffsetY (Map_Default_SizeY/2) // 默认地图坐标和存储索引偏移量--Y

#define CellUnknown 127
#define CellUpCovered 255
#define CellDrop 0

class Grid_Map_Cell_t
{
public:
    Grid_Map_Cell_t();
    Grid_Map_Cell_t(unsigned char ocpstat, unsigned int scancnt=0);
    ~Grid_Map_Cell_t();
    unsigned int m_scan_cnt;
    unsigned char m_ocp_stat;
};
ostream&  operator << ( ostream&  os, const Grid_Map_Cell_t &t );
ofstream& operator << ( ofstream& os, const Grid_Map_Cell_t &t );


struct Map_Attr_t
{
    unsigned int map_sizeX;
    unsigned int map_sizeY; 
    unsigned int map_grid_size; // Unit: mm
    unsigned int index_offsetX;
    unsigned int index_offsetY;
    float global_X_direction; // Used for Compass
};
ostream&  operator << ( ostream&  os, const Map_Attr_t &t );
ofstream& operator << ( ofstream& os, const Map_Attr_t &t );

class Grid_Map_t
{
private:
    void Init( void );
    void UnInit( void );
public:
    Grid_Map_t();
    Grid_Map_t(unsigned int SizeX, unsigned int SizeY);

    // Add at 2017-03-01 by limin
    Grid_Map_t( const Grid_Map_t *srcMapData );
    Grid_Map_t( Mat mapImage );
    Grid_Map_t( string directory, string mapName );

    ~Grid_Map_t();

    void SetAttr( Map_Attr_t newAttr );
    Map_Attr_t GetAttr( void ) const;

    // Add at 2017-03-01 by limin
    bool IsInside( Point t );
    bool IsUnknown( Point t );
    bool IsOcp( Point t );
    bool IsReachable( Point t );
    bool IsUpCovered( Point t );
    bool IsDrop( Point t );
    bool IsUnScan( Point t );

    bool IsInside( int index_x, int index_y );
    bool IsUnknown( int index_x, int index_y );
    bool IsOcp( int index_x, int index_y );
    bool IsReachable( int index_x, int index_y );
    bool IsUpCovered( int index_x, int index_y );
    bool IsDrop( int index_x, int index_y );
    bool IsUnScan( int index_x, int index_y );

    // Deleted at 2017-03-01 by limin
    /*
    bool UpdateCell( int index_x, int index_y, Grid_Map_Cell_t newCellData );
    Grid_Map_Cell_t GetCell( int index_x, int index_y );
    */

    // Add at 2017-03-01 by limin
    unsigned char GetGridOcpStat( Point t );
    unsigned char GetGridOcpStat( int x, int y );
    void SetGridOcpStat( Point t, unsigned char newStat );
    void SetGridOcpStat( int x, int y, unsigned char newStat );

    // Add at 2017-03-01 by limin
    unsigned int GetGridCntStat( Point t );
    unsigned int GetGridCntStat( int x, int y );
    void SetGridCntStat( Point t, unsigned int newCnt );
    void SetGridCntStat( int x, int y, unsigned int newCnt );


    bool UpdateLocalMap( int x, int y, Grid_Map_t *localMap );

    void fill_all( unsigned char ocp_stat=CellUnknown+100 );
    void fill_circle( Point center, int Radius, unsigned char ocp_stat, int flag=0 );
    void fill_rect( Point center, int len_x, int len_y, unsigned char ocp_stat, int flag=0 );
    
    // Add at 2017-03-01 by limin
    void fill( vector<Point> p, unsigned char newStat, unsigned int newCnt );

    void dilate( Grid_Map_t *dstGridMap );

    // Modified at 2017-03-22 By Limin: add sub-directory path
    void Save( string directory, string mapName );
    void Load( string directory, string mapName );

    // Add at 2017-04-07 by Limin
    void copyto( Grid_Map_t &mapSnap );
    Grid_Map_t clone(void);

public:
    Grid_Map_Cell_t **ptr;
private:
    Map_Attr_t m_mapattr;
};
ostream&  operator << ( ostream&  os, Grid_Map_t &t );
ofstream& operator << ( ofstream& os, Grid_Map_t &t );

#endif // _GRID_MAP_CORE_H_
