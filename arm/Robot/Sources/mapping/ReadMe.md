## 地图模块

&#160;&#160;&#160;&#160;地图模块提供了用于与栅格地图相关的数据类型和操作。

&#160;&#160;&#160;&#160;数据类型主要包括三种：```Grid_Map_Cell_t, Map_Attr_t, Grid_Map_t```, 其中最关键和最复杂的是```Grid_Map_t```。

|数据类型名称|数据类型说明|
|---|---|
|Grid_Map_Cell_t | 栅格地图基本单元 |
|Map_Attr_t | 地图属性 |
|Grid_Map_t | 地图类   |

### 1. 数据类型说明

#### 1.1 栅格地图基本单元：Grid_Map_Cell_t
每个栅格单元包含两个属性：栅格占据状态```m_ocp_stat```和栅格被扫描过的次数```m_scan_cnt```，这两个属性均为```public```类型，可以直接读取和修改。

**栅格占据状态**```m_ocp_stat```为```unsigned char```类型，取值范围为[0, 255]，各数值的含义如下表所示：

栅格占据状态值 | 含义 | 别名
-----------|--------------|---
0          | 栅格有跌落危险 | CellDrop
[27, 126]  | 栅格被占据     | 
127        | 栅格占据状态未知 | CellUnknown
[128, 227] | 栅格未被占据 |
255        | 栅格有上方被遮盖，顶部摄像头不可使用 | CellUpCovered

> **一个细节**：在读取图片格式的地图数据时，为了抑制由于图片失真造成的误判，会对读取的地图图片像素值在中间部分的做未知栅格处理，即：在图片载入时，(CellUnknown-50, CellUnknown-50)会被设置为CellUnknown。

**栅格扫描状态**```m_scan_cnt```为```unsigned int```类型,为了保存地图数据方便，设定栅格的最大扫描次数为255，即```m_scan_cnt```取值范围为[0, 255].

### 1.2 地图属性：Map_Attr_t
地图属性包括六个地图参数：
* ```map_sizeX``` : 地图X轴向最大栅格数目，unsigned int类型，默认值为```Map_Default_SizeX=500```.
* ```map_sizeY``` : 地图Y轴向最大栅格数目，unsigned int类型，默认值为```Map_Default_SizeY=500```.
* ```map_grid_size``` : 每个栅格代表的真实物理空间中的尺寸，单位为mm，unsigned int类型，默认值为```Map_Default_GridSize=40```.
* ```index_offsetX``` : 栅格坐标X与存储索引之间的位移，默认为```map_sizeX```的一半
* ```index_offsetY``` : 栅格坐标Y与存储索引之间的位移，默认为```map_sizeY```的一半
* ```global_X_direction``` : 地图X轴在地球坐标系中的的绝对方向角，float类型，==暂未使用，待添加9轴陀螺仪后添加使用方法。==

地图默认属性如下：

``` C++
#define Map_Default_GridSize 40 // 默认栅格大小，单位mm
#define Map_Default_SizeX 500   // 默认地图X轴向大小
#define Map_Default_SizeY 500   // 默认地图Y轴向大小
#define Map_Index_OffsetX (Map_Default_SizeX/2) // 默认地图坐标和存储索引偏移量--X
#define Map_Index_OffsetY (Map_Default_SizeY/2) // 默认地图坐标和存储索引偏移量--Y
```

### 1.3 栅格地图类型：Grid_Map_t
&#160;&#160;&#160;&#160;设计```Grid_Map_t```是为了更方便地对地图数据进行搜索、更新、存储、加载等操作。
#### 1.3.1 Grid_Map_t变量
含两个成员变量：

变量名    | 类型              |变量说明
----------|-------------------|---------
**ptr     | public Grid_Map_Cell_t | 二维指针，便于调整地图尺寸，不要在地图类成员函数以外直接使用！
m_mapattr | private Map_Attr_t    | 地图的属性

#### 1.3.2 Grid_Map_t方法

**构造函数/析构函数**：
* Grid_Map_t()：根据默认的地图属性，创建一张空白地图；
* Grid_Map_t( unsigned int SizeX, unsigned int SizeY )：创建大小为SizeX X SizeY的空白地图；
* Grid_Map_t( const Grid_Map_t *srcMapData )：基于已经存在的地图复制地图。特别说明：输入参数必须为引用类型
* Grid_Map_t( Mat mapImage )：根据图像数据构建地图。
* Grid_Map_t( string directory, string mapName )：根据地图图片路径创建地图数据

* ~Grid_Map_t()：因为使用到了指针,构造地图时使用Init()开辟内存空间，所以析构函数要求主动调用UnInit()释放内存空间。

**地图复制函数**：
* void copyto( Grid_Map_t &mapSnap );
* Grid_Map_t clone(void); // 很奇怪在PC上能正确运行，但是在开发板上运行错误，怀疑是开发板使用的编译器太老

**存储空间开辟/释放函数**：

> 内部private函数，请勿使用！

* void Init( void )： 用于依据地图属性开辟合适大小的内存区域用于存储地图数据。
* void UnInit( void )：用于释放存储地图数据的内存空间。

**地图属性操作**：
* void SetAttr( Map_Attr_t newAttr )：用于设置重新设定地图属性，目前版本将释放原有内存空间（擦除原有地图数据），然后依据新的地图属性重新开辟内存空间（生成空白的地图）；
* Map_Attr_t GetAttr( void ) const：获取当前地图的属性值。

**栅格单元状态判断**：

> 在进行栅格单元操作时，一定要确保地址索引在规定的范围以内，建议使用```IsInside()```方法先进行一次判断。特别声明：Grid_Map_t提供的所有操作均要求做到地址安全！

