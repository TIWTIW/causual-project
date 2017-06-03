
#include "grid_map_core.h"
/************************************************************************/
// Grid map cell class--Grid_Map_Cell_t definition
Grid_Map_Cell_t::Grid_Map_Cell_t()
{
    m_ocp_stat = CellUnknown;
    m_scan_cnt = 0;
}
Grid_Map_Cell_t::Grid_Map_Cell_t(unsigned char ocpstat, unsigned int scancnt)
{
    m_ocp_stat = ocpstat;
    m_scan_cnt = scancnt;
}

Grid_Map_Cell_t::~Grid_Map_Cell_t()
{}

ostream&  operator << ( ostream&  os, const Grid_Map_Cell_t &t )
{
    os << "[" << (unsigned int)t.m_ocp_stat << "," << t.m_scan_cnt << "]";
    return os;
}
ofstream& operator << ( ofstream& os, const Grid_Map_Cell_t &t )
{
    os << "[" << (unsigned int)t.m_ocp_stat << "," << t.m_scan_cnt << "]";
    return os;
}
// The End of Grid_Map_Cell_t class definition
/************************************************************************/
ostream&  operator << ( ostream&  os, const Map_Attr_t &t )
{
    os << "Map Attribution: "
       << "\n  Map Size: " << t.map_sizeX << " x " << t.map_sizeY << " ."
       << "\n  Grid Cell Size: " << t.map_grid_size << "mm/grid."
       << "\n  Map Index Offset X--Y: " << t.index_offsetX << "--" << t.index_offsetY
       << "\n  Global X Direction: " << t.global_X_direction;
    return os;
}
ofstream& operator << ( ofstream& os, const Map_Attr_t &t )
{
    os << "Map Attribution: "
       << "\n  Map Size: " << t.map_sizeX << " x " << t.map_sizeY << " ."
       << "\n  Grid Cell Size: " << t.map_grid_size << "cm/grid."
       << "\n  Map Index Offset X--Y: " << t.index_offsetX << "--" << t.index_offsetY
       << "\n  Global X Direction: " << t.global_X_direction;
    return os;
}


/************************************************************************/
// Grid map class--Grid_Map_t definition
Grid_Map_t::Grid_Map_t()
{
    // map attribution initialization
    m_mapattr.map_sizeX = Map_Default_SizeX;
    m_mapattr.map_sizeY = Map_Default_SizeY;
    m_mapattr.map_grid_size = Map_Default_GridSize;
    m_mapattr.index_offsetX = m_mapattr.map_sizeX/2;
    m_mapattr.index_offsetY = m_mapattr.map_sizeY/2;
    m_mapattr.global_X_direction = 0.0;
    // map data initialization
    Init();
}

Grid_Map_t::Grid_Map_t(unsigned int SizeX, unsigned int SizeY)
{
    m_mapattr.map_sizeX = SizeX;
    m_mapattr.map_sizeY = SizeY;
    m_mapattr.map_grid_size = Map_Default_GridSize;
    m_mapattr.index_offsetX = m_mapattr.map_sizeX/2;
    m_mapattr.index_offsetY = m_mapattr.map_sizeY/2;
    m_mapattr.global_X_direction = 0.0;
    // map data initialization
    Init();
}

// Add at 2017-03-01 By limin
Grid_Map_t::Grid_Map_t( const Grid_Map_t *srcMapData )
{
    m_mapattr = srcMapData->GetAttr();
    Init();
    for( unsigned int i = 0; i < m_mapattr.map_sizeX; i++ )
    {
        for( unsigned int j = 0; j < m_mapattr.map_sizeY; j++ )
        {
            ptr[i][j] = srcMapData->ptr[i][j];
        }
    }
}

