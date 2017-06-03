/**********************************************************************************/
/**************************************************************/
 // @Module Name       : Mapping
 // @Module Author     : LiMin
 // @Module History    : 
 //     1. Created By LiMin @ 2017-03-22.
 //     2. Modified By LiMin @ 2017-04012:
 //         1. Check the work-flow of the mapping module;
 //         2. Correct the map update models( compact/infrade/camera )
 // 
 // @Module Description: 
 //     This module is used to build the grid map of the robot workspace.
 // 
 //     
 //
/**************************************************************/
vector<Point> GetInfradeObstacles( pose_t currPose, int gridSize )
{
    int disL = GetGP2Y0A_L();
    int disR = GetGP2Y0A_R();
    const int threshold = 2000;
    vector<Point> Res;
    if( disL < threshold && disR < threshold )
    {
        // No Infrade detected
        Res.clear();
        return Res; 
    }
    else if( disL >= threshold && disR < threshold )
    {
        // Lefe Infrade detected
        Res.clear();
        //cout << "Left Infrade!" << endl;
        Point tmpL1 = GridLocaltoMapIndex( Point(0, 5), currPose, gridSize );
        Point tmpL2 = GridLocaltoMapIndex( Point(0, 6), currPose, gridSize );
        Res.push_back(tmpL1);
        Res.push_back(tmpL2);
        return Res;
    }
    else if( disL < threshold && disR >= threshold )
    {
        // Right Infrade detected
        Res.clear();
        //cout << "Right Infrade!" << endl;
        Point tmpL1 = GridLocaltoMapIndex( Point(0, -5), currPose, gridSize );
        Point tmpL2 = GridLocaltoMapIndex( Point(0, -6), currPose, gridSize );
        Res.push_back(tmpL1);
        Res.push_back(tmpL2);
        return Res; 
    }
    else
    {
        // Both Infrade detected
        Res.clear();
        //cout << "Both Infrade!" << endl;
        Point tmpL1 = GridLocaltoMapIndex( Point(0, 5), currPose, gridSize );
        Point tmpL2 = GridLocaltoMapIndex( Point(0, 6), currPose, gridSize );
        Point tmpL3 = GridLocaltoMapIndex( Point(0, -5), currPose, gridSize );
        Point tmpL4 = GridLocaltoMapIndex( Point(0, -6), currPose, gridSize );
        Res.push_back(tmpL1);
        Res.push_back(tmpL2);
        Res.push_back(tmpL3);
        Res.push_back(tmpL4);
        return Res; 
    }
}

vector<Point> CompactObstaclesLeft = {Point(2,4), Point(3,4), Point(4,3), Point(4,2), Point(5,2)};
vector<Point> CompactObstaclesRight = {Point(2,-4), Point(3,-4), Point(4,-3), Point(4,-2), Point(5,-2)};
vector<Point> CompactObstaclesBoth = {Point(5,1), Point(5,0), Point(5,-1)};
vector<Point> GetCompactObstacles( pose_t currPose, int gridSize )
{
    unsigned char sen1 = GetSEN1() & 0xc0;
    vector<Point> Res;
    if( sen1 == 0x80 )
    {
        // Left Compact
        vector<Point>::const_iterator iter;
        for( iter = CompactObstaclesLeft.begin(); iter != CompactObstaclesLeft.end(); iter++ )
        {
            Res.push_back( GridLocaltoMapIndex( *iter, currPose, gridSize ) );
        }
        return Res;
    }
    else if( sen1 == 0x40 )
    {
        // Right Compact
        vector<Point>::iterator iter;
        for( iter = CompactObstaclesRight.begin(); iter != CompactObstaclesRight.end(); iter++ )
        {
            Res.push_back( GridLocaltoMapIndex( *iter, currPose, gridSize ) );
        }
        return Res;
    }
    else if( sen1 == 0xc0 )
    {
        // Both Compact
        vector<Point>::iterator iter;
        for( iter = CompactObstaclesBoth.begin(); iter != CompactObstaclesBoth.end(); iter++ )
        {
            Res.push_back( GridLocaltoMapIndex( *iter, currPose, gridSize ) );
        }
        return Res;
    }
    else
    {
        // No Compact
        Res.clear();
        return Res;
    }
}



