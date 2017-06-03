
#include"centerline.h"
void downsize(vector<vector<myline> > coord,vector<vector<float> >&centerfinal)
{
    unsigned int i,j,y;
    //int _col;
    //_col=coord[0][0].readc();
    //cout<<"_col "<<_col<<endl;
    //cout<<"a"<<endl;
    vector<vector<float> >center;
    //vector<float>_center;
    //_center.push_back(0);
    //centerfinal.assign(640,_center);
    centerfinal.resize(640);
    //，对于每个光条，将640个像素分为32段，每一段20个像素长度，光条在每一段中所有列的中心值（若光条经过该列）都设为一样
    double num_in_20[32],sum_of_20[32],aver_of_20[32];//每一块（20个像素）中正常的列的个数，所有正常列的高度之和，这一块中所有列的高度平均值
    //int aver_flag[32]={0};
    int normal_in_20[32]={0};//记录一段20列中正常列的个数
    int abnormal_in_20[32]={0};//记录一段20列中异常列的个数
    int flag_of_20[32]={0};//记录每一段需要处理的方法：为0表示为正常段或无值段，不必处理，为1表示将当前段的中心值设为下一段的中心值，为2设为上一段的中心值，为3设为上一段下一段的中心值的平均值
    int success;
    float aver_of_640,normal_in_32,sum_in_640,num_in_640;//aver_of_640所有列的平均中心值，normal_in_32十六段中正常段的个数
    for(y=0;y<coord.size();y++)
    {       
        center.clear();
        //center.assign(640,_center);
        center.resize(640);
        for(j=0;j<coord[y].size();j++)//将“块”中每一列每个线段的中心值都存入center容器（一列可能不止一个中心值，所以采用容器而不是数组）
        {
            center[coord[y][j].readc()].push_back(float(coord[y][j].reads()+coord[y][j].reade())/2);
        }
    
        //若一段里存在正常列，则成为正常段，若全为空列，则成为无值段，若即存在空列又存在异常列而没有正常列，则成为冲突段
                       
        for(i=0;i<32;i++)//进行初步计算，算出所有正常段的中心值
        {
            num_in_20[i]=0;
            sum_of_20[i]=0;
            aver_of_20[i]=0;
            //aver_flag[i]=0;
            normal_in_20[i]=0;
            abnormal_in_20[i]=0;
            flag_of_20[i]=0;
            num_in_640=0;
            sum_in_640=0;
            for(j=i*20;j<(i+1)*20;j++)//统计每一段中正常列和异常列的个数
            {
                if(center[j].size()==1)
                    normal_in_20[i]+=1;
                else if(center[j].size()>1)
                    abnormal_in_20[i]+=1;

            }
            if(normal_in_20[i]>0&&normal_in_20[i]<=20)//若存在正常列，则计算所有正常列中心值的平均值，以此来代替该段的所有非空列的中心值
            {
                for(j=i*20;j<(i+1)*20;j++)
                if(center[j].size()==1)
                {
                    num_in_20[i]++;
                    sum_of_20[i]+=center[j][0];
                }
                if(num_in_20[i]!=0)
                {
                    aver_of_20[i]=sum_of_20[i]/num_in_20[i];
                    for(j=i*20;j<(i+1)*20;j++)
                    if(center[j].size()>=1)
                    {
                        center[j][0]=(float)aver_of_20[i];
                    }
                }
            }

        }


        normal_in_32=0;//计算32段里正常段的个数
        //for(i=0;i<32;i++)
         // cout<<i<<"normal_in_20="<<normal_in_20[i]<<"abnormal_in_20= "<<abnormal_in_20[i]<<endl;

        for(i=0;i<32;i++)
        {
            if(normal_in_20[i]<=20&&normal_in_20[i]>0)
                normal_in_32++;
        }
        //cout<<"normal_in_32"<<normal_in_32<<endl;
        if(normal_in_32==0)//如果32段里没有一段是正常的，即所有的段都是冲突段或无值段，计算所有段的所有线段的中心值
        {
            for(i=0;i<640;i++)
            {
                for(j=0;j<center[i].size();j++)
                {
                    num_in_640++;
                    sum_in_640+=center[i][j];
                }
            }
            if(num_in_640>0)
            {
                aver_of_640=(float)sum_in_640/(num_in_640);
                for(j=0;j<640;j++)
                    if(center[j].size()>0)
                        center[j][0]=aver_of_640;
            }
        }
        else//只要32段里有一个正常段，就可以进行计算
        {
            while(1)
            {
                success=0;
                if(normal_in_20[0]==0&&abnormal_in_20[i]>0)//若第一段为冲突段，只需判断第二段是否为正常段
                {
                    if(normal_in_20[1]>0&& normal_in_20[1]<=20)
                    {
                        for(j=0;j<20;j++)
                            if(center[j].size()>0)
                                center[j][0]=(float)aver_of_20[1];
                        flag_of_20[0]=2;
                    }
                }
                for(i=1;i<31;i++)//对于第二段到第十五段，都需判断两边的段是否为正常段
                {
                    if(normal_in_20[i]==0&&abnormal_in_20[i]>0)
                    {
                        if((normal_in_20[i-1]>0&&normal_in_20[i-1]<=20)&&(normal_in_20[i+1]>0&&normal_in_20[i+1]<=20))
                        {
                            for(j=i*20;j<(i+1)*20;j++)
                                if(center[j].size()>0)
                                    center[j][0]=(float)(aver_of_20[i-1]+aver_of_20[i+1])/2;
                            flag_of_20[i]=3;
                            //normal_in_20[i]=60;
                        }
                        else if(normal_in_20[i-1]>0&&normal_in_20[i-1]<=20)
                        {
                            for(j=i*20;j<(i+1)*20;j++)
                                if(center[j].size()>0)
                                    center[j][0]=(float)aver_of_20[i-1];
                            flag_of_20[i]=1;
                            //normal_in_20[i]=60;
                        }
                        else if(normal_in_20[i+1]>0&&normal_in_20[i+1]<=20)
                        {
                            for(j=i*20;j<(i+1)*20;j++)
                                if(center[j].size()>0)
                                    center[j][0]=(float)aver_of_20[i+1];
                            flag_of_20[i]=2;

                        }
                    }

                }
                if(normal_in_20[31]==0&&abnormal_in_20[31]>0)//对于第十六段，只需判断第十五段是否为正常段
                {
                    if(normal_in_20[30]>0&&normal_in_20[30]<=20)
                    {
                        for(j=600;j<640;j++)
                            if(center[j].size()>0)
                                center[j][0]=(float)aver_of_20[30];
                        flag_of_20[i]=1;
                      //normal_in_20[31]=60;
                    }
                }
                for(i=0;i<32;i++)//根据之前的标记对冲突段进行赋值
                {
                    if(flag_of_20[i]==1)
                    {
                        aver_of_20[i]=aver_of_20[i-1];
                        normal_in_20[i]=10;
                    }
                    else if(flag_of_20[i]==2)
                    {
                        aver_of_20[i]=aver_of_20[i+1];
                        normal_in_20[i]=10;
                    }
                    else if(flag_of_20[i]==3)
                    {
                        aver_of_20[i]=(aver_of_20[i-1]+aver_of_20[i+1])/2;
                        normal_in_20[i]=10;
                    }
                }

                for(i=0;i<32;i++)//统计经过一次处理后还剩下的冲突段的个数，若为0，则表示所有冲突段都已得到处理，退出循环
                    if(normal_in_20[i]==0&&abnormal_in_20[i]>0)
                        success++;
                if(success==0)
                    break;
            }
        }
        for(i=0;i<center.size();i++)//将每一块算出的每一列的中心值存入centerfinal容器中，准备下一步的干扰处理
        {
            if(center[i].size()>=1)
            {
                centerfinal[i].push_back(center[i][0]);
            }
        }
        //if(y==1)
        //imshow("daa",dst);
    }
}


