
void *pThread_LP(void* param)
{
    cout << "LP start to work!" << endl;
    //int i = 0;
    while(true)
    {
        pthread_mutex_lock(&mutex_GPLP);
        if( flag_GPLP==1 )
        {
            pthread_cond_signal(&cond_GPLP);
            pthread_mutex_unlock(&mutex_GPLP);
        }
        else
        {
            cnt++;
            cout << "LP: " << cnt << endl;
            if( cnt==6 )
            {
                flag_GPLP = 1;
                pthread_cond_signal(&cond_GPLP);
                pthread_mutex_unlock(&mutex_GPLP);
            }
            cout << "Setting new aim pose!" << endl;
            pthread_mutex_unlock(&mutex_GPLP);
            usleep(20000);
        }
    }
}

/**********************************************************************************/
/**************************************************************/
 // @Module Name       : Global Planning
 // @Module Author     : LiMin
 // @Module History    : 
 //     1. Created By LiMin @ 2017-04-15
 // 
 // @Module Description: 
 //     This module is used to calculate the global path for Robot
 // 
 //     
 //
/**************************************************************/
void *pThread_GP(void* param)
{
    log_t log( "./logs/GlobalPlanning"+time_filename_str(), "Global Planning Module By LiMin" );

    log.fs(INFO) << "Global Planning Start to Work..." << endl;

    vector<Point> Res; // the result of the aim position search and path planning
    vector<Point> Res_divided; // divided global path
    pose_t currPose;   // start point of search the aim position and path planning
    float direction = 90.0;

    Grid_Map_t dilateMap;
    Grid_Map_t mapSnap;
    Map_Attr_t mapAttr;

    while(true)
    {
        log.fs(INFO) << "Waiting for active signal from Local Planning Module..." << endl;
        pthread_mutex_lock(&mutex_GPLP);
        pthread_cond_wait(&cond_GPLP, &mutex_GPLP);

        log.fs(INFO) << "Active signal captured! Global Planning is executing..." << endl;

        currPose = GetPose();
        log.fs(INFO) << "Getting the map snap shoot..." << endl;
        pthread_mutex_lock( &mutex_mapData );
        mapSnap = mapData.clone();
        pthread_mutex_unlock( &mutex_mapData );
        mapAttr = mapSnap.GetAttr();
        log.fs(INFO) << "Saving Map Snap shoot..." << endl;
        mapSnap.Save(".", "GP_MapSnap");

        log.fs(INFO) << "Dilating the map snap shoot..." << endl;
        mapSnap.dilate( &dilateMap );
        dilateMap.Save(".", "GP_DilateMap");

        log.fs(INFO) << "Global Path planning..." << endl;
        Res = PathPlanning_CRT( pose2grid(currPose, mapAttr), &dilateMap );
        if( !Res.empty() )
        {
            Res_divided = PathSegmente(Res);

            log.fs(INFO) << "Global Path: "
            for( vector<Poing>::iterator iter = Res_divided.begin(); iter != Res_divided.end(); iter++ )
            {
                log.fs(ORI) << *iter << "->";
            }
            log.fs(ORI) << endl;

            SetGlobalPath( Res_divided );
            SetCleanDirection( direction );
            log.fs(INFO) << "Global Planning has Done! " << endl;
        }
        else
        {
            log.fs(INFO) << "Global Planning failed to find a path!" << endl;
        }
        pthread_mutex_unlock(&mutex_GPLP);
        //printf_globalPath( Res_divided );
        usleep(20000);
    }
}
// This is the end of Global Path planning 
// --*END*--
/*****************************************************************************/