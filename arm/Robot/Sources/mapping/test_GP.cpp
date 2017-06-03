#include "grid_map_core.h"
#include "GlobalPlanning.h"
#include "../logmodule/logmodule.hpp"

using namespace std;
using namespace cv;

Mat srcImgMat, dstImgMat, tmpImgMat;
Grid_Map_t dilateMap; 
const string winName = "Global Planning Test";
const string winNameGP = "Searching Path...";
void On_Mouse( int event, int x, int y, int flags, void *param );

int main(int argc, char const *argv[])
{
	if( argc != 2 )
	{
		cout << "Usage: test_GP <filename> " << endl;
		return -1;
	}


	const string imgName = argv[1];

	srcImgMat = imread( imgName, 0 );
	if( !srcImgMat.data )
	{
		cout << "Failed to Load the source image!" << endl;
		return -1;
	}

	imshow( winName, srcImgMat );
	waitKey( 1500 ); // wait 1.5s

	Grid_Map_t mapData( srcImgMat );
	//cout << mapData << endl;
	Map_Attr_t mapAttr = mapData.GetAttr();
	cout << "Map " << mapAttr << endl;
	mapData.Save(".", "InitMap");

	dilateMap.Load(".","InitMap");
	mapData.dilate( &dilateMap );
	dilateMap.Save( ".", "dilateMap" );
	//cout << dilateMap << endl;
	dstImgMat = imread( "./ocpMapdilateMap.jpg" );
	if( !dstImgMat.data )
	{
		cout << "Failed to read the dilated map image!" << endl;
		return -1;
	}

	setMouseCallback( winName, On_Mouse, 0 );
	imshow( winName, dstImgMat );
	waitKey(0);

	return 0;
}


void On_Mouse( int event, int x, int y, int flags, void *param )
{
	static Point pre_pt(-1,-1);
    static Point cur_pt(-1,-1);  
    char temp[16];

	vector<Point> Res;
	vector<Point> Res_divided;
	vector<pose_t> globalPosePath;
	vector<Point>::iterator iter;
	
	Map_Attr_t mapattr = dilateMap.GetAttr();
	Point Map_cur_pt = Point(-1,-1);
	
	vector<Point> PathDisMIn;
    if ( event == CV_EVENT_LBUTTONDOWN )  
    {  
    	srcImgMat.copyTo( tmpImgMat );
        //dstImgMat.copyTo( tmpImgMat );
        sprintf(temp,"(%d,%d)",x,y);  
        pre_pt = Point(x,y);  
        putText(tmpImgMat, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0,0),1,8); 
        circle(tmpImgMat, pre_pt, 2,Scalar(255,0,0,0), CV_FILLED,CV_AA,0);
        imshow( winNameGP, tmpImgMat );
        waitKey(1000);

        Point currPoint( y-mapattr.index_offsetX, x-mapattr.index_offsetY);


        //cout << dilateMap << endl;
        double t1=(double)getTickCount();
		Res = PathPlanning_CRT( currPoint, &dilateMap );
		Res_divided = PathSegmente(Res);
		globalPosePath = PathSegmentePoseV2(Res, mapattr.map_grid_size);
		double t2=(double)getTickCount();
		double time = (t2-t1)/getTickFrequency();
        cout << "Find Path Time Usage: " << time << "ms." << endl;

		if( Res.empty() )
		{
			cout << "No Path Found!" << endl;
		}  
		
		while( !Res.empty() )
		{	
			Map_cur_pt.x = Res.back().y+mapattr.index_offsetX;
			Map_cur_pt.y = Res.back().x+mapattr.index_offsetY;
			circle( tmpImgMat, Map_cur_pt, 1, Scalar(77,255,255), CV_FILLED, CV_AA, 0 );
			Res.pop_back();
			//imshow( winNameGP, tmpImgMat );
			//usleep(50000);
		} 
		int i = 0;
		while( !Res_divided.empty() )
		{	
			i++;
			cout << Res_divided.back();
			Map_cur_pt.x = Res_divided.back().y+mapattr.index_offsetX;
			Map_cur_pt.y = Res_divided.back().x+mapattr.index_offsetY;
			circle( tmpImgMat, Map_cur_pt, 1, Scalar(0,255,255), CV_FILLED, CV_AA, 0 );
			sprintf(temp, "%d", i);
			//putText(tmpImgMat, temp, Map_cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0),1,8); 
			Res_divided.pop_back();
			//imshow( winNameGP, tmpImgMat );
			//usleep(50000);
		}
		cout << endl;

		for( vector<pose_t>::iterator iter = globalPosePath.begin(); iter != globalPosePath.end(); iter++ )
		{
			pose_t midAim = *iter;
			cout << "(" << midAim.x << "," << midAim.y << "," << midAim.theta << ")"  << "->";
		}
		cout << endl;
		imshow( winNameGP, tmpImgMat );
		waitKey(0);
    }
    else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON)){}
    //左键没有按下的情况下鼠标移动的处理函数   
    else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON)){}
    //左键按下时，鼠标移动，则在图像上划矩形  
    else if (event == CV_EVENT_LBUTTONUP){}
    //左键松开，将在图像上划矩形 
}  