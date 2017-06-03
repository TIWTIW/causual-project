#include "distance_decoder.h"

#define STEPLEN

void distance_decoder(float *distance, pair<float,float> *realobst )
{
    //cout<<"decode start"<<endl;
    //double distance[32]={126.3,126.863,126.525,126.325,125.463,124.775,123.238,121.8,120.262,118.262,116.137,113.637,111.012,108.012,104.537,101.213};
    double angle[32]={-0.882,-0.824,-0.766,-0.708,-0.650,-0.591,-0.533,-0.475,-0.416,-0.358,-0.3,-0.242,-0.183,-0.125,-0.067,-0.0084,0.0498,0.108,0.166,0.225,0.283,0.341,0.4,0.458,0.516,0.574,0.633,0.691,0.749,0.808,0.866,0.924};
    double offset[2][32]={{15.36 ,14.29 ,14.05 ,13.62 ,13.28 ,12.66 ,13.65 ,13.71 ,12.76 ,10.83 ,11.38 ,11.39 ,11.77 ,10.70 ,10.67 ,11.48 ,9.86 ,10.38 ,10.51 ,10.33 ,10.47 ,10.27 ,10.37 ,10.27 ,10.20 ,10.51 ,10.85 ,11.30 ,11.53 ,9.90 ,11.61 ,10.64 },{17.50 ,18.84 ,18.56 ,16.39 ,15.99 ,16.22 ,15.04 ,16.13 ,15.35 ,15.13 ,14.34 ,13.16 ,12.81 ,14.87 ,14.87 ,14.83 ,14.20 ,14.46 ,12.46 ,12.39 ,13.37 ,15.65 ,13.87 ,13.49 ,13.44 ,15.49 ,13.65 ,13.60 ,13.51 ,12.91 ,11.80 ,11.93 }};

    double product[2][32]={{925.33 ,956.99 ,957.70 ,966.85 ,972.93 ,985.96 ,953.02 ,945.63 ,964.93 ,1013.79 ,994.61 ,993.71 ,981.15 ,1000.39 ,997.97 ,971.11 ,1010.85 ,994.61 ,991.09 ,993.33 ,987.91 ,994.22 ,993.11 ,994.22 ,995.43 ,986.13 ,975.18 ,956.27 ,947.47 ,990.01 ,931.62 ,954.23 },{893.02 ,867.74 ,876.88 ,918.53 ,917.74 ,913.40 ,927.28 ,904.68 ,915.70 ,915.35 ,927.63 ,947.33 ,945.80 ,904.51 ,904.51 ,902.56 ,916.03 ,908.71 ,943.13 ,942.16 ,924.96 ,884.06 ,914.54 ,922.51 ,923.82 ,885.92 ,917.87 ,918.39 ,914.79 ,920.00 ,932.96 ,922.06 }};

    unsigned int i;
    //把obst转化为坐标（纵向距离，横向距离），按障碍物来分
    //vector<pair<double,double> >realobst;//不按障碍物分，所有的有值点都放到一起
    //vector<int>obstnum;//点的号码
    double vert,level;//纵向距离和横向距离
    for(i=0;i<32;i++)
    {
        //cout<<distance[i]<<endl;
        if(distance[i]!=0)
        {
            vert=product[distance[i]>60][i]/(distance[i]-offset[distance[i]>60][i]);
            //cout<<product[distance[i]>60][i]<<" "<<distance[i]<<" "<<offset[distance[i]>60][i]<<endl;
            level=vert*angle[i];
            //cout<<"vert"<<vert<<" level="<<level<<endl;
            realobst[i]=make_pair(vert,level);
        }
        else
            realobst[i]=make_pair(-1,-1);
    }
    //cout<<"realobst.size()="<<realobst.size()<<endl;
    //for(i=0;i<32;i++)
        //cout<<realobst[i].first<<" "<<realobst[i].second<<endl;
   
    
}