// Add at 2017-03-01 By limin
Grid_Map_t::Grid_Map_t( Mat mapImage )
{
    m_mapattr.map_sizeX = mapImage.rows;
    m_mapattr.map_sizeY = mapImage.cols;
    m_mapattr.map_grid_size = Map_Default_GridSize;
    m_mapattr.index_offsetX = m_mapattr.map_sizeX/2;
    m_mapattr.index_offsetY = m_mapattr.map_sizeY/2;
    m_mapattr.global_X_direction = 0.0;
    Init();
    for( unsigned int i = 0; i < m_mapattr.map_sizeX; i++ )
    {
        for( unsigned int j = 0; j < m_mapattr.map_sizeY; j++ )
        {
            unsigned char imval = mapImage.at<uchar>(i,j);
            if( imval<=CellUnknown-50 )
            {
                ptr[i][j].m_ocp_stat = CellUnknown-100;
            }
            else if( imval>CellUnknown-50 && imval<CellUnknown+50 )
            {
                ptr[i][j].m_ocp_stat = CellUnknown ;
            }
            else
            {
                ptr[i][j].m_ocp_stat = CellUnknown+100;
            }
            ptr[i][j].m_scan_cnt = 0; // New map! all scan count is zero!
        }
    }
}
// Add at 2017-03-01 By limin
Grid_Map_t::Grid_Map_t( string directory, string mapName )
{
    m_mapattr.map_sizeX = Map_Default_SizeX;
    m_mapattr.map_sizeY = Map_Default_SizeY;
    m_mapattr.map_grid_size = Map_Default_GridSize;
    m_mapattr.index_offsetX = m_mapattr.map_sizeX/2;
    m_mapattr.index_offsetY = m_mapattr.map_sizeY/2;
    m_mapattr.global_X_direction = 0.0;
    // map data initialization
    Init();
    Load( directory, mapName ); // Load the nameMapImg
}

// Test Passed! By limin
Grid_Map_t::~Grid_Map_t()
{    
    //cout << "Destructing..."  << endl;
    UnInit();
}

// Test Passed! By limin
void Grid_Map_t::Init( void )
{
    ptr = new Grid_Map_Cell_t*[m_mapattr.map_sizeX];
    for (unsigned int i = 0; i < m_mapattr.map_sizeX; ++i)
    {
        ptr[i] = new Grid_Map_Cell_t[ m_mapattr.map_sizeY ];
    }
}

// Test Passed! By limin
void Grid_Map_t::UnInit( void )
{
    for (unsigned int i = 0; i < m_mapattr.map_sizeX; ++i)
    {
        delete [] ptr[i];
    }
    delete [] ptr;
}

// Test Passed! By limin
void Grid_Map_t::SetAttr( Map_Attr_t newAttr )
{
    // Step-1: Free the Old Map Memory
    UnInit();
    cout << "Resetting Map Attribute..." << endl;
    // Step-2: Reset the New Map Attribute
    m_mapattr = newAttr;
    // Step-3: Create New Map Memory
    Init();
}

// Test Passed! By limin
Map_Attr_t Grid_Map_t::GetAttr( void ) const
{
    return m_mapattr;
}

