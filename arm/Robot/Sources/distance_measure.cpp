#include "distance_measure.h"

/*函数名 distance_measure
  输入参数 image 需要处理的图像
  输入输出参数 distance 图像中光条在横向32段的中心值
  输出参树 int 1:代表前方无障碍物 0：代表前方有障碍物*/
float distance_measure( Mat image,float *distance ,int &edgemask)
{
    cout<<"distance_measure::edgemask="<<edgemask<<endl;
    Mat element=getStructuringElement(MORPH_RECT,Size(10,10));
    int minrow,maxrow,i;
    minrow=239;
    maxrow=0;
    //imwrite(s1,image);
    Mat imageori;
    image.copyTo(imageori);
    float wholeaver,wholesum;
    wholesum=0;
    for(i=0;i<16;i++)
    {
        Mat imageROI=image(Rect(i*40,0,40,image.rows));
        wholesum+=dete(imageROI,minrow,maxrow); 
    }
    //cout<<"minrow="<<minrow<<" maxrow="<<maxrow<<endl;
    //调试的时候可以将这句注释去掉，保存分割后的二值图像
    minrow=max(0,minrow-5);
    maxrow=min(239,maxrow+5);
    //cout<<"minrow="<<minrow<<" maxrow="<<maxrow<<endl;
    if(maxrow>minrow)
    {
       Mat imageROI=image(Rect(0,minrow,image.cols,maxrow-minrow+1));
       morphologyEx(imageROI,imageROI,MORPH_CLOSE,element);
    }
    
    vector<vector<myline> >coord;
    vector<piece>shape;
    mark_white(image,imageori,shape,coord,minrow,maxrow,edgemask);
    //cout<<"mark done!"<<endl;
    centerline(image,coord,shape,distance);
    wholeaver=wholesum/16;
    return wholeaver;  
}

/*int  Frontinit()
{
     return getframe2.init();
}*/