void Frontobst(pair<float,float> *realobst,vector<pair<float,float> >&frontobst,float &frontnearest,unsigned int &frontnearestnum,float &extendnearest,float &extendfarthest,int alongdirection)
{
    int i;
    frontobst.clear();
    int extendnearestnum;
    vector<pair<float,float> >extendobst;
    if(alongdirection==2)
    {
        frontnearest=100;
        for(i=0;i<32;i++)
        {
            if(realobst[i].first>0 && realobst[i].first <=50 && realobst[i].second<=15.5 && realobst[i].second>=-15.5)
            {
                //cout<<realobst[i].first<<" "<<realobst[i].second<<endl;
                frontnearest=realobst[i].first+(17-sqrt(289-realobst[i].second*realobst[i].second));
                //cout<<"nearest="<<frontnearest<<endl;
                frontobst.push_back(realobst[i]);
                frontnearestnum=frontobst.size()-1;
                break;
            }
        }
        for(i=i+1;i<32;i++)
        {
            if(realobst[i].first>0 && realobst[i].first <=50 && realobst[i].second<=15.5 && realobst[i].second>=-15.5)
            {
                frontobst.push_back(realobst[i]);
                //cout<<realobst[i].first<<" "<<realobst[i].second<<endl;
                if(realobst[i].first+(17-sqrt(289-realobst[i].second*realobst[i].second))<frontnearest)
                {
                    frontnearest=realobst[i].first+(17-sqrt(289-realobst[i].second*realobst[i].second));
                    //cout<<"nearest="<<frontnearest<<endl;
                    frontnearestnum=frontobst.size()-1;
                }
            }
        }
        extendnearest=frontnearest;

        for(i=0;i<32;i++)
        {
            if(realobst[i].first>0 && realobst[i].second<=21.5 && realobst[i].second>15.5)
            {
                extendobst.push_back(realobst[i]);
                if(realobst[i].first<extendnearest)
                {
                    extendnearest=realobst[i].first;
                    extendnearestnum=extendobst.size()-1;
                }
            }
        }

        extendfarthest=extendnearest;
        if(extendnearest<frontnearest)
        {
            for(i=extendnearestnum;i>=0;i--)
            {
                if(extendobst[i].first<extendfarthest+34)
                {
                    extendfarthest=extendobst[i].first;
                }
            }
        }
        //cout<<"frontnearest="<<frontnearest<<" extendnearest="<<extendnearest<<" extendfarthest="<<extendfarthest<<endl;
    }
    if(alongdirection==0)
    {
        frontnearest=100;
        for(i=0;i<32;i++)
        {
            if(realobst[i].first>0 && realobst[i].first <=50 && realobst[i].second<=15.5 && realobst[i].second>=-15.5)
            {
                //cout<<realobst[i].first<<" "<<realobst[i].second<<endl;
                frontnearest=realobst[i].first+(17-sqrt(289-realobst[i].second*realobst[i].second));
                //cout<<"nearest="<<frontnearest<<endl;
                frontobst.push_back(realobst[i]);
                frontnearestnum=frontobst.size()-1;
                break;
            }
        }
        for(i=i+1;i<32;i++)
        {
            if(realobst[i].first>0 && realobst[i].first <=50 && realobst[i].second<=15.5 && realobst[i].second>=-15.5)
            {
                frontobst.push_back(realobst[i]);
                //cout<<realobst[i].first<<" "<<realobst[i].second<<endl;
                if(realobst[i].first+(17-sqrt(289-realobst[i].second*realobst[i].second))<frontnearest)
                {
                    frontnearest=realobst[i].first+(17-sqrt(289-realobst[i].second*realobst[i].second));
                    //cout<<"nearest="<<frontnearest<<endl;
                    frontnearestnum=frontobst.size()-1;
                }
            }
        }
        extendnearest=frontnearest;
        for(i=0;i<32;i++)
        {
            if(realobst[i].first>0 && realobst[i].second<=-15.5 && realobst[i].second>-21.5)
            {
                extendobst.push_back(realobst[i]);
                if(realobst[i].first<extendnearest)
                {
                    extendnearest=realobst[i].first;
                    extendnearestnum=extendobst.size()-1;
                }
            }
        }
        extendfarthest=extendnearest;
        if(extendnearest<frontnearest)
        {
            for(i=extendnearestnum;i>=0;i--)
            {
                if(extendobst[i].first<extendfarthest+34)
                {
                    extendfarthest=extendobst[i].first;
                }
            }
        }
    }
}