// Add at 2017-03-01 By limin
bool Grid_Map_t::IsInside( Point t )
{
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return ( t.x>=0 && t.y>=0 && t.x<m_mapattr.map_sizeX && t.y<m_mapattr.map_sizeY );
}
// Add at 2017-03-01 By limin
bool Grid_Map_t::IsUnknown( Point t )
{
    if( !IsInside( t ) )
    {
        return false;
    }
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return (ptr[t.x][t.y].m_ocp_stat == CellUnknown) ;
    // Error Way: ptr[t.x][t.y] index out of range may happen!
    //return IsInside(t) && ptr[t.x][t.y].m_ocp_stat == CellUnknown;
}
// Add at 2017-03-01 By limin
bool Grid_Map_t::IsOcp( Point t )
{
    if( !IsInside( t ) )
    {
        return false;
    }
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    //cout << t <<"Is Occupied Test!" << endl;
    //cout<< (ptr[t.x][t.y].m_ocp_stat < CellUnknown)<<endl;
    return (ptr[t.x][t.y].m_ocp_stat < CellUnknown) ;
}
// Add at 2017-03-01 By limin
bool Grid_Map_t::IsReachable( Point t )
{
    if( !IsInside( t ) )
    {
        return false;
    }
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return (ptr[t.x][t.y].m_ocp_stat > CellUnknown) ;
}
// Add at 2017-03-01 By limin
bool Grid_Map_t::IsUpCovered( Point t )
{
    if( !IsInside( t ) )
    {
        return false;
    }
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return ( ptr[t.x][t.y].m_ocp_stat == CellUpCovered ) ;
}
// Add at 2017-03-01 By limin
bool Grid_Map_t::IsDrop( Point t )
{
    if( !IsInside( t ) )
    {
        return false;
    }
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return ( ptr[t.x][t.y].m_ocp_stat == CellDrop ) ;
}
// Add at 2017-03-01 By limin
bool Grid_Map_t::IsUnScan( Point t )
{
    if( !IsInside( t ) )
    {
        return false;
    }
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return ( ptr[t.x][t.y].m_scan_cnt == 0 );
}
// Modified at 2017-03-01 by limin
bool Grid_Map_t::IsInside(int x, int y)
{
    x += m_mapattr.index_offsetX;
    y += m_mapattr.index_offsetY;
    return ( x>=0 && y>=0 && x<m_mapattr.map_sizeX && y<m_mapattr.map_sizeY );
}
// Modified at 2017-03-01 by limin
bool Grid_Map_t::IsUnknown( int index_x, int index_y )
{
    if( !IsInside(index_x, index_y) )
        return false;
    index_x += m_mapattr.index_offsetX;
    index_y += m_mapattr.index_offsetY;
    return ptr[index_x][index_y].m_ocp_stat == CellUnknown ;
}
// Modified at 2017-03-01 by limin
bool Grid_Map_t::IsReachable( int index_x, int index_y )
{
    if( !IsInside(index_x, index_y) )
        return false;
    index_x += m_mapattr.index_offsetX;
    index_y += m_mapattr.index_offsetY;
    return ptr[index_x][index_y].m_ocp_stat > CellUnknown ;
}
// Modified at 2017-03-01 by limin
bool Grid_Map_t::IsUpCovered( int index_x, int index_y )
{
    if( !IsInside(index_x, index_y) )
        return false;
    index_x += m_mapattr.index_offsetX;
    index_y += m_mapattr.index_offsetY;
    return ptr[index_x][index_y].m_ocp_stat == CellUpCovered ;
}
// Modified at 2017-03-01 by limin
bool Grid_Map_t::IsDrop( int index_x, int index_y )
{
    if( !IsInside(index_x, index_y) )
        return false;
    index_x += m_mapattr.index_offsetX;
    index_y += m_mapattr.index_offsetY;
    return ptr[index_x][index_y].m_ocp_stat = CellDrop ;
}
// Modified at 2017-03-01 by limin
bool Grid_Map_t::IsUnScan( int index_x, int index_y )
{
    if( !IsInside(index_x, index_y) )
        return false;
    index_x += m_mapattr.index_offsetX;
    index_y += m_mapattr.index_offsetY;
    return ptr[index_x][index_y].m_scan_cnt == 0 ;
}
// Add at 2017-03-01 by limin
unsigned char Grid_Map_t::GetGridOcpStat( Point t )
{
    // Please ensure the Point t is inside the map range
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return ptr[t.x][t.y].m_ocp_stat;
}
// Add at 2017-03-01 by limin
unsigned char Grid_Map_t::GetGridOcpStat( int x, int y )
{
    // Please ensure the Point(x, y) is inside the map range
    x += m_mapattr.index_offsetX;
    y += m_mapattr.index_offsetY;
    return ptr[x][y].m_ocp_stat;
}
// Add at 2017-03-01 by limin
void Grid_Map_t::SetGridOcpStat( Point t, unsigned char newStat )
{
    if( !IsInside(t) )
        return;
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    ptr[t.x][t.y].m_ocp_stat = newStat;
}
// Add at 2017-03-01 by limin
void Grid_Map_t::SetGridOcpStat( int x, int y, unsigned char newStat )
{
    if( !IsInside(x, y) )
        return;
    x += m_mapattr.index_offsetX;
    y += m_mapattr.index_offsetY;
    ptr[x][y].m_ocp_stat = newStat;
}
// Add at 2017-03-01 by limin
unsigned int Grid_Map_t::GetGridCntStat( Point t )
{
    // Please ensure the Point(x, y) is inside the map range
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    return ptr[t.x][t.y].m_scan_cnt;
}
// Add at 2017-03-01 by limin
unsigned int Grid_Map_t::GetGridCntStat( int x, int y )
{
    // Please ensure the Point(x, y) is inside the map range
    x += m_mapattr.index_offsetX;
    y += m_mapattr.index_offsetY;
    return ptr[x][y].m_scan_cnt;
}
// Add at 2017-03-01 by limin
void Grid_Map_t::SetGridCntStat( Point t, unsigned int newCnt )
{
    if( !IsInside( t ) )
        return;
    t.x += m_mapattr.index_offsetX;
    t.y += m_mapattr.index_offsetY;
    ptr[t.x][t.y].m_ocp_stat = newCnt;
}
// Add at 2017-03-01 by limin
void Grid_Map_t::SetGridCntStat( int x, int y, unsigned int newCnt )
{
    if( !IsInside(x, y) )
        return;
    x += m_mapattr.index_offsetX;
    y += m_mapattr.index_offsetY;
    ptr[x][y].m_ocp_stat = newCnt;
}
// Deleted at 2017-03-01 by limin
/*
Grid_Map_Cell_t Grid_Map_t::GetCell( int index_x, int index_y )
{
    int IndexX = index_x + m_mapattr.index_offsetX;
    int IndexY = index_y + m_mapattr.index_offsetY;
    if ( IndexX < 0 || IndexX>=m_mapattr.map_sizeX ||
         IndexY < 0 || IndexY>=m_mapattr.map_sizeY )
    {
        cout << "Failed to Get the map cell: The Index is out of the map range, please check the index!" << endl;
        Grid_Map_Cell_t temp;
        return temp; // This way is not good, but how to do?
    }
    return ptr[IndexX][IndexY];
}
bool Grid_Map_t::UpdateCell( int index_x, int index_y, Grid_Map_Cell_t newCellData )
{
    int IndexX = index_x + m_mapattr.index_offsetX;
    int IndexY = index_y + m_mapattr.index_offsetY;
    if ( IndexX < 0 || IndexX>=m_mapattr.map_sizeX ||
         IndexY < 0 || IndexY>=m_mapattr.map_sizeY )
    {
        cout << index_x << ", " << index_y << " Failed to Update the map cell: The Index is out of the map range, please check the index!" << endl;
        return false;
    }
    ptr[IndexX][IndexY] = newCellData;
    return true;
}
*/

