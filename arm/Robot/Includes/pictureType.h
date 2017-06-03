#ifndef _PICTURETYPE_H
#define _PICTURETYPE_H


#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;

class piece
{
  public:
  piece(int,int,int,int);//构造函数
  void setpiece(int,int,int,int);//设置私有参数的函数
  int readz();//读取私有参数的函数
  int ready();
  int reads();
  int readx();
  private:
  int zuo;//表示“块“的左边界
  int you;//表示“块“的右边界
  int shang;//表示“块“的上边界
  int xia;//表示“块“的下边界
};

class myline
{
  public:
  myline(int,int,int);//构造函数
  void setline(int,int,int);//设置私有参数的函数
  int reads();//读取私有参数的函数
  int reade();
  int readc();
  private:
  int start;//表示线段的开端
  int end;//表示线段的结尾
  int colr;//表示线段所在列
};

#endif //_PICTURETYPE_H
