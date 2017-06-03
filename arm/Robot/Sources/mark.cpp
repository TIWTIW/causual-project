#include"mark.h"
//#include"piece.h"
//#include"myline.h"
void getlines(const Mat& img,vector<int>& stRun,vector<int>& enRun,vector<int>& colRun,int &NumberOfRuns,int minrow,int maxrow)
{
    if(NumberOfRuns!=0)
        NumberOfRuns=0;
    int i;
    for ( i = 0; i < img.cols; i++)
    {
       const  uchar *pa=img.ptr<uchar>(minrow);
       if(pa[i]==255)
        {
            NumberOfRuns++;
            stRun.push_back(0);
            colRun.push_back(i);
        }
        for (int j = minrow+1; j <= maxrow; j++)
        {
            pa=img.ptr<uchar>(j);
          const  uchar *pd=img.ptr<uchar>(j-1);
            if (pd[i] == 0 && pa[i] == 255)
            {
                NumberOfRuns++;
                stRun.push_back(j);
                colRun.push_back(i);
            }
            else if (pd[i] == 255 && pa[i] == 0)
            {
                enRun.push_back(j - 1);
            }
        }
        if (pa[i]==255)
        {
            enRun.push_back(maxrow );
        }
    }
}
void firstPass(vector<int>& stRun, vector<int>& enRun, vector<int>& colRun, int NumberOfRuns,
    int * runLabels, vector<pair<int, int> >& equivalences, int offset)
{
    
    int idxLabel = 1;
    int curRowIdx = 0;
    int firstRunOnCur = 0;
    int firstRunOnPre = 0;
    int lastRunOnPre = -1;
    //cout<<"number="<<NumberOfRuns<<endl;
    for (int i = 0; i < NumberOfRuns; i++)
    {
        if (colRun[i] != curRowIdx)
        {
            curRowIdx = colRun[i];
            firstRunOnPre = firstRunOnCur;
            lastRunOnPre = i - 1;
            firstRunOnCur = i;

        }
        for (int j = firstRunOnPre; j <= lastRunOnPre; j++)
        {
            if ((colRun[i]-colRun[j]==1)&&stRun[i] <= enRun[j] + offset && enRun[i] >= stRun[j] - offset)
            {
                if (runLabels[i] == 0) // 没有被标号过
                    runLabels[i] = runLabels[j];
                else if (runLabels[i] != runLabels[j])// 已经被标号             
                    equivalences.push_back(make_pair(runLabels[i], runLabels[j])); // 保存等价对
            }
        }
        if (runLabels[i] == 0) // 没有与前一列的任何run重合
        {
            runLabels[i] = idxLabel++;
        }

    }
}