CameraMapModel_t GetFrontCameraMap(int gridSize )
{
    CameraMapModel_t Res;
    vector<Point> Ocp;
    vector<Point> Free;
    cout << "Get Front Camera map update model..." << endl;
    pthread_mutex_lock( &mutex_Take );
    pose_t currPose = posetake;
    cout << "mapping--Pose" << currPose << endl;
    for (unsigned int i=0; i<32; i++)
    {
        if( obsttake[i].first<=50 && obsttake[i].first>=0 )
        {
            // Local Position temp
            Point PhyLocation( 10*(obsttake[i].first+15), -10*obsttake[i].second );
            Point obst_Grid = toGrid( PhyLocation, gridSize );
            cout << "Ocp Grid in Robot COordinate: " << obst_Grid << endl;
            
            Ocp.push_back( obst_Grid );
            /*if( obst_Grid != Ocp.back() )
            {
                Ocp.push_back(obst_Grid);
            }*/
        }
    }
    pthread_mutex_unlock( &mutex_Take);
    cout << "mapping--Total Ocp Girds: " << Ocp.size() << endl;

    if( Ocp.empty() )
    {
        // Front Camera obstacles detected may failed, abound this frame
        Ocp.clear();
        Free.clear();
        Res.OcpGrid = Ocp;
        Res.FreeGrid = Free;
        return Res;
    }
    else
    {
        // This frame is valid
        vector<float> angleSegment;
        vector<int> lenThreshold;
        // grid is used to store the ocp state
        int grid[12][15];
        for( int i = 0; i < 12; i++ )
        {
            for( int j = 0; j < 15; j++ )
            {
                grid[i][j] = 0;
            }
        }

        // Search all the OCP grids: get the angle segment
        int minLength = 225;
        for( int i = 0; i<Ocp.size(); i++ )
        {
            if( Ocp.size() == 1 )
            {
                Point cur = Ocp.at(i);
                float angle1 = atan2f(cur.y-0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle1);
                minLength = 225;

                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                minLength = minLength <= len ? minLength : len;
                cout << minLength << endl;

                float angle2 = atan2f(cur.y+0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle2);
                lenThreshold.push_back( minLength );
                break;
            }

            if( i == 0 )
            {
                Point cur = Ocp.at(i);
                float angle1 = atan2f(cur.y-0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle1);
                minLength = 225;
                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                minLength = minLength <= len ? minLength : len;
                cout << minLength << endl;
            }
            else if( i == Ocp.size()-1 )
            {
                Point cur = Ocp.at(i);
                float angle2 = atan2f(cur.y+0.5, cur.x-4) * 180/3.14;
                angleSegment.push_back(angle2);
                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                minLength = minLength <= len ? minLength : len;
                cout << minLength << endl;
                lenThreshold.push_back( minLength );
            }
            else
            {
                Point cur = Ocp.at(i);
                Point next = Ocp.at(i+1);
                float x = next.x - cur.x;
                float y = next.y - cur.y;
                int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                if( x*x+y*y > 2 )
                {
                    // Not Border Upon
                    float angle2 = atan2f(cur.y+0.5, cur.x-4) * 180/3.14;
                    int len = (cur.x-4)*(cur.x-4) + cur.y*cur.y;
                    minLength = minLength <= len ? minLength : len;
                    cout << minLength << endl;

                    angleSegment.push_back(angle2);
                    lenThreshold.push_back( minLength );

                    float angle1 = atan2f(next.y-0.5, next.x-4) * 180/3.14;
                    angleSegment.push_back(angle1);
                    minLength = 225;
                }
                else
                {
                    minLength = minLength <= len ? minLength : len;
                    cout << minLength << endl;
                }
            }
        }

        cout << "segment size: " << angleSegment.size() << endl;
        cout << "len size: " << lenThreshold.size() << endl;
        for( int k=0; k<angleSegment.size()/2; k++)
        {
            cout << "len:" << lenThreshold.at(k) << angleSegment.at(2*k) << "~" << angleSegment.at(2*k+1) << endl;

        }

        for( int i = 5; i <= 15; i++ )
        {
            int Maxj = i<=11 ? i-4 : 19-i;
            for( int j = -Maxj; j <= Maxj; j++ )
            {
                //cout << i << "--" << j << "=" << 180/3.14*atan2f(j, i-4) << endl;
                float angleTest = atan2f(j, i-4) * 180/3.14;
                int len = j*j + (i-4)*(i-4);
                for( int k=0; k<angleSegment.size()/2; k++)
                {
                    //cout << angles.at(2*i) << "~" << angles.at(2*i+1) << endl;
                    if( angleTest >= angleSegment.at(2*k) && angleTest <= angleSegment.at(2*k+1))
                    {
                        if( len > lenThreshold.at(k) )
                        {
                            grid[i-4][j+7] = 3;
                        }
                    }
                }
            }
        }

        for( int i = 0; i<Ocp.size(); i++ )
        {
            Point cur = Ocp.at(i);
            grid[cur.x-4][cur.y+7] = 1;
        }

        for( int i = 11; i >=0; i-- )
        {
            for( int j = 0; j < 15; j++ )
            {
                cout << grid[i][j];
            }
            cout << endl;
        }
        
        vector<Point> FreeGrids;
        vector<Point> ObstGrids;
        for( int i = 5; i <= 15; i++ )
        {
            int Maxj = i<=11 ? i-4 : 19-i;
            for( int j = -Maxj; j <= Maxj; j++ )
            {
                if( grid[i-4][j+7] == 0 )
                {
                    FreeGrids.push_back( GridLocaltoMapIndex( Point(i,j), currPose, gridSize ) );
                }
                else if( grid[i-4][j+7] == 1 )
                {
                    ObstGrids.push_back( GridLocaltoMapIndex( Point(i,j), currPose, gridSize ) );
                }
            }
        }
        Res.OcpGrid = ObstGrids;
        Res.FreeGrid = FreeGrids;
    }
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
        ObstacleCompact = GetCompactObstacles(currPose, mapAttr.map_grid_size);
        log.fs(INFO) << "Compact Grids: " << ObstacleCompact.size() << endl;
        // Get the Obstacles if infraded detect obstacles
        ObstacleInfrade = GetInfradeObstacles(currPose, mapAttr.map_grid_size);
        log.fs(INFO) << "Infrade Grids: " << ObstacleCompact.size() << endl;
        // Get the Obstacles if front Camera detect obstacles
        if( flagFrontImageUpdate )
        {
            CameraMapModel_t cameraMap = GetFrontCameraMap(mapAttr.map_grid_size);
            ObstacleFrontCamera = cameraMap.OcpGrid;
            FrontCameraFreeGrid = cameraMap.FreeGrid;
            log.fs(INFO) << "Camera obstacles Grids: " << ObstacleCompact.size() << endl;
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
            if( !FrontCameraFreeGrid.empty() )
            {
                // fill the freedom area front of the robot
                mapData.fill( FrontCameraFreeGrid, CellUnknown+100, 0 );
            }
            /*
            cout << "Map Update at Physical Pose: " << currPose << "--Grid Position: " << currPosition << endl;
            vector<Point>::iterator iter;
            for( iter=ObstacleFrontCamera.begin(); iter!=ObstacleFrontCamera.end(); iter++ )
            {
                cout << *iter << endl;
            }*/
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