bool Grid_Map_t::UpdateLocalMap( int x, int y, Grid_Map_t *localmap )
{
    Map_Attr_t localmapattr = localmap->GetAttr();
    int IndexX = x-localmapattr.index_offsetX + m_mapattr.index_offsetX;
    int IndexY = y-localmapattr.index_offsetY + m_mapattr.index_offsetY;
    //cout << "Updating Local Map..." << endl;
    //cout << localmapattr << endl;
    if ( IndexX < 0 || IndexX+localmapattr.map_sizeX>=m_mapattr.map_sizeX ||
         IndexY < 0 || IndexY+localmapattr.map_sizeY>=m_mapattr.map_sizeY )
    {
        cout << "Failed to Update the map cell: The Index is out of the map range, please check the index!" << endl;
        return false;
    }

    for (int i = 0; i < localmapattr.map_sizeX; ++i)
    {
        for (int j=0; j<localmapattr.map_sizeY; j++)
        {
            //cout << i*localmapattr.map_sizeY+j << endl;
            ptr[ IndexX+i ][ IndexY+j ] = localmap->ptr[i][j] ;
        }
    }

    return true;
}

// Delete at 2017-03-01 by limin
/*
void Grid_Map_t::fill_all( Grid_Map_Cell_t newCellData )
{
    for (int i = 0; i < m_mapattr.map_sizeX; i++)
    {
        for (int j=0; j<m_mapattr.map_sizeY; j++)
        {
            ptr[i][j] = newCellData;
        }
    }
}*/
void Grid_Map_t::fill_all( unsigned char ocp_stat )
{
    for (int i = 0; i < m_mapattr.map_sizeX; i++)
    {
        for (int j = 0; j < m_mapattr.map_sizeY; j++)
        {
            ptr[i][j].m_ocp_stat = ocp_stat;
        }
    }
}

