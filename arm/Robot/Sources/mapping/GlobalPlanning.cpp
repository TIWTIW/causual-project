#include "GlobalPlanning.h"

vector<Point> PathPlanning_CRT(  Point startPoint, Grid_Map_t *mapdata )
{
	vector<Point> path;

	if( mapdata->IsOcp(startPoint) )
	{
		cout << "Bad Start Point: Start Point is Occupied!" << startPoint << endl;
		return path;
	}
	if( mapdata->IsUnknown(startPoint)  )
	{
		cout << "Bad Start Point: Start Point is Unknown!" << startPoint<< endl;
		return path;
	}

	vector<Point> DetectList;
	vector<Point> DetectListNew;
	vector<Point> aimPointCandidate;
	const Map_Attr_t mapattr = mapdata->GetAttr();
	const int MapSizeX = mapattr.map_sizeX;
	const int MapSizeY = mapattr.map_sizeY;
	const int MapIndexOffsetX = mapattr.index_offsetX;
	const int MapIndexOffsetY = mapattr.index_offsetY;
	const int maxval = MapSizeX + MapSizeY;

	DetectList.push_back( startPoint );
	cout << "Searching path from " << startPoint << " to it's nearest unknown area..."<< endl;

	int pathlen = 0;
	Point aimPoint(-1,-1);

	// Initialize the GirdPathValue Matrix
	float **GridPathValue;
	GridPathValue = new float*[MapSizeX];
	for (unsigned int i = 0; i < MapSizeX; ++i)
	{
		GridPathValue[i] = new float[MapSizeY];
	}
	for( int i=0; i<MapSizeX; i++ )
	{
	    for( int j=0; j<MapSizeY; j++ )
	    {
			GridPathValue[i][j] = maxval;   	
	    }
	}

	GridPathValue[startPoint.x+MapIndexOffsetX][startPoint.y+MapIndexOffsetX] = 0;

	// Searching the nearest unknown gird and the reachable path
	//cout << "Starting to search the aimPoint..." << endl;
	while( true )
	{
		if( DetectList.empty() )
		{
			cout << " There is no reachable unknown area in the map! " << endl;
			return path;
		}

		// Search the Unoccupied grids of the outer ring: DetectList
		while( !DetectList.empty() )
		{
			// Current search point: currPt
			Point currPt = DetectList.back();
			DetectList.pop_back();
			//cout << "Searching Point: " << currPt << endl;
			// Search all the grids adjoin currPt
			for( int i=-1; i<=1; i++ )
			{
				for( int j=-1; j<=1; j++ )
				{
					Point testPoint( currPt.x + i, currPt.y + j );
					Point indextest(testPoint.x+MapIndexOffsetX, testPoint.y+MapIndexOffsetY);

					if( mapdata->IsInside( testPoint.x, testPoint.y ) )
					{
						//cout << testPoint << endl;
						switch( abs(i)+abs(j) )
						{
							case 1:
								if( mapdata->IsUnknown( testPoint ) && GridPathValue[indextest.x][indextest.y] > GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1)
								{
									GridPathValue[indextest.x][indextest.y] = GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1;
									//cout << "Find the Nearest Unknown Grid!" << testPoint << endl;
									aimPointCandidate.push_back(testPoint);
								}
								if( mapdata->IsReachable(testPoint) && GridPathValue[indextest.x][indextest.y]>GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1)
								{
									GridPathValue[indextest.x][indextest.y] = GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1;
									//cout << "Adding Aim Position:" << testPoint << endl;
									//if( GridPathValue[indextest.x][indextest.y] == maxval )
									//{
										DetectListNew.push_back(testPoint);
									//}
								}
								break;
							case 2:
								if( mapdata->IsUnknown( testPoint ) && GridPathValue[indextest.x][indextest.y] > GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1.4 )
								{
									GridPathValue[indextest.x][indextest.y] = GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1.4;
									//cout << "Find the Nearest Unknown Grid!" << testPoint << endl;
									aimPointCandidate.push_back(testPoint);
								}
								if( mapdata->IsReachable(testPoint) && GridPathValue[indextest.x][indextest.y] > GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1.4)
								{
									GridPathValue[indextest.x][indextest.y] = GridPathValue[currPt.x+MapIndexOffsetX][currPt.y+MapIndexOffsetY]+1.4;
									//cout << "Adding Aim Position:" << testPoint << endl;
									//if( GridPathValue[indextest.x][indextest.y] == maxval )
									//{
										DetectListNew.push_back(testPoint);
									//}
								}
								break;
							default:
								break;
						}

					}
				}
			}
		}
		//cout << "aimPointCandidate size: " << aimPointCandidate.size() << endl;
		if( !aimPointCandidate.empty() )
		{
			// Get the nearest unknown grid
			float pathlen = maxval;
			Point aimPoint;
			vector<Point>::iterator iter;
			for( iter=aimPointCandidate.begin(); iter!=aimPointCandidate.end();iter++ )
			{
				if( pathlen > GridPathValue[iter->x+MapIndexOffsetX][iter->y+MapIndexOffsetY] ) 
				{
					pathlen = GridPathValue[iter->x+MapIndexOffsetX][iter->y+MapIndexOffsetY];
					aimPoint = *iter;
					//cout << aimPoint << endl;
				}
			}
			cout << "Getting the path..." << endl;
			return GetPath( startPoint, aimPoint , mapdata, GridPathValue);
		}
		// Enlarge the search ring
		while( !DetectListNew.empty() )
		{
			DetectList.push_back( DetectListNew.back() );
			DetectListNew.pop_back();
		}
	}
}

