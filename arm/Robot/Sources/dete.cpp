#include"dete.h"
float dete(Mat &img,int &minrow,int &maxrow)
{
  
  int i,j;
  float graysum=0;
  float grayaver=0;
  // for(i=0;i<256;i++)
  // cout<<i<<" "<<a[i]<<endl;
  //统计直方图
  const int histSize=256;
  MatND hist;
  const float franges[]={0,256};
  const float* ranges[]={franges};
  const int channels=0;
  calcHist(&img,1,&channels,Mat(),hist,1,&histSize,&ranges[0],true,false);
  float *a=(float *)hist.data;
  //cout<<endl;
  //输出直方图信息
  // for(i=0;i<256;i++)
  //  cout<<i<<" "<<a[i]<<endl;
 
  int ac[86];//直方图尺寸缩小为原来的三分之一，为了排除伪峰值和谷值
  int bigpeak=0;//存放直方图的最大峰值（灰度最大，即从最大灰度向下扫描，遇到的第一个峰值）
  int cut=0;//存放直方图的阈值（从最大峰值向下扫描遇到的第一个谷值）
 
  for(i=0;i<85;i++)
  {
       ac[i]=a[i*3]+a[i*3+1]+a[i*3+2];
       graysum+=ac[i]*(i*3+1);
  }
  ac[85]=a[255];
  graysum+=ac[85]*255;
  grayaver=graysum/(img.rows*img.cols);
  // for(i=0;i<86;i++)
   //  cout<<i<<" "<<ac[i]<<endl;

  if(ac[85]>ac[84]&&ac[85]>ac[83])
  {
      bigpeak=85;
  }
  else
  {
      for(i=85;i>=1;i--)
      {
          if((ac[i]>ac[i+1])&&(ac[i]>ac[i-1])&&ac[i]>=5)
          {
              bigpeak=i;
              break; 
          }
      }
          
  }
  //cout<<"bigpeak="<<bigpeak<<" ";
  int histbig=ac[bigpeak];
  int bigpeak2=bigpeak;
  for(i=bigpeak-3;i<=min(bigpeak+3,86);i++)
  {
      if(ac[i]>histbig)
      {
          bigpeak2=i;
          histbig=ac[i];
      }
  }
  //cout<<"bigpeak2="<<bigpeak2<<" ";
  if(bigpeak2>1)
  {
      for(i=bigpeak2-1;i>=1;i--)
      {
          if(ac[i]<=ac[i+1] && ac[i]<=ac[i-1] && ac[i+1]+ac[i-1]-2*ac[i]>=4)
          {
              cut=i;
              break;
          }
      }
          
  } 
  else if(bigpeak2==1||bigpeak2==0)
  {
      cut=1;
  }

  int cutfin0;
  cutfin0=cut*3;
  int histmax=a[cutfin0];
  int cutfin=cutfin0;
  for(i=max(0,cutfin0-6);i<min(bigpeak2*3 ,cutfin0+9);i++)
  {
      if(a[i]<histmax)
      {
          histmax=a[i];
          cutfin=i;
      }
  }
      
  if(cutfin==0)
  {
      cutfin=1; 
  }
  if(cutfin>=threshget(grayaver) && grayaver<=210)
  {
      for ( i=0;i<img.rows;i++)
      {
          uchar *imgdata=img.ptr<uchar>(i);
          for( j=0;j<img.cols;j++)
          {
              if(imgdata[j]>=cutfin)
              {
                  imgdata[j]=255;
                  minrow=min(minrow,i);
                  maxrow=max(maxrow,i);
              }
              else
                  imgdata[j]=0; 
          }
      }
  }
      
  else
  {
      for ( i=0;i<img.rows;i++)
      {
          uchar *imgdata=img.ptr<uchar>(i);
          for( j=0;j<img.cols;j++)
          {
              imgdata[j]=0; 
          }
      }
  }
  return grayaver;
      
    

 //imshow("cut",img);
}

float aver(Mat img)
{
    float graysum=0;
    float grayaver;
    for(int i=0;i<img.rows;i++)
    {
        uchar *data=img.ptr<uchar>(i);
        for(int j=0;j<img.cols;j++)
        {
            graysum+=data[j];
        }
    }
    grayaver=graysum/(img.rows*img.cols);
    return grayaver;
}
int threshget(float grayaver)
{
    if(grayaver<10)
    {
        return 0;
    }
    else if(grayaver<40)
    {
        return 100;
    }
    else if(grayaver<80)
    {
        return 150;
    }
    else
    {
        return 210;
    }
}