// Repair the point index error at 2017-03-01 by limin
void Grid_Map_t::fill_circle( Point center, int Radius, unsigned char ocp_stat, int flag )
{
    // description
    if( !IsInside(center) )
    {
        cout << "Center Not inside!" << endl;
        return;
    }
    //cout << "filling circle..." << center << "-->" << Radius << endl;

    for (int i = -Radius; i <= Radius; ++i)
    {
        for (int j = -Radius; j <= Radius; ++j)
        {
            if( IsInside( Point(center.x+i, center.y+j) ) )
            {
                if( i*i+j*j <= Radius*Radius )
                {
                    int location_x, location_y;
                    location_x = center.x + i + m_mapattr.index_offsetX;
                    location_y = center.y + j + m_mapattr.index_offsetY;
                    ptr[location_x][location_y].m_ocp_stat =  ocp_stat;
                    //cout << Point(location_x, location_y) << "=" << (int)ptr[location_x][location_y].m_ocp_stat << endl;
                    if( flag==0 )
                        continue;
                    if( ptr[location_x][location_y].m_scan_cnt==255 )
                    {
                        ptr[location_x][location_y].m_scan_cnt = 255;
                    }
                    else
                    {
                        ptr[location_x][location_y].m_scan_cnt ++;
                    }
                } // In the circle range
            } // Inside the map index
        }
    } // Fill the circle
}
// Repair the point index error at 2017-03-01 by limin
void Grid_Map_t::fill_rect( Point center, int len_x, int len_y, unsigned char ocp_stat, int flag )
{
    if( !IsInside(center) )
        return;

    for( int i = -len_x/2; i <= len_x/2; i++ )
    {
        for( int j = -len_y/2; j <= len_y/2; j++ )
        {
            if( IsInside( Point(center.x+i, center.y+j) ) )
            {
                int location_x, location_y;
                location_x = center.x + i + m_mapattr.index_offsetX;
                location_y = center.y + j + m_mapattr.index_offsetY;
                ptr[location_x][location_y].m_ocp_stat =  ocp_stat;
                if( flag==0 )
                    continue;
                if( ptr[location_x][location_y].m_scan_cnt==255 )
                {
                    ptr[location_x][location_y].m_scan_cnt = 255;
                }
                else
                {
                    ptr[location_x][location_y].m_scan_cnt ++;
                }
            }
        }
    }
}

// Add at 2017-03-01 by limin
void Grid_Map_t::fill( vector<Point> p, unsigned char newStat, unsigned int newCnt )
{
    vector<Point>::iterator iter;
    if( p.empty() )
        return ;
    for( iter = p.begin(); iter != p.end(); iter++ )
    {
        if( IsInside( *iter ) )
        {
            int location_x, location_y;
            location_x = iter->x + m_mapattr.index_offsetX;
            location_y = iter->y + m_mapattr.index_offsetY;
            ptr[location_x][location_y].m_ocp_stat = newStat;
            ptr[location_x][location_y].m_scan_cnt = newCnt;
        }
    }
}

// Modified by limin @ 2017-03-02: save both occupied map and scan count map
void Grid_Map_t::Save( string directory, string mapName )
{
    string OcpMap = directory + "/ocpMap"+mapName + ".jpg";
    string CntMap = directory + "/cntMap"+mapName + ".jpg";
    cout << "Saving image " << OcpMap << "..." << endl;
    Mat ocpMap( m_mapattr.map_sizeX, m_mapattr.map_sizeY, CV_8UC1, Scalar::all(CellUnknown) );
    Mat cntMap( m_mapattr.map_sizeX, m_mapattr.map_sizeY, CV_8UC1, Scalar::all(0) );
    for (int i = 0; i < m_mapattr.map_sizeX; i++)
    {
        for (int j=0; j<m_mapattr.map_sizeY; j++)
        {
            ocpMap.at<uchar>(i,j) = ptr[i][j].m_ocp_stat;
            cntMap.at<uchar>(i,j) = ptr[i][j].m_scan_cnt;
        }
    }
    imwrite( OcpMap, ocpMap );
    imwrite( CntMap, cntMap );
}
// Modified by limin @ 2017-03-02: load both occupied map and scan count map
void Grid_Map_t::Load( string directory, string mapName )
{
    string OcpMap = directory + "/ocpMap"+mapName + ".jpg";
    string CntMap = directory + "/cntMap"+mapName + ".jpg";
    cout << "Loading image " << mapName << "..." << endl;
    Mat ocpMap = imread( OcpMap, 0 );
    Mat cntMap = imread( CntMap, 0 );
    if ( !ocpMap.data )
    {
        cout << "Failed to Load the image: " << mapName << endl;
        return ;
    }
    bool flagNoCntMap = false;
    if( !cntMap.data )
    {
        cout << "No scan count map!" << endl;
        flagNoCntMap = true;
    }
    // Free the Old Map Memory
    UnInit();
    m_mapattr.map_sizeX = ocpMap.rows;
    m_mapattr.map_sizeY = ocpMap.cols;
    m_mapattr.index_offsetX = m_mapattr.map_sizeX/2;
    m_mapattr.index_offsetY = m_mapattr.map_sizeY/2;
    Init();
    for( unsigned int i = 0; i < m_mapattr.map_sizeX; i++ )
    {
        for( unsigned int j = 0; j < m_mapattr.map_sizeY; j++ )
        {
            ptr[i][j].m_scan_cnt = flagNoCntMap ? 0 : cntMap.at<uchar>(i, j);

            if( ocpMap.at<uchar>(i,j) > CellUnknown-50 && ocpMap.at<uchar>(i,j) < CellUnknown+50 )
            {
                ptr[i][j].m_ocp_stat = CellUnknown;
            }
            else
            {
                ptr[i][j].m_ocp_stat = ocpMap.at<uchar>(i,j);
            }
        }
    }
}