void replaceSameLabel(int* runLabels, vector<pair<int, int> >&
    equivalence,int number,int &maxLabel)
{
    int i,j;
    maxLabel=runLabels[0];
    for(i=0;i<number;i++)
    {
      maxLabel=max(maxLabel,runLabels[i]);
    }
    int eqTab[maxLabel][maxLabel];
    for(i=0;i<maxLabel;i++)
    {
        for(j=0;j<maxLabel;j++)
        {
            eqTab[i][j]=0;
        }
    }
    //vector<vector<bool> > eqTab(maxLabel, vector<bool>(maxLabel, false));
    vector<pair<int, int> >::iterator vecPairIt = equivalence.begin();
    while (vecPairIt != equivalence.end())
    {
        eqTab[vecPairIt->first - 1][vecPairIt->second - 1] = 1;
        eqTab[vecPairIt->second - 1][vecPairIt->first - 1] = 1;
        vecPairIt++;
    }
    int labelFlag[maxLabel];
    for(i=0;i<maxLabel;i++)
    {
        labelFlag[i]=0;
    }
    //vector<int> labelFlag(maxLabel, 0);
    vector<vector<int> > equaList;
    vector<int> tempList;
    //cout << maxLabel << endl;
    for (int i = 1; i <= maxLabel; i++)
    {
        if (labelFlag[i - 1])
        {
            continue;
        }
        labelFlag[i - 1] = equaList.size() + 1;
        tempList.push_back(i);
        for (vector<int>::size_type j = 0; j < tempList.size(); j++)
        {
            for (int k = 0; k < maxLabel; k++)
            {
                if (eqTab[tempList[j] - 1][k] && !labelFlag[k])
                {
                    tempList.push_back(k + 1);
                    labelFlag[k] = equaList.size() + 1;
                }
            }
        }
        equaList.push_back(tempList);
        tempList.clear();
    }
    //cout << equaList.size() << endl;
    for (vector<int>::size_type i = 0; i <number; i++)
    {
        runLabels[i] = labelFlag[runLabels[i] - 1];
    }
    maxLabel=runLabels[0];
    for(i=0;i<number;i++)
    {
      maxLabel=max(maxLabel,runLabels[i]);
    }
}

    
void mark_white(Mat &image,Mat imageori,vector<piece>&shape,vector<vector<myline> >&coord,int minrow,int maxrow ,int &edgemask)
{
    int i,j;
    vector<int> start,end,colr;
    int number=0;
    getlines(image,start,end,colr,number,minrow,maxrow);
    int runlabels[number];
    for(i=0;i<number;i++)
    {
        runlabels[i]=0;
    }
    vector<pair<int, int> > equivalences;
  
    myline xian(0,0,0);
    piece k(0,0,0,0);
    if(number>0)
    {
        firstPass(start,end,colr,number,runlabels,equivalences,1);
        int piece;
        replaceSameLabel(runlabels,equivalences,number,piece);
        int sum[piece];
        for(i=0;i<piece;i++)
        {
            sum[i]=0;
        }
        int zuo,you,shang,xia;
        //float widebig,widesum;
        float edgesum,edgebig;
        vector<myline>_coord;
    
        for(i=0;i<piece;i++)
        {
            zuo=640;
            you=0;
            shang=480;
            xia=0;
            //widebig=0;
            //widesum=0;
            edgesum=0;
            edgebig=0;
            //flag=0;
            _coord.clear();
            edgesum=0;
            edgebig=0;
            for(j=0;j<start.size();j++)
            {
                if(runlabels[j]==i+1)
                {
                    /*if(end[j]==239)
                    {
                        flag=1;
                        break;
                    }*/
                    //widesum+=1;
                    if(colr[j]>0 && colr[j]<639 && start[j]>0 && start[j]<239)
                    {
                        uchar *edgepre=imageori.ptr<uchar>(start[j]-1);
                        uchar *edgenext=imageori.ptr<uchar>(start[j]+1);
                        if(abs(edgepre[colr[j]-1]+2*edgepre[colr[j]]+edgepre[colr[j]+1]-edgenext[colr[j]-1]-2*edgenext[colr[j]]-edgenext[colr[j]+1])>4*40)
                        {
                            edgebig+=1;
                        }
                    }
                    if(colr[j]>0 && colr[j]<639 && end[j]>0 && end[j]<239 && start[j]!=end[j])
                    {
                        uchar *edgepre=imageori.ptr<uchar>(end[j]-1);
                        uchar *edgenext=imageori.ptr<uchar>(end[j]+1);
                        if(abs(edgepre[colr[j]-1]+2*edgepre[colr[j]]+edgepre[colr[j]+1]-edgenext[colr[j]-1]-2*edgenext[colr[j]]-edgenext[colr[j]+1])>4*40)
                        {
                            edgebig+=1;
                        }
                    }
                    if(start[j]<shang)
                       shang=start[j];
                    if(end[j]>xia)
                       xia=end[j];
                    if(colr[j]<zuo)
                       zuo=colr[j];
                    if(colr[j]>you)
                       you=colr[j];
                    //if(end[j]-start[j]>=40)
                       //widebig+=1;
                    xian.setline(start[j],end[j],colr[j]);
                    _coord.push_back(xian);
                    sum[i]+=end[j]-start[j]+1;
                }
            }
            edgesum=(you-zuo+1)*2;
/*<<<<<<< HEAD
// Merge by limin @ 20170316
            
            if (sum[i]>=25)
            {
                cout << edgebig<<"--**--"<<edgesum << endl;
            }
            
            if(sum[i]>=25 && widebig/widesum<0.2 && flag==0 && edgebig/edgesum>=0.25)
======= */
            if(edgemask==1)
//>>>>>>> fxz0228
            {
                if(sum[i]>=25 )
                {
                    coord.push_back(_coord);
                    k.setpiece(zuo,you,shang,xia);
                    shape.push_back(k);
                }
                //edgemask=0;
            }
            else
            {
                if(sum[i]>=25 && edgebig/edgesum>0.25 )
                {
                    coord.push_back(_coord);
                    k.setpiece(zuo,you,shang,xia);
                    shape.push_back(k);
                }
            }
            
        }
    }
}