void CrossLine(vector<unsigned int> &slopepair,vector<pair<float,float> >realobst,unsigned int index,unsigned int index2)
{
    unsigned int flag;
    unsigned int i,j;
    float slope,offset;
    if(index>index2)
    {
        for(i=index2;i<index;)
        {
            flag=0;
            //cout<<"i="<<i<<endl;
            slope=(realobst[i].first-realobst[index].first)/(realobst[i].second-realobst[index].second);
            offset=realobst[i].first-slope*realobst[i].second;
            for(j=index2;j<index;j++)
            {
                if(j!=i&&j!=index)
                {
                    if(slope*realobst[j].second+offset>realobst[j].first)
                    {
                        flag++;
                        break;
                    }
                }
            }
            if(flag==0)
            {
                slopepair.push_back(i);
                //cout<<"yes!"<<endl;
                break;
            }
            else
                i=i+1;
        }
    }
    else
    {
        for(i=index+1;i<=index2;)
        {
            flag=0;
            //cout<<"i="<<i<<endl;
            slope=(realobst[i].first-realobst[index].first)/(realobst[i].second-realobst[index].second);
            offset=realobst[i].first-slope*realobst[i].second;
            //cout<<"slope="<<slope<<" offset="<<offset<<endl;
            for(j=index+1;j<=index2;j++)
            {
                if(j!=i&&j!=index)
                {
                    if(slope*realobst[j].second+offset>realobst[j].first)
                    {
                        flag++;
                        break;
                    }
                }
            }
            if(flag==0)
            {
                slopepair.push_back(i);
                cout<<"yes!"<<endl;
                break;
            }
            else
                i=i+1;
        }
    }
    
}

