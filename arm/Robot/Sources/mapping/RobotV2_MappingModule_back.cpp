/**********************************************************************************/
/**************************************************************/
 // @Module Name       : Mapping
 // @Module Author     : LiMin
 // @Module History    : 
 //     1. Created By LiMin @ 2017-03-22.
 // 
 // @Module Description: 
 //     This module is used to build the grid map of the robot workspace.
 // 
 //     
 //
/**************************************************************/
int IsInfradeDetected(void)
{
    int disL = GetGP2Y0A_L();
    int disR = GetGP2Y0A_R();
    const int threshold = 2000;
    if( disL < threshold && disR < threshold )
    {
        return 0; // No Infrade detected
    }
    else if( disL >= threshold && disR < threshold )
    {
        return 1; // Lefe Infrade detected
    }
    else if( disL < threshold && disR >= threshold )
    {
        return 2; // Right Infrade detected
    }
    else
    {
        return 3; // Both Infrade detected
    }
}
vector<Point> GetInfradeObstacles_L(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    Point obst_Phy = Map_Local_to_Global(Point(0, 220), currPose);
    Point obst_Grid = Phy_to_Grid(obst_Phy, mapAttr );
    Res.push_back( obst_Grid );

    return Res;
}
vector<Point> GetInfradeObstacles_R(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    Point obst_Phy = Map_Local_to_Global(Point(0, -220), currPose);
    Point obst_Grid = Phy_to_Grid(obst_Phy, mapAttr );
    Res.push_back( obst_Grid );

    return Res;
}
vector<Point> GetInfradeObstacles_Both(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    // Left
    Point obst_Phy = Map_Local_to_Global(Point(0, 220), currPose);
    Point obst_Grid = Phy_to_Grid(obst_Phy, mapAttr );
    Res.push_back( obst_Grid );
    // Right
    obst_Phy = Map_Local_to_Global(Point(0, -220), currPose);
    obst_Grid = Phy_to_Grid(obst_Phy, mapAttr );
    Res.push_back( obst_Grid );

    return Res;
}
vector<Point> GetCompactObstacles_L(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    Point obst_Phy; 
    Point obst_Grid;

    for(int i=0; i<=4; i++)
    {
        for( int j=0; j<=4; j++)
        {
            int dis = i*i+j*j;
            if( dis>9 && dis < 25 )
            {
                obst_Phy = Map_Local_to_Global(Point(i*40, j*40), currPose);
                obst_Grid = Phy_to_Grid(obst_Phy, mapAttr );
                Res.push_back( obst_Grid );
            }
        }
    }

    return Res;
}
vector<Point> GetCompactObstacles_R(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    Point obst_Phy; 
    Point obst_Grid;

    for(int i=0; i<=4; i++)
    {
        for( int j=-4; j<=0; j++)
        {
            int dis = i*i+j*j;
            if( dis>9 && dis < 25 )
            {
                obst_Phy = Map_Local_to_Global(Point(i*40, j*40), currPose);
                obst_Grid = Phy_to_Grid(obst_Phy, mapAttr );
                Res.push_back( obst_Grid );
            }
        }
    }
    
    return Res;
}
vector<Point> GetCompactObstacles_Both(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    Point obst_Phy; 
    Point obst_Grid;

    for(int i=0; i<=4; i++)
    {
        for( int j=-4; j<=4; j++)
        {
            int dis = i*i+j*j;
            if( dis>9 && dis < 25 )
            {
                obst_Phy = Map_Local_to_Global(Point(i*40, j*40), currPose);
                obst_Grid = Phy_to_Grid(obst_Phy, mapAttr );
                Res.push_back( obst_Grid );
            }
        }
    }
    
    return Res;
}
vector<Point> GetFrontCameraObstacles(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    Point obst_Phy; 
    Point obst_Grid;

    pthread_mutex_lock( &mutex_Take );
    for (unsigned int i=0; i<32; i++)
    {
        if(obsttake[i].first<=50 && obsttake[i].first>=0)
        {
            // Local Position temp
            Point temp( 10*(obsttake[i].first+15), -10*obsttake[i].second );
            // Trans Local to Global
            obst_Phy = Map_Local_to_Global(temp, currPose);
            obst_Grid = Phy_to_Grid( obst_Phy, mapAttr );
            Res.push_back(obst_Grid);
        }
    }
    //flagFrontImageUpdate = false;
    pthread_mutex_unlock( &mutex_Take);

    return Res;
}

