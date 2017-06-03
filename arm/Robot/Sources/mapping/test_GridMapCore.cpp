
#include "grid_map_core.h"

int main(int argc, char const *argv[])
{
    if ( argc != 3 )
    {
        cout << "Usage: test_grid_map_core MapSizeX MapSizeY" << endl;
        return -1;
    }
    int MapSizeX = atoi( argv[1] );
    int MapSizeY = atoi( argv[2] );
    cout << "Input Map Size: " << MapSizeX << "x" << MapSizeY << endl;

    cout << "Start grid_map_core Testing..." << endl;
    // default constructor test
    Grid_Map_t DefaultMap;
    Map_Attr_t DefaultMap_Attr = DefaultMap.GetAttr();
 	// GetAttr() test
 	cout << DefaultMap_Attr << endl;

 	// fill_all() and Save() test
 	DefaultMap.fill_all( 25 );
    DefaultMap.Save( ".", "DefaultMap_25" );
    DefaultMap.fill_all( 255 );
    DefaultMap.Save( ".", "DefaultMap_255" );

    // fill_circle() and constructor-2 test
    Grid_Map_t SizedMap( MapSizeX, MapSizeY );
    // A white circle in the map image
    SizedMap.fill_circle( Point(0,0), MapSizeX/5, 255 );
    // A black rectangle in the map image
    SizedMap.fill_rect( Point(MapSizeX/5,0), MapSizeX/5, MapSizeY/4, 0 );
    SizedMap.Save(".", "SizedMap" );

    // constructor-5 and Load() test
    Grid_Map_t LoadMap(".", "SizedMap");
    // constructor-3 ans SetAttr() test
    Grid_Map_t CopyMap( &DefaultMap );
    Map_Attr_t newAttr = LoadMap.GetAttr();
    CopyMap.Save( ".", "CopyFromDefaultMap_255" );
    CopyMap.SetAttr( newAttr );
    CopyMap.Save( ".", "NewCopyMap" );

    // copyto() and dilate() test
    Grid_Map_t mapSnap(1,1);
    SizedMap.copyto( mapSnap );
    Grid_Map_t mapDilate( &mapSnap );
    mapSnap.dilate( &mapDilate );
    mapDilate.Save(".", "SizedMapDilate");

    return 0;
}