vector<Point> GetPath( Point startPoint, Point endPoint , Grid_Map_t *mapdata, float *GridPathValue[] )
{
	const Map_Attr_t mapattr = mapdata->GetAttr();
	const int maxval = mapattr.map_sizeX+ mapattr.map_sizeY;
	const int MapIndexOffsetX = mapattr.index_offsetX;
	const int MapIndexOffsetY = mapattr.index_offsetY;
	vector<Point> ResPath;
	if( GridPathValue[endPoint.x+MapIndexOffsetX][endPoint.y+MapIndexOffsetY] == maxval )
	{
		cout << endPoint << "aim position unreachable!" << endl;
		return ResPath;
	}
	
	Point nextPoint = endPoint;
	Point CurrPoint = endPoint;
	cout << "Finding Path from "<< startPoint << "to" << endPoint << endl;
	ResPath.push_back(endPoint);
	while( CurrPoint != startPoint )
	{
		//cout << nextPoint << "=" << GridPathValue[nextPoint.x][nextPoint.y] << endl;
		for( int i=-1; i<=1; i++ )
		{
			for( int j=-1; j<=1; j++ )
			{
				if( abs(i)+abs(j)!=0 )
				{
					Point testPoint;
					testPoint.x = nextPoint.x + i;
					testPoint.y = nextPoint.y + j;
					Point indextest(testPoint.x+MapIndexOffsetX, testPoint.y+MapIndexOffsetY);
					
					if( mapdata->IsInside( testPoint ) )
					{
						//cout << startPoint << "=" << GridPathValue[startPoint.x][startPoint.y] << testPoint << "=" << GridPathValue[indextest.x][indextest.y] << endl;
						if( GridPathValue[indextest.x][indextest.y] < GridPathValue[CurrPoint.x+MapIndexOffsetX][CurrPoint.y+MapIndexOffsetY] )
						{
							//cout << testPoint << "=" << GridPathValue[indextest.x][indextest.y] << endl;
							CurrPoint = testPoint;
						}
					}
				}
			}
		}
		//cout << "Adding New Path Grid!" << endl;
		ResPath.push_back( CurrPoint );
		nextPoint = CurrPoint;
	}
	ResPath.push_back(startPoint);
	return ResPath;
}

vector<Point> PathSegmente( vector<Point> globalPath )
{
	vector<Point>::iterator iter = globalPath.begin();

	cout << "PathSegmente: From " << *(globalPath.end()-1) << "to" << *iter << endl;

	vector<Point> resPath;

	Point P1 = *globalPath.begin();
	Point P2 = *globalPath.begin();
	Point P3 = *(globalPath.begin()+1);

	//resPath.push_back(P1);

	int len=0;

	for ( iter = globalPath.begin(); iter+1 != globalPath.end(); iter++ )
	{
		P2 = *iter;
		P3 = *(iter+1);

		Point V1(P2.x-P1.x, P2.y-P1.y);
		Point V2(P3.x-P2.x, P3.y-P2.y);
		float angle_V1 = atan2f(V1.y, V1.x);
		float angle_V2 = atan2f(V2.y, V2.x);

		if( angle_V2 == angle_V1 )
		{
			len++;
			if(len==15)
			{
				//cout << angle_V1 << "---" << angle_V2 << endl;
				//cout << P2 << endl;
				resPath.push_back(P2);
				P1 = P2;
				len=0;
			}
		}
		else
		{
			//cout << angle_V1 << "---" << angle_V2 << endl;
			//cout << P2 << endl;
			resPath.push_back(P2);
			P1 = P2;
			len=0;
		}
	}
	return resPath;
}