vector<Point> GetFrontCameraFree(pose_t currPose, Map_Attr_t mapAttr)
{
    vector<Point> Res;
    Point obst_Phy; 
    Point obst_Grid;

    pthread_mutex_lock( &mutex_Take );
    for (unsigned int i=0; i<32; i++)
    {
        if(obsttake[i].first > 50 || obsttake[i].first < 0)
        {
            // Local Position temp
            Point temp( 10*(obsttake[i].first+15), -10*obsttake[i].second );
            // Trans Local to Global
            obst_Phy = Map_Local_to_Global(temp, currPose);
            obst_Grid = Phy_to_Grid( obst_Phy, mapAttr );
            Res.push_back(obst_Grid);
        }
    }
    //flagFrontImageUpdate = false;
    pthread_mutex_unlock( &mutex_Take);
    return Res;
}

void* pThread_MapUpdate( void*argv )
{
    // Global Grid Map Initialization: Load and Set the Map Attributes
    // Robot related const values
    const int Robot_Radius_g = 4; // 4 Grids

    // Mapping thread logger 
    log_t log( "./logs/MapUpdate"+time_filename_str(), "Grid Map Update Module By LiMin" );
    log.fs(INFO) << "mapping thread Initializing... " << endl;
    // Mapping Module Initialization
    // Create a Grid Map object, the map size is define by (GridMapSizeX, GridMapSizeY)
    //unsigned int GridMapSizeX = 500;
    //unsigned int GridMapSizeY = 500;
    //Grid_Map_t mapData( GridMapSizeX, GridMapSizeY );
    Map_Attr_t mapAttr = mapData.GetAttr();
    log.fs(INFO) << "grid map object created with size: " << Size( GridMapSizeX, GridMapSizeY ) << endl;
    
    // Occupied stat map filename format: ./GridMapHis/ocpMap_<time_stamp>.jpg
    // Scan count map filename format: ./GridMapHis/cntMap_<time_stamp>.jpg
    // Note-1: the prefix--<ocp_/cnt_> and suffix--<.jpg> will be auto added while using Save() function
    // Note-2: <time_stamp> can be generated with function string time_stamp_str(void);
    // Check subdirectory "./GridMapHis" whether exist, if not create it while mode 777
    string path_str = "MapSnapShoots";
    if( DeleteDir( path_str.c_str() )!=0 )
    {
        log.fs(ERROR) << "Failed to delete the old map files!" << endl;
        log.fs(FATAL) << "mapping thread will not work!!!" << endl;
        // cancel the thread
    }
    if( !CreateDir( path_str.c_str() ) )
    {
        log.fs(ERROR) << "Failed to create the map store directory!" << endl;
        log.fs(FATAL) << "mapping thread will not work!!!" << endl;
        // cancel the thread
    }
    log.fs(INFO) << "\n Map Snap shoot images stored in directory : " << path_str << endl;

    // Robot path history will be recored in value vector<Point> pathHis in the format of grid map position
    // Note-1: gird map position can be transformed from robot pose through function Point pose2grid( pose_t, Map_Attr_t )
    vector<Point> pathHis;
    vector<pose_t> poseHis;
    // Robot current position in the grid map
    Point currPosition;
    pose_t currPose;
    Point lastConfirmedPosition;
    pose_t lastConfirmedPose;
    // Obstacle's position around the robot
    vector<Point> ObstacleCompact;
    vector<Point> ObstacleInfrade; 
    vector<Point> ObstacleFrontCamera;
    vector<Point> FrontCameraFreeGrid;

    bool flag_map_adjust_request = false;

    log.fs(INFO) << "mapping module start to work!" << endl;

    unsigned int cnt_Front = 0;
    double Start_Runtime = (double)cv::getTickCount()/cv::getTickFrequency();
    double Total_Runtime = 0;
    int tickCNT = 0;
    while( true )
    {

        mapAttr = mapData.GetAttr();

        ObstacleCompact.clear();
        ObstacleInfrade.clear();
        ObstacleFrontCamera.clear();
        FrontCameraFreeGrid.clear();
        // Step-1: Update robot current position
        currPose = GetPose();
        currPosition = pose2grid( currPose, mapAttr );

        pathHis.push_back( currPosition ); // Record the path history
        poseHis.push_back( currPose );     // Record the pose history

        // Step-0: If IMU Location Accumulative Error if big enough to Adjust the Old Path Map
        if( flag_map_adjust_request )
        {
            log.fs(WARNING) << "Adjusting map data for history localization error detected!" << endl;
            // Adjust the map ROI:
            // Search the pathHis to get the path between currPosition and lastConfirmedPosition
            // Adjust the map in the path
            lastConfirmedPosition = currPosition;
            lastConfirmedPose = currPose;
            log.fs(WARNING) << "Modify the Grid map at "
                            << "Physical Pose: " << lastConfirmedPose
                            << "Map Position: "  << lastConfirmedPosition
                            << endl;
            continue;
        }
    /***************************************************/
    //--*Start*-- Prepare the obstacles data
            // Get the Obstacles if compact detected
            switch( IsCompacted() )
            {
                case 0: // No Compact
                    ObstacleCompact.clear();
                    break;
                case 1: // Left Compact
                    ObstacleCompact = GetCompactObstacles_L(currPose, mapAttr);
                    break;
                case 2: // Right Compact
                    ObstacleCompact = GetCompactObstacles_R(currPose, mapAttr);
                    break;
                case 3: // Both Compact
                    ObstacleCompact = GetCompactObstacles_Both(currPose, mapAttr);
                    break;
                default:
                    ObstacleCompact.clear();
                    break;
            }
            // Get the Obstacles if infraded detect obstacles
            switch( IsInfradeDetected() )
            {
                case 0: // No Infrade detected
                    ObstacleInfrade.clear();
                    break;
                case 1: // Lefe Infrade detected
                    ObstacleInfrade = GetInfradeObstacles_L(currPose, mapAttr);
                    break;
                case 2: // Right Infrade detected
                    ObstacleInfrade = GetInfradeObstacles_R(currPose, mapAttr);
                    break;
                case 3: // Both detected
                    ObstacleInfrade = GetInfradeObstacles_Both(currPose, mapAttr);
                default:
                    ObstacleInfrade.clear();
                    break;
            }
            // Get the Obstacles if front Camera detect obstacles
            if( flagFrontImageUpdate )
            {
                ObstacleFrontCamera = GetFrontCameraObstacles(currPose, mapAttr);
                FrontCameraFreeGrid = GetFrontCameraFree( currPose, mapAttr );
                flagFrontImageUpdate = false;
                cnt_Front++;
            }
            
    //--*End*-- Prepare the obstacles data
    /***************************************************/

    /***************************************************/
    //--*Start*-- Update the Grid Map
            // update the area inner the robot body : update both occupied map and scan map
            mapData.fill_circle( currPosition, Robot_Radius_g, CellUnknown+100, 1 );

            // update the area outside the robot body : Only update the occupied map
            // Version 1: violence update
            mapData.fill( ObstacleCompact, CellUnknown-100, 0 );
            mapData.fill( ObstacleInfrade, CellUnknown-100, 0 );
            if( !ObstacleFrontCamera.empty() )
            {
                mapData.fill( ObstacleFrontCamera, CellUnknown-100, 0 );
                /*
                cout << "Map Update at Physical Pose: " << currPose << "--Grid Position: " << currPosition << endl;
                vector<Point>::iterator iter;
                for( iter=ObstacleFrontCamera.begin(); iter!=ObstacleFrontCamera.end(); iter++ )
                {
                    cout << *iter << endl;
                }*/
            }
            if( !FrontCameraFreeGrid.empty() )
            {
                // fill the freedom area front of the robot
                mapData.fill( FrontCameraFreeGrid, CellUnknown+100, 0 );
            }
            
    //--*End*-- Update the Grid Map
    /***************************************************/

    /***************************************************/        
    //--*Start*-- log the mapping module statistic information
            /*
            log.fs(INFO) << "Map Update at Physical Pose: " << currPose << "--Grid Position: " << currPosition
                         << "\n\t Compact Obstacle Count: " << ObstacleCompact.size()
                         << "\n\t Infrade Obstacle Count: " << ObstacleInfrade.size()
                         << "\n\t Front Obstacle Count  : " << ObstacleFrontCamera.size()
                         << endl;
            */
            Total_Runtime = (double)cv::getTickCount()/cv::getTickFrequency() - Start_Runtime;        
            tickCNT++;
            if(tickCNT%50 == 0 )
            {
                log.fs(INFO) << "Mapping Module statistic information: " 
                             << "\n\t Map Update Frequency(Hz): " << tickCNT/Total_Runtime
                             << "\n\t Front Obstacles Update Frequency(Hz): " << cnt_Front/Total_Runtime
                             << endl;
                /*log.fs(ORI) << "\n\tPath history information: "
                            << "\n\t poseHis size: " << poseHis.size();
                vector<pose_t>::iterator iter;
                for(iter = poseHis.begin(); iter != poseHis.end(); iter++ )
                {
                    if( iter==poseHis.begin() )
                        log.fs(ORI) << "\n\t Start: " << *iter << "-->";
                    else if(iter==poseHis.end()-1)
                        log.fs(ORI) << *iter << endl;
                    else
                        log.fs(ORI) << *iter << "-->";
                }
                */

                // Save the map snap shoot images
                string filename = time_filename_str();
                double t1=(double)getTickCount();
                mapData.Save( path_str, filename );
                double t2=(double)getTickCount();
                double time = (t2-t1)/getTickFrequency();
                log.fs(ORI) << "\n\t Save Map Time Usage: " << time << "s."
                                    << "\n map name: " << filename
                                    << endl;
            }

    //--*End*-- log the mapping module statistic information
    /***************************************************/        
        usleep(20000);
    } // --*while*--
    return NULL;
}
// This is the end of Module Grid Map update 
// --*END*--
/*****************************************************************************/