float DisP2P(float x1,float y1,float x2,float y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void LineParam(float x1,float y1,float x2,float y2,float &a, float &b ,float &c)
{
    if(x2==x1)
    {
        b=0;
        a=1;
        c=-x2;
    }
    else if(y1==y2)
    {
        a=0;
        b=1;
        c=-y1;
    }
    else
    {
        b=-1;
        a=(y2-y1)/(x2-x1);
        c=y1-a*x1;
    }
    //cout<<"a="<<a<<" b="<<b<<"c="<<c<<endl;
}
float DisP2L(float x0,float y0,float a,float b ,float c)
{
    float denominator=sqrt(a*a+b*b);
    float numerator=a*x0+b*y0+c;
    return abs(numerator/denominator);
}
bool FreeTooMuch(vector<pair<float,float> >realobst,unsigned int index1,unsigned int index2, unsigned int &farest ,float a,float b,float c)
{
    unsigned int i;
    float dx=DisP2P(realobst[index1].first,realobst[index1].second,realobst[index2].first,realobst[index2].second);
    cout<<"index1="<<index1<<" index2"<<index2<<endl;
    float areasum=0;
    float dy;
    float maxy=0;
    if(index1<index2)
    {
        dx=dx/(index2-index1);
        cout<<"dx="<<dx<<endl;
        for(i=index1+1;i<index2;i++)
        {
            dy=DisP2L(realobst[i].second,realobst[i].first,a,b,c);
            if(dy>maxy)
            {
                maxy=dy;
                farest=i;
            }
            areasum+=dy*dx;
        }
    }
    else
    {
        dx=dx/(index1-index2);
        cout<<"dx="<<dx<<endl;
        for(i=index2+1;i<index1;i++)
        {
            dy=DisP2L(realobst[i].second,realobst[i].first,a,b,c);
            if(dy>maxy)
            {
                maxy=dy;
                farest=i;
            }
            areasum+=dy*dx;
        }
    }
    cout<<"the areasum="<<areasum<<endl;
    areasum+=dy*dx;
    if(areasum>120)
        return true;
    else
        return false;
}
void AngleIsOk(float angle,vector<pair<float,float> >realobst,float nearestnum,float &realfront,int turndirection)
{
    unsigned i;
    float mid;
    if(angle!=90)
    {
        for(i=0;i<realobst.size();i++)
        {
            mid=-(1-turndirection)*(realobst[i].second-realobst[nearestnum].second)/tan(angle*3.14/180);
            mid+=realobst[nearestnum].first;
            mid+=(17-sqrt(289-realobst[i].second*realobst[i].second));
            //cout<<i<<" mid="<<mid<<endl;
            if(mid<realfront)
            {
                realfront=mid;
            } 
        }
    }
}
float AngleANDLengthGet(vector<pair<float,float> >&realobst,float &turnlength,unsigned int nearestnum,int turndirection, float &realfront)
{

    unsigned int i,j;
    turnlength=0;
    float angle=90;
    int judgeflag=1;
    /*cout<<"frontnearestnum="<<nearestnum<<endl;
    for(i=0;i<realobst.size();i++)
    {
        cout<<i<<" "<<realobst[i].first<<" "<<realobst[i].second<<endl;
    }*/
    if(turndirection==0)
    {
        vector<unsigned int>slopepair;
        float a,b,c;
        if(realobst.size()>1)
        {
            if(nearestnum>0 && nearestnum<realobst.size()-1)
            {    
                CrossLine(slopepair,realobst,nearestnum,0);
                if(slopepair.size()>0)
                {
                    LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                    angle=angleget(a,b,0);
                    if(DisP2L(0,-15,a,b,c)<17)
                    {
                        judgeflag=0;
                        CrossLine(slopepair,realobst,nearestnum,realobst.size()-1);
                        LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                        angle=angleget(a,b,0);
                        if(DisP2L(0,-15,a,b,c)<17)
                        {
                            angle=90;
                        }
                    }
                }
            }
            else if(nearestnum==0)
            {
                CrossLine(slopepair,realobst,nearestnum,realobst.size()-1);
                if(slopepair.size()>0)
                {
                    LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                    angle=angleget(a,b,0);
                }
            }
            else if(nearestnum==realobst.size()-1)
            {
                CrossLine(slopepair,realobst,nearestnum,0);
                if(slopepair.size()>0)
                {
                    LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                    angle=angleget(a,b,0);
                    if(DisP2L(0,-15,a,b,c)<17)
                    {
                        judgeflag=0;
                        angle=90;
                    }
                }
            }
            //cout<<"angle="<<angle<<endl;
            unsigned int farest;
            if(judgeflag==1)
            {
                if(FreeTooMuch(realobst,slopepair[0],nearestnum,farest,a,b,c))
                {
                    //cout<<"farest"<<farest<<endl;
                    float a2,b2,c2,a3,b3,c3,dis;
                    vector<unsigned int> slopepair2,slopepair3;
                    if(slopepair[0]<nearestnum)
                    {
                        CrossLine(slopepair2,realobst,farest,slopepair[0]);
                        CrossLine(slopepair3,realobst,farest,nearestnum);
                    }
                    else
                    {
                        CrossLine(slopepair3,realobst,farest,slopepair[0]);
                        CrossLine(slopepair2,realobst,farest,nearestnum);
                    }
                    LineParam(realobst[slopepair2[0]].second,realobst[slopepair2[0]].first,realobst[farest].second,realobst[farest].first,a2,b2,c2);
                    LineParam(realobst[farest].second,realobst[farest].first,realobst[slopepair3[0]].second,realobst[slopepair3[0]].first,a3,b3,c3);
                    angle=angleget(a2,b2,0);
                    //cout<<"angle="<<angle<<endl;
                    dis=100;
                    AngleIsOk(angle,realobst,farest,dis,0);
                    //cout<<"dis="<<dis<<endl;
                    if(dis-realfront>5)
                    {
                        angle=angleget(a3,b3,0)+90;
                        //cout<<"dis2="<<DisP2L(0,realfront-15,a3,b3,c3)<<endl;
                        if(DisP2L(0,realfront-15,a3,b3,c3)>=16)
                        {
                            angle-=90;
                        }
                        lengthget(realobst,nearestnum,angle,turnlength,0);
                        AngleIsOk(angle,realobst,farest,realfront,0);
                        //cout<<"angle="<<angle<<endl;
                    }
                    else 
                    {
                        if(dis-realfront<0)
                        {
                            realfront=dis;
                        }
                        lengthget(realobst,farest,angle,turnlength,0);
                    }
                }
                else
                {
                    AngleIsOk(angle,realobst,nearestnum,realfront,0);
                    lengthget(realobst,nearestnum,angle,turnlength,0);
                }
            }
            else
            {
                AngleIsOk(angle,realobst,nearestnum,realfront,0);
                lengthget(realobst,nearestnum,angle,turnlength,0);
            }
            
        }
        else if(realobst.size()==1)
        {
            angle=90;
            lengthget(realobst,nearestnum,angle,turnlength,0);
        }
    } 
    if(turndirection==2)
    {
        vector<unsigned int>slopepair;
        float a,b,c;
        if(realobst.size()>1)
        {
            if(nearestnum<realobst.size()-1 && nearestnum>0)
            {    
                CrossLine(slopepair,realobst,nearestnum,realobst.size()-1);
                if(slopepair.size()>0)
                {
                    LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                    angle=angleget(a,b,2);
                    if(DisP2L(0,-15,a,b,c)<17)
                    {
                        judgeflag=0;
                        CrossLine(slopepair,realobst,nearestnum,0);
                        LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                        angle=angleget(a,b,2);
                        if(DisP2L(0,-15,a,b,c)<17)
                        {
                            angle=90;
                        }
                    }
                }
            }
            else if(nearestnum==realobst.size()-1)
            {
                CrossLine(slopepair,realobst,nearestnum,0);
                if(slopepair.size()>0)
                {
                    LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                    angle=angleget(a,b,2);
                }
            }
            else if(nearestnum==0)
            {
                CrossLine(slopepair,realobst,nearestnum,realobst.size());
                if(slopepair.size()>0)
                {
                    LineParam(realobst[slopepair[0]].second,realobst[slopepair[0]].first,realobst[nearestnum].second,realobst[nearestnum].first,a,b,c);
                    angle=angleget(a,b,2);
                    if(DisP2L(0,-15,a,b,c)<17)
                    {
                        judgeflag=0;
                        angle=90;
                    }
                }
            }
            cout<<"angle="<<angle<<endl;
            unsigned int farest;
            if(judgeflag==1)
            {
                if(FreeTooMuch(realobst,slopepair[0],nearestnum,farest,a,b,c))
                {
                    //cout<<"farest"<<farest<<endl;
                    float a2,b2,c2,a3,b3,c3,dis;
                    vector<unsigned int> slopepair2,slopepair3;
                    if(slopepair[0]<nearestnum)
                    {
                        CrossLine(slopepair2,realobst,farest,slopepair[0]);
                        CrossLine(slopepair3,realobst,farest,nearestnum);
                    }
                    else
                    {
                        CrossLine(slopepair3,realobst,farest,slopepair[0]);
                        CrossLine(slopepair2,realobst,farest,nearestnum);
                    }
                    LineParam(realobst[slopepair2[0]].second,realobst[slopepair2[0]].first,realobst[farest].second,realobst[farest].first,a3,b3,c3);
                    LineParam(realobst[farest].second,realobst[farest].first,realobst[slopepair3[0]].second,realobst[slopepair3[0]].first,a2,b2,c2);
                    angle=angleget(a2,b2,2);
                    //cout<<"angle="<<angle<<endl;
                    dis=100;
                    AngleIsOk(angle,realobst,farest,dis,2);
                    //cout<<"dis="<<dis<<endl;
                    if(dis-realfront>5)
                    {
                        angle=angleget(a3,b3,2)+90;
                        //cout<<"dis2="<<DisP2L(0,realfront-15,a3,b3,c3)<<endl;
                        if(DisP2L(0,realfront-15,a3,b3,c3)>=16)
                        {
                            angle-=90;
                        }
                        lengthget(realobst,nearestnum,angle,turnlength,2);
                        //cout<<"angle="<<angle<<endl;
                    }
                    else
                    {
                        lengthget(realobst,farest,angle,turnlength,2);
                    }
                }
                else
                {
                    AngleIsOk(angle,realobst,nearestnum,realfront,2);
                    lengthget(realobst,nearestnum,angle,turnlength,2);
                }
            }
            else
            {
                AngleIsOk(angle,realobst,nearestnum,realfront,2);
                lengthget(realobst,nearestnum,angle,turnlength,2);
            }
        }
        else if(realobst.size()==1)
        {
            angle=90;
            lengthget(realobst,nearestnum,angle,turnlength,2);
        }
    } 
    return angle;
}
void lengthget(vector<pair<float,float> >realobst,unsigned int index,float angle,float &turnlength,int direction)
{
    float mid;
    int i;
    //cout<<"index="<<index<<endl;
    if(direction==0)
    {
        for(i=index;i>=0;i--)
        {
            //cout<<i<<endl;
            mid=(realobst[i].second-realobst[index].second)/tan(3.14*angle/180);
            //cout<<"mid="<<mid<<endl;
            //cout<<"mid2="<<mid+realobst[i].first-realobst[index].first<<endl;
            if(mid+realobst[i].first-realobst[index].first<=5 && mid+realobst[i].first-realobst[index].first>0)
            {
                if(17-realobst[i].second>turnlength)
                {
                    turnlength=17-realobst[i].second;
                }
            }
        }
    }
    else if(direction==2)
    {
        for(i=index;i<realobst.size();i++)
        {
            //cout<<i<<endl;
            mid=-(realobst[i].second-realobst[index].second)/tan(3.14*angle/180);
            //cout<<"mid="<<mid<<endl;
            //cout<<"mid2="<<mid+realobst[i].first-realobst[index].first<<endl;
            if(mid+realobst[i].first-realobst[index].first<=5 && mid+realobst[i].first-realobst[index].first>0)
            {
                if(17+realobst[i].second>turnlength)
                {
                    turnlength=17+realobst[i].second;
                }
            }
        }
    }   
    //cout<<"turnlength before="<<turnlength<<endl;
    turnlength=turnlength/sin(3.14*angle/180)+17*(1-tan(1.57*angle/180));
    
}

float angleget(float a ,float b ,int direction )
{
    float angle;
    if(direction==0)
    {
        if(a==0)
        {
            angle=90;
        }
        else
        {
            angle=atan(-b/a)*180/3.14;
            if(-b/a<0)
            {
                angle=-angle;
            }
            else
            {
                angle=180-angle;
            }
        }
    }
    if(direction==2)
    {
        if(a==0)
        {
            angle=90;
        }
        else
        {
            angle=atan(-b/a)*180/3.14;
            if(-b/a<0)
            {
                angle=180+angle;
            }
        }
    }
    return angle;
}
int Infrared_decoder(int voltage)
{
    if(voltage>2100)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void obst_convert(pose_t posetake, pose_t posenow, pair<float,float> *obsttake, pair<float,float> *obstnow )
{
    unsigned int i;
    float midx,midy;
    float rad;
    //float dx,dy;
    rad=(posetake.theta-90)*3.14/180;
    for(i=0;i<32;i++)
    {
        if(obsttake[i].first>0)
        {
            obstnow[i].first=(obsttake[i].first+15)*cos(rad)+obsttake[i].second*sin(rad)+posetake.y/10;
            obstnow[i].second=obsttake[i].second*cos(rad)-(obsttake[i].first+15)*sin(rad)+posetake.x/10;
        }
        else
        {
            obstnow[i].first=-1;
            obstnow[i].second=-1;
        } 
    }
    rad=(posenow.theta-90)*3.14/180;
    for(i=0;i<32;i++)
    {
        if(obsttake[i].first>0)
        {
            midy=(obstnow[i].first-posenow.y/10)*cos(rad)-(obstnow[i].second-posenow.x/10)*sin(rad);
            midx=(obstnow[i].second-posenow.x/10)*cos(rad)+(obstnow[i].first-posenow.y/10)*sin(rad);
            obstnow[i].first=midy-15;
            obstnow[i].second=midx;
        }
    }
}

void obst_convert2(pose_t posetake, pose_t posenow, pair<float,float> *obsttake, pair<float,float> *obstnow ,int flag)
{
    unsigned int i;
    float midx,midy;
    float rad;
    //float dx,dy;
    rad=(posetake.theta-90)*3.14/180;
    for(i=0;i<32;i++)
    {
        if(obsttake[i].first>0)
        {
            obstnow[i].first=(obsttake[i].first+15)*cos(rad)+obsttake[i].second*sin(rad)+posetake.y/10;
            obstnow[i].second=obsttake[i].second*cos(rad)-(obsttake[i].first+15)*sin(rad)+posetake.x/10;
        }
        else
        {
            obstnow[i].first=-1;
            obstnow[i].second=-1;
        } 
    }
    /*for(i=0;i<32;i++)
    {
        cout<<"obstnow1= "<<i<<" "<<obstnow[i].first<<" "<<obstnow[i].second<<endl;
    }*/
    cout<<"poseturn="<<posetake<<endl;
    cout<<"posenow="<<posenow<<endl;
    rad=(posenow.theta-90)*3.14/180;
    for(i=0;i<32;i++)
    {
        if(obsttake[i].first>0)
        {
            midy=(obstnow[i].first-posenow.y/10)*cos(rad)-(obstnow[i].second-posenow.x/10)*sin(rad);
            midx=(obstnow[i].second-posenow.x/10)*cos(rad)+(obstnow[i].first-posenow.y/10)*sin(rad);
            obstnow[i].first=midy-15;
            obstnow[i].second=midx;
        }
    }
}