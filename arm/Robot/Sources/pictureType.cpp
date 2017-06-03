#include"pictureType.h"

piece::piece(int _zuo,int _you,int _shang,int _xia)
{
 zuo=_zuo;
 you=_you;
 shang=_shang;
 xia=_xia;
}
void piece::setpiece(int _zuo,int _you,int _shang,int _xia)
{
 zuo=_zuo;
 you=_you;
 shang=_shang;
 xia=_xia;
}
int piece::readz()
{
  return zuo;
}
int piece::ready()
{
  return you;
}
int piece::reads()
{
  return shang;
}
int piece::readx()
{
  return xia;
}



myline::myline(int _start,int _end,int _colr)
{
  start=_start;
  end=_end;
  colr=_colr;
}
void myline::setline(int _start,int _end,int _colr)
{
  start=_start;
  end=_end;
  colr=_colr;
}
int myline::reads()
{
  return start;
}
int myline::reade()
{
  return end;
}
int myline::readc()
{
  return colr;
}
  