// Add by limin @2017-03-02 : Test Passed!
void Grid_Map_t::dilate( Grid_Map_t *dstGridMap )
{
    cout << "Dilating the map..." << endl;
    for(unsigned int i = 0; i < m_mapattr.map_sizeX; i++ )
    {
        for( unsigned int j =0; j < m_mapattr.map_sizeY; j++ )
        {
            //cout<<Point(i,j)<<endl;
            if( ptr[i][j].m_ocp_stat < CellUnknown )
            {
                dstGridMap->fill_circle( Point( i-m_mapattr.index_offsetX, j-m_mapattr.index_offsetY), 3, ptr[i][j].m_ocp_stat );
            }
        }
    }
}

// Add by limin @ 2017-04-07 : Test Pass!
void Grid_Map_t::copyto( Grid_Map_t &mapSnap )
{
    mapSnap.SetAttr( m_mapattr );
    for( unsigned int i = 0; i < m_mapattr.map_sizeX; i++ )
    {
        for( unsigned int j = 0; j < m_mapattr.map_sizeY; j++ )
        {
            mapSnap.ptr[i][j] = ptr[i][j];
        }
    }
}
// Add by limin @ 2017-04-07 : Test Pass!
Grid_Map_t Grid_Map_t::clone(void)
{
    return Grid_Map_t( this );
}


ostream&  operator << ( ostream&  os, Grid_Map_t &t )
{
    const Map_Attr_t mapattr= t.GetAttr();
    os << mapattr;
    os << "Map Data Element = \n" ;
    for (unsigned int i = 0; i < mapattr.map_sizeX; i++)
    {
        for (unsigned int j=0; j< mapattr.map_sizeY; j++)
        {
            //os << (unsigned short)t.ptr[i][j].m_ocp_stat << ", ";
            if( t.ptr[i][j].m_ocp_stat> CellUnknown )
            {
                //os << (int)t.ptr[i][j].m_ocp_stat;
                os << " ";
            }
            else if( t.ptr[i][j].m_ocp_stat == CellUnknown )
            {
                //os << (int)t.ptr[i][j].m_ocp_stat<<"\t";
                os << "U";
            }
            else
            {
                //os << (int)t.ptr[i][j].m_ocp_stat<<"\t";
                os << "*";
            }
        }
        os << ";" << endl;
    }
    return os;
}

ofstream& operator << ( ofstream& os, Grid_Map_t &t )
{
    const Map_Attr_t mapattr= t.GetAttr();
    os << mapattr;
    os << "Map Data Element = \n" ;
    for (unsigned int i = 0; i < mapattr.map_sizeX; i++)
    {
        for (unsigned int j=0; j< mapattr.map_sizeY; j++)
        {
            //os << (unsigned short)t.ptr[i][j].m_ocp_stat << ", ";
            if( t.ptr[i][j].m_ocp_stat< CellUnknown )
            {
                os << " ";
            }
            else if( t.ptr[i][j].m_ocp_stat == CellUnknown )
            {
                os << "U";
            }
            else
            {
                os << "*";
            }
        }
        os << ";" << endl;
    }
    return os;
}