void denoise(vector<vector<float> >&centerfinal,vector<piece> shape)
{
    float dvalue,value;
    int success;
    unsigned int i,j,y;
    vector<pair<unsigned int,unsigned int> >abnormalrow;
    double sum,aver;
    unsigned int max=shape.size();
    int flag[max];
    /*这部分代码解决了这样一个问题，如下图所示
    ——————      ——————
    ——————
    如果经过之前的处理之后，得到的中心值图像上图一样，在图像的左边有一块连续的列，在连续的列里，
    每一列都有不止一个中心值，而且这一连续列是孤立的，周围没有正常的列，若不处理，则会使后面的
    程序陷入死循环，处理方法是对于这样连续的列，将其每列的中心值都设为其几个中心值的平均值*/
    for(i=0;i<max;i++)
        flag[i]=0;
    for(i=0;i<shape.size();i++)
    {
        if(flag[i]==1)
            continue;
        for(j=0;j<shape.size();j++)
        {
            if(i!=j&&shape[i].readz()==shape[j].readz()&&shape[i].ready()==shape[j].ready())
                abnormalrow.push_back(make_pair(shape[i].readz(),shape[i].ready()));
            flag[i]=1;
            flag[j]=1;
        }
    }
    vector<float>::iterator it;
    if(abnormalrow.size()>0)
    {
        for(i=0;i<abnormalrow.size();i++)
        {
            for(y=abnormalrow[i].first;y<=abnormalrow[i].second;y++)
            {
                sum=0;
                for(j=0;j<centerfinal[y].size();j++)
                    sum+=centerfinal[y][j];
                aver=sum/(j-1);
                //cout<<"j"<<j-1<<endl;
                centerfinal[y][0]=(float)aver;
                //cout<<"aver"<<(int)aver<<endl;
                for(it=centerfinal[y].begin()+1;it!=centerfinal[y].end();)
                    it=centerfinal[y].erase(it);
                //cout<<"b"<<endl;
            }
        }
    }

    while(1)
    {
        success=0;
        //如果某列存在多个中心值，即表示该列经过不止一个块，说明存在干扰，对于干扰的处理如下：
        //（1）若该列左边不存在干扰，则判断此列所有中心值跟左边列中心值差距最小的一个，设为此列的中心值，其他的去掉
        // (2) 若该列右边不存在干扰，则判断此列所有中心值跟右边列中心值差距最小的一个，设为此列的中心值，其他的去掉
        //（3）若该列左右列都不存在干扰，则判断此列所有中心值跟左右列中心值平均值差距最小的一个，设为此列的中心值，其他的去掉
        if(centerfinal[0].size()>1)//对第一列进行处理
        {
            dvalue=640;
            success++;
            if(centerfinal[1].size()==1)
            {
                for(j=1;j<centerfinal[0].size();j++)
                    if(abs(centerfinal[1][0]-centerfinal[0][j])<dvalue)
                    {
                        dvalue=abs(centerfinal[0][j]-centerfinal[1][0]);
                        value=centerfinal[0][j];
                    }
                centerfinal[0][0]=value;
                for(it=centerfinal[0].begin()+1;it!=centerfinal[0].end();)//这个删除的步骤貌似可以去掉，也不影响结果，但是不去的话输出更直观
                    it=centerfinal[0].erase(it);
            }
        }

        for(i=1;i<centerfinal.size()-1;i++)//对其他列进行处理
        {
            if(centerfinal[i].size()>1)
            {
                success++;
                dvalue=640;
                if(centerfinal[i-1].size()==1&&centerfinal[i+1].size()==1)
                {
                    for(j=1;j<centerfinal[i].size();j++)
                        if(abs((centerfinal[i-1][0]+centerfinal[i+1][0])/2-centerfinal[i][j])<dvalue)
                        {
                            dvalue=abs((centerfinal[i-1][0]+centerfinal[i+1][0])/2-centerfinal[i][j]);
                            value=centerfinal[i][j];
                        }
                    centerfinal[i][0]=value;
                    for(it=centerfinal[i].begin()+1;it!=centerfinal[i].end();)
                        it=centerfinal[i].erase(it);
                }
                else if(centerfinal[i-1].size()==1)
                {
                    for(j=1;j<centerfinal[i].size();j++)
                        if(abs(centerfinal[i-1][0]-centerfinal[i][j])<dvalue)
                        {
                            dvalue=abs(centerfinal[i][j]-centerfinal[i-1][0]);
                            value=centerfinal[i][j];
                        }
                        centerfinal[i][1]=value;
                        for(it=centerfinal[i].begin()+1;it!=centerfinal[i].end();)
                            it=centerfinal[i].erase(it);
                }
                else if(centerfinal[i+1].size()==1)
                {
                    for(j=1;j<centerfinal[i].size();j++)
                        if(abs(centerfinal[i+1][0]-centerfinal[i][j])<dvalue)
                        {
                            dvalue=abs(centerfinal[i][j]-centerfinal[i+1][0]);
                            value=centerfinal[i][j];
                        }
                        centerfinal[i][0]=value;
                        for(it=centerfinal[i].begin()+1;it!=centerfinal[i].end();)
                            it=centerfinal[i].erase(it);
                }
            }
        }
        if(centerfinal[639].size()>1)
        {
            success++;
            if(centerfinal[638].size()==1)
            {
                for(j=1;j<centerfinal[639].size();j++)
                    if(abs(centerfinal[638][0]-centerfinal[639][j])<dvalue)
                    {
                        dvalue=abs(centerfinal[639][j]-centerfinal[638][0]);
                        value=centerfinal[639][j];
                    }
                centerfinal[639][0]=value;
                for(it=centerfinal[639].begin()+1;it!=centerfinal[639].end();)
                    it=centerfinal[639].erase(it);
            }
        }
        if(success==0)
            break;
    }
}
void centerline(Mat image,vector<vector<myline> >coord,vector<piece>shape,float *distance)
{
 int i;
 vector<vector<float> >centerfinal;
 //int i,j,y;
 //cout<<"a"<<endl;
 //vector<vector<pair<int,double> > >center;
 //vector<pair<int,double> >_center;
 
 Mat dst=Mat::zeros(image.rows,image.cols,CV_8UC1);
 
 downsize(coord,centerfinal);
// cout<<"downsize done!"<<endl;
  
  denoise(centerfinal,shape);
 // cout<<"denoise done!"<<endl;
   
  for(i=10;i<640;i+=20)
     {
       if(centerfinal[i].size()>=1)
         {
          //cout<<i<<" "<<centerfinal[i][0]<<endl;
          distance[i/20]=centerfinal[i][0];
         }
       else
          distance[i/20]=0;
     }
  
}
       
    