&#160;&#160;&#160;&#160;栅格状态方法的函数名称形式为IsXxx(),输入参数可以是```Point```类型或者```int x, int y```表示的***栅格坐标***，返回类型为```bool```类型。

* bool IsInside( Point t );
* bool IsInside( int index_x, int index_y );
* bool IsUnknown( Point t );
* bool IsUnknown( int index_x, int index_y );
* bool IsOcp( Point t );
* bool IsOcp( int index_x, int index_y );
* bool IsReachable( Point t );
* bool IsReachable( int index_x, int index_y );
* bool IsUpCovered( Point t );
* bool IsUpCovered( int index_x, int index_y );
* bool IsDrop( Point t );
* bool IsDrop( int index_x, int index_y );
* bool IsUnScan( Point t );
* bool IsUnScan( int index_x, int index_y );

**栅格单元状态读取/设置操作**：
* unsigned char GetGridOcpStat( Point t );
* unsigned char GetGridOcpStat( int x, int y );
* void SetGridOcpStat( Point t, unsigned char newStat );
* void SetGridOcpStat( int x, int y, unsigned char newStat );
* unsigned int GetGridCntStat( Point t );
* unsigned int GetGridCntStat( int x, int y );
* void SetGridCntStat( Point t, unsigned int newCnt );
* void SetGridCntStat( int x, int y, unsigned int newCnt );

**局部地图操作**：
* bool UpdateLocalMap( int x, int y, Grid_Map_t *localMap );
* void fill_all( unsigned char ocp_stat=CellUnknown+100 );
* void fill_circle( Point center, int Radius, unsigned char ocp_stat, int flag=0 );
* void fill_rect( Point center, int len_x, int len_y, unsigned char ocp_stat, int flag=0 );
* void fill( vector<Point> p, unsigned char newStat, unsigned int newCnt );

**全局地图操作**：
* void dilate( Grid_Map_t *dstGridMap );

**地图存储/加载函数**:
* void Save( string directory, string mapName );
* void Load( string directory, string mapName );

### 2. 相关操作方法说明

#### 2.1 坐标转换操作

&#160;&#160;&#160;&#160;```grid_map_coordinate.h```提供了四个坐标转换函数：

* Point pose2grid( pose_t pose, Map_Attr_t mapAttr )：位姿向栅格坐标的转化
* Point  Phy_to_Grid( Point phy, Map_Attr_t mapAttr )：世界坐标向栅格坐标的转化
* Point  Map_Global_to_Local(Point global, location_t pose)：世界坐标向机器人坐标的转换
* Point  Map_Local_to_Global(Point local,  location_t pose)：机器人坐标向世界坐标的转化

#### 2.2 全局规划操作
&#160;&#160;&#160;&#160;```GlobalPlanning.h```提供了全局规划所需要的全部函数：
* vector<Point> PathPlanning_CRT(  Point startPoint, Grid_Map_t *mapdata )：全局规划的接口函数，用于搜索地图获取全局路径；
* vector<Point> GetPath( Point startPoint, Point endPoint , Grid_Map_t *mapdata, float *GridValue[] )：全局规划内部函数，用于从价值矩阵中获取全局路径；
* vector<Point> PathSegmente( vector<Point> globalPath )：全局规划内部函数，用于分割密集的全局路径；

### 3. 地图测试和使用


#### 3.3.1 Grid_Map_t使用示例一：Grid_Map_t 测试程序

```C++

#include "grid_map_core.h"

int main(int argc, char const *argv[])
{
    if ( argc != 3 )
    {
        cout << "Usage: test_grid_map_core MapSizeX MapSizeY" << endl;
        return -1;
    }
    int MapSizeX = atoi( argv[1] );
    int MapSizeY = atoi( argv[2] );
    cout << "Input Map Size: " << MapSizeX << "x" << MapSizeY << endl;

    cout << "Start grid_map_core Testing..." << endl;
    // default constructor test
    Grid_Map_t DefaultMap;
    Map_Attr_t DefaultMap_Attr = DefaultMap.GetAttr();
    // GetAttr() test
    cout << DefaultMap_Attr << endl;

    // fill_all() and Save() test
    DefaultMap.fill_all( 25 );
    DefaultMap.Save( ".", "DefaultMap_25" );
    DefaultMap.fill_all( 255 );
    DefaultMap.Save( ".", "DefaultMap_255" );

    // fill_circle() and constructor-2 test
    Grid_Map_t SizedMap( MapSizeX, MapSizeY );
    // A white circle in the map image
    SizedMap.fill_circle( Point(0,0), MapSizeX/5, 255 );
    // A black rectangle in the map image
    SizedMap.fill_rect( Point(MapSizeX/5,0), MapSizeX/5, MapSizeY/4, 0 );
    SizedMap.Save(".", "SizedMap" );

    // constructor-5 and Load() test
    Grid_Map_t LoadMap(".", "SizedMap");
    // constructor-3 ans SetAttr() test
    Grid_Map_t CopyMap( &DefaultMap );
    Map_Attr_t newAttr = LoadMap.GetAttr();
    CopyMap.Save( ".", "CopyFromDefaultMap_255" );
    CopyMap.SetAttr( newAttr );
    CopyMap.Save( ".", "NewCopyMap" );

    // copyto() and dilate() test
    Grid_Map_t mapSnap(1,1);
    SizedMap.copyto( mapSnap );
    Grid_Map_t mapDilate( &mapSnap );
    mapSnap.dilate( &mapDilate );
    mapDilate.Save(".", "SizedMapDilate");

    return 0;
}
```