vector<pose_t> PathSegmentePose( vector<Point> globalPath, int map_grid_size)
{
	vector<Point>::iterator iter = globalPath.begin();
	cout << "PathSegmente: From " << *(globalPath.end()-1) << "to" << *iter << endl;
	
	Point P1 = *globalPath.begin();
	Point P2 = *globalPath.begin();
	Point P3 = *(globalPath.begin()+1);

	vector<pose_t> resPath;

	int len=0;
	for ( iter = globalPath.begin(); iter+1 != globalPath.end(); iter++ )
	{
		P2 = *iter;
		P3 = *(iter+1);

		Point V1(P2.x-P1.x, P2.y-P1.y);
		Point V2(P3.x-P2.x, P3.y-P2.y);

		float angle_V1 = atan2f(V1.y, V1.x);
		float angle_V2 = atan2f(V2.y, V2.x);

		if( angle_V2 == angle_V1 )
		{
			len++;
			if(len==20)
			{
				cout << angle_V1* _180_D_PI << "<--->" << angle_V2* _180_D_PI << endl;
				cout << P2 << endl;
				pose_t aimPose;
				aimPose.x = float( P2.x*map_grid_size + map_grid_size/2 );
				aimPose.y = float( P2.y*map_grid_size + map_grid_size/2 );
				aimPose.theta = -angle_V1 * _180_D_PI;
				resPath.push_back(aimPose);
				P1 = P2;
				len=0;
			}
		}
		else
		{
			cout << angle_V1* _180_D_PI << "<--->" << angle_V2* _180_D_PI << endl;
			cout << P2 << endl;
			pose_t aimPose;
			aimPose.x = float( P2.x*map_grid_size + map_grid_size/2 );
			aimPose.y = float( P2.y*map_grid_size + map_grid_size/2 );
			aimPose.theta = -angle_V1 * _180_D_PI;
			resPath.push_back(aimPose);
			P1 = P2;
			len=0;
		}
	}
	return resPath;
}
vector<pose_t> PathSegmentePoseV2( vector<Point> globalPath, int map_grid_size)
{
	vector<Point>::reverse_iterator iter = globalPath.rbegin();
	cout << "PathSegmente: From " << *globalPath.rbegin() << "to" << *(globalPath.rend()-1) << endl;
	
	Point P1 = *globalPath.rbegin();
	Point P2 = *globalPath.rbegin();
	Point P3 = *(globalPath.rbegin()+1);

	vector<pose_t> resPath;

	int len=0;
	for ( iter = globalPath.rbegin(); iter+1 != globalPath.rend(); iter++ )
	{
		P2 = *iter;
		P3 = *(iter+1);

		Point V1(P2.x-P1.x, P2.y-P1.y);
		Point V2(P3.x-P2.x, P3.y-P2.y);

		float angle_V1 = atan2f(V1.y, V1.x);
		float angle_V2 = atan2f(V2.y, V2.x);

		if( iter == globalPath.rbegin() )
		{
			pose_t aimPose;
			aimPose.x = float( P2.x*map_grid_size + map_grid_size/2 );
			aimPose.y = float( P2.y*map_grid_size + map_grid_size/2 );
			aimPose.theta = angle_V2 * _180_D_PI;
			resPath.push_back(aimPose);
		}
		
		if( angle_V2 == angle_V1 )
		{
			len++;
			if(len==20)
			{
				//cout << angle_V1* _180_D_PI << "<--->" << angle_V2* _180_D_PI << endl;
				//cout << P2 << endl;
				pose_t aimPose;
				aimPose.x = float( P2.x*map_grid_size + map_grid_size/2 );
				aimPose.y = float( P2.y*map_grid_size + map_grid_size/2 );
				aimPose.theta = angle_V2 * _180_D_PI;
				resPath.push_back(aimPose);
				P1 = P2;
				len=0;
			}
		}
		else
		{
			//cout << angle_V1* _180_D_PI << "<--->" << angle_V2* _180_D_PI << endl;
			//cout << P2 << endl;
			pose_t aimPose;
			aimPose.x = float( P2.x*map_grid_size + map_grid_size/2 );
			aimPose.y = float( P2.y*map_grid_size + map_grid_size/2 );
			aimPose.theta = angle_V2 * _180_D_PI;
			resPath.push_back(aimPose);
			P1 = P2;
			len=0;
		}

		if( iter+1 == globalPath.rend()-1 )
		{
			pose_t aimPose;
			aimPose.x = float( P3.x*map_grid_size + map_grid_size/2 );
			aimPose.y = float( P3.y*map_grid_size + map_grid_size/2 );
			aimPose.theta = angle_V2 * _180_D_PI;
			resPath.push_back(aimPose);
		}
	}
	return resPath;
}