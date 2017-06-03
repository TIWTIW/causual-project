#include "cornerextraction.h"
#define USE_SIMPLIFY 1 //简化运算
const int imgwidth=640;
const int imgheight=480;
cornerExtraction::cornerExtraction()
{
    
}
struct greaterThanPtr
{
    bool operator()(const float* a, const float* b) const { return *a > *b; }
};
//用于计算方向角度值
static const float atan2_p1 = 0.9997878412794807f*(float)(180/CV_PI);
static const float atan2_p3 = -0.3258083974640975f*(float)(180/CV_PI);
static const float atan2_p5 = 0.1555786518463281f*(float)(180/CV_PI);
static const float atan2_p7 = -0.04432655554792128f*(float)(180/CV_PI);
//OpenCV源码提供的256对随机点对
const int pattern_opencv[256*4] =
{
    8,-3, 9,5/*mean (0), correlation (0)*/,
    4,2, 7,-12/*mean (1.12461e-05), correlation (0.0437584)*/,
    -11,9, -8,2/*mean (3.37382e-05), correlation (0.0617409)*/,
    7,-12, 12,-13/*mean (5.62303e-05), correlation (0.0636977)*/,
    2,-13, 2,12/*mean (0.000134953), correlation (0.085099)*/,
    1,-7, 1,6/*mean (0.000528565), correlation (0.0857175)*/,
    -2,-10, -2,-4/*mean (0.0188821), correlation (0.0985774)*/,
    -13,-13, -11,-8/*mean (0.0363135), correlation (0.0899616)*/,
    -13,-3, -12,-9/*mean (0.121806), correlation (0.099849)*/,
    10,4, 11,9/*mean (0.122065), correlation (0.093285)*/,
    -13,-8, -8,-9/*mean (0.162787), correlation (0.0942748)*/,
    -11,7, -9,12/*mean (0.21561), correlation (0.0974438)*/,
    7,7, 12,6/*mean (0.160583), correlation (0.130064)*/,
    -4,-5, -3,0/*mean (0.228171), correlation (0.132998)*/,
    -13,2, -12,-3/*mean (0.00997526), correlation (0.145926)*/,
    -9,0, -7,5/*mean (0.198234), correlation (0.143636)*/,
    12,-6, 12,-1/*mean (0.0676226), correlation (0.16689)*/,
    -3,6, -2,12/*mean (0.166847), correlation (0.171682)*/,
    -6,-13, -4,-8/*mean (0.101215), correlation (0.179716)*/,
    11,-13, 12,-8/*mean (0.200641), correlation (0.192279)*/,
    4,7, 5,1/*mean (0.205106), correlation (0.186848)*/,
    5,-3, 10,-3/*mean (0.234908), correlation (0.192319)*/,
    3,-7, 6,12/*mean (0.0709964), correlation (0.210872)*/,
    -8,-7, -6,-2/*mean (0.0939834), correlation (0.212589)*/,
    -2,11, -1,-10/*mean (0.127778), correlation (0.20866)*/,
    -13,12, -8,10/*mean (0.14783), correlation (0.206356)*/,
    -7,3, -5,-3/*mean (0.182141), correlation (0.198942)*/,
    -4,2, -3,7/*mean (0.188237), correlation (0.21384)*/,
    -10,-12, -6,11/*mean (0.14865), correlation (0.23571)*/,
    5,-12, 6,-7/*mean (0.222312), correlation (0.23324)*/,
    5,-6, 7,-1/*mean (0.229082), correlation (0.23389)*/,
    1,0, 4,-5/*mean (0.241577), correlation (0.215286)*/,
    9,11, 11,-13/*mean (0.00338507), correlation (0.251373)*/,
    4,7, 4,12/*mean (0.131005), correlation (0.257622)*/,
    2,-1, 4,4/*mean (0.152755), correlation (0.255205)*/,
    -4,-12, -2,7/*mean (0.182771), correlation (0.244867)*/,
    -8,-5, -7,-10/*mean (0.186898), correlation (0.23901)*/,
    4,11, 9,12/*mean (0.226226), correlation (0.258255)*/,
    0,-8, 1,-13/*mean (0.0897886), correlation (0.274827)*/,
    -13,-2, -8,2/*mean (0.148774), correlation (0.28065)*/,
    -3,-2, -2,3/*mean (0.153048), correlation (0.283063)*/,
    -6,9, -4,-9/*mean (0.169523), correlation (0.278248)*/,
    8,12, 10,7/*mean (0.225337), correlation (0.282851)*/,
    0,9, 1,3/*mean (0.226687), correlation (0.278734)*/,
    7,-5, 11,-10/*mean (0.00693882), correlation (0.305161)*/,
    -13,-6, -11,0/*mean (0.0227283), correlation (0.300181)*/,
    10,7, 12,1/*mean (0.125517), correlation (0.31089)*/,
    -6,-3, -6,12/*mean (0.131748), correlation (0.312779)*/,
    10,-9, 12,-4/*mean (0.144827), correlation (0.292797)*/,
    -13,8, -8,-12/*mean (0.149202), correlation (0.308918)*/,
    -13,0, -8,-4/*mean (0.160909), correlation (0.310013)*/,
    3,3, 7,8/*mean (0.177755), correlation (0.309394)*/,
    5,7, 10,-7/*mean (0.212337), correlation (0.310315)*/,
    -1,7, 1,-12/*mean (0.214429), correlation (0.311933)*/,
    3,-10, 5,6/*mean (0.235807), correlation (0.313104)*/,
    2,-4, 3,-10/*mean (0.00494827), correlation (0.344948)*/,
    -13,0, -13,5/*mean (0.0549145), correlation (0.344675)*/,
    -13,-7, -12,12/*mean (0.103385), correlation (0.342715)*/,
    -13,3, -11,8/*mean (0.134222), correlation (0.322922)*/,
    -7,12, -4,7/*mean (0.153284), correlation (0.337061)*/,
    6,-10, 12,8/*mean (0.154881), correlation (0.329257)*/,
    -9,-1, -7,-6/*mean (0.200967), correlation (0.33312)*/,
    -2,-5, 0,12/*mean (0.201518), correlation (0.340635)*/,
    -12,5, -7,5/*mean (0.207805), correlation (0.335631)*/,
    3,-10, 8,-13/*mean (0.224438), correlation (0.34504)*/,
    -7,-7, -4,5/*mean (0.239361), correlation (0.338053)*/,
    -3,-2, -1,-7/*mean (0.240744), correlation (0.344322)*/,
    2,9, 5,-11/*mean (0.242949), correlation (0.34145)*/,
    -11,-13, -5,-13/*mean (0.244028), correlation (0.336861)*/,
    -1,6, 0,-1/*mean (0.247571), correlation (0.343684)*/,
    5,-3, 5,2/*mean (0.000697256), correlation (0.357265)*/,
    -4,-13, -4,12/*mean (0.00213675), correlation (0.373827)*/,
    -9,-6, -9,6/*mean (0.0126856), correlation (0.373938)*/,
    -12,-10, -8,-4/*mean (0.0152497), correlation (0.364237)*/,
    10,2, 12,-3/*mean (0.0299933), correlation (0.345292)*/,
    7,12, 12,12/*mean (0.0307242), correlation (0.366299)*/,
    -7,-13, -6,5/*mean (0.0534975), correlation (0.368357)*/,
    -4,9, -3,4/*mean (0.099865), correlation (0.372276)*/,
    7,-1, 12,2/*mean (0.117083), correlation (0.364529)*/,
    -7,6, -5,1/*mean (0.126125), correlation (0.369606)*/,
    -13,11, -12,5/*mean (0.130364), correlation (0.358502)*/,
    -3,7, -2,-6/*mean (0.131691), correlation (0.375531)*/,
    7,-8, 12,-7/*mean (0.160166), correlation (0.379508)*/,
    -13,-7, -11,-12/*mean (0.167848), correlation (0.353343)*/,
    1,-3, 12,12/*mean (0.183378), correlation (0.371916)*/,
    2,-6, 3,0/*mean (0.228711), correlation (0.371761)*/,
    -4,3, -2,-13/*mean (0.247211), correlation (0.364063)*/,
    -1,-13, 1,9/*mean (0.249325), correlation (0.378139)*/,
    7,1, 8,-6/*mean (0.000652272), correlation (0.411682)*/,
    1,-1, 3,12/*mean (0.00248538), correlation (0.392988)*/,
    9,1, 12,6/*mean (0.0206815), correlation (0.386106)*/,
    -1,-9, -1,3/*mean (0.0364485), correlation (0.410752)*/,
    -13,-13, -10,5/*mean (0.0376068), correlation (0.398374)*/,
    7,7, 10,12/*mean (0.0424202), correlation (0.405663)*/,
    12,-5, 12,9/*mean (0.0942645), correlation (0.410422)*/,
    6,3, 7,11/*mean (0.1074), correlation (0.413224)*/,
    5,-13, 6,10/*mean (0.109256), correlation (0.408646)*/,
    2,-12, 2,3/*mean (0.131691), correlation (0.416076)*/,
    3,8, 4,-6/*mean (0.165081), correlation (0.417569)*/,
    2,6, 12,-13/*mean (0.171874), correlation (0.408471)*/,
    9,-12, 10,3/*mean (0.175146), correlation (0.41296)*/,
    -8,4, -7,9/*mean (0.183682), correlation (0.402956)*/,
    -11,12, -4,-6/*mean (0.184672), correlation (0.416125)*/,
    1,12, 2,-8/*mean (0.191487), correlation (0.386696)*/,
    6,-9, 7,-4/*mean (0.192668), correlation (0.394771)*/,
    2,3, 3,-2/*mean (0.200157), correlation (0.408303)*/,
    6,3, 11,0/*mean (0.204588), correlation (0.411762)*/,
    3,-3, 8,-8/*mean (0.205904), correlation (0.416294)*/,
    7,8, 9,3/*mean (0.213237), correlation (0.409306)*/,
    -11,-5, -6,-4/*mean (0.243444), correlation (0.395069)*/,
    -10,11, -5,10/*mean (0.247672), correlation (0.413392)*/,
    -5,-8, -3,12/*mean (0.24774), correlation (0.411416)*/,
    -10,5, -9,0/*mean (0.00213675), correlation (0.454003)*/,
    8,-1, 12,-6/*mean (0.0293635), correlation (0.455368)*/,
    4,-6, 6,-11/*mean (0.0404971), correlation (0.457393)*/,
    -10,12, -8,7/*mean (0.0481107), correlation (0.448364)*/,
    4,-2, 6,7/*mean (0.050641), correlation (0.455019)*/,
    -2,0, -2,12/*mean (0.0525978), correlation (0.44338)*/,
    -5,-8, -5,2/*mean (0.0629667), correlation (0.457096)*/,
    7,-6, 10,12/*mean (0.0653846), correlation (0.445623)*/,
    -9,-13, -8,-8/*mean (0.0858749), correlation (0.449789)*/,
    -5,-13, -5,-2/*mean (0.122402), correlation (0.450201)*/,
    8,-8, 9,-13/*mean (0.125416), correlation (0.453224)*/,
    -9,-11, -9,0/*mean (0.130128), correlation (0.458724)*/,
    1,-8, 1,-2/*mean (0.132467), correlation (0.440133)*/,
    7,-4, 9,1/*mean (0.132692), correlation (0.454)*/,
    -2,1, -1,-4/*mean (0.135695), correlation (0.455739)*/,
    11,-6, 12,-11/*mean (0.142904), correlation (0.446114)*/,
    -12,-9, -6,4/*mean (0.146165), correlation (0.451473)*/,
    3,7, 7,12/*mean (0.147627), correlation (0.456643)*/,
    5,5, 10,8/*mean (0.152901), correlation (0.455036)*/,
    0,-4, 2,8/*mean (0.167083), correlation (0.459315)*/,
    -9,12, -5,-13/*mean (0.173234), correlation (0.454706)*/,
    0,7, 2,12/*mean (0.18312), correlation (0.433855)*/,
    -1,2, 1,7/*mean (0.185504), correlation (0.443838)*/,
    5,11, 7,-9/*mean (0.185706), correlation (0.451123)*/,
    3,5, 6,-8/*mean (0.188968), correlation (0.455808)*/,
    -13,-4, -8,9/*mean (0.191667), correlation (0.459128)*/,
    -5,9, -3,-3/*mean (0.193196), correlation (0.458364)*/,
    -4,-7, -3,-12/*mean (0.196536), correlation (0.455782)*/,
    6,5, 8,0/*mean (0.1972), correlation (0.450481)*/,
    -7,6, -6,12/*mean (0.199438), correlation (0.458156)*/,
    -13,6, -5,-2/*mean (0.211224), correlation (0.449548)*/,
    1,-10, 3,10/*mean (0.211718), correlation (0.440606)*/,
    4,1, 8,-4/*mean (0.213034), correlation (0.443177)*/,
    -2,-2, 2,-13/*mean (0.234334), correlation (0.455304)*/,
    2,-12, 12,12/*mean (0.235684), correlation (0.443436)*/,
    -2,-13, 0,-6/*mean (0.237674), correlation (0.452525)*/,
    4,1, 9,3/*mean (0.23962), correlation (0.444824)*/,
    -6,-10, -3,-5/*mean (0.248459), correlation (0.439621)*/,
    -3,-13, -1,1/*mean (0.249505), correlation (0.456666)*/,
    7,5, 12,-11/*mean (0.00119208), correlation (0.495466)*/,
    4,-2, 5,-7/*mean (0.00372245), correlation (0.484214)*/,
    -13,9, -9,-5/*mean (0.00741116), correlation (0.499854)*/,
    7,1, 8,6/*mean (0.0208952), correlation (0.499773)*/,
    7,-8, 7,6/*mean (0.0220085), correlation (0.501609)*/,
    -7,-4, -7,1/*mean (0.0233806), correlation (0.496568)*/,
    -8,11, -7,-8/*mean (0.0236505), correlation (0.489719)*/,
    -13,6, -12,-8/*mean (0.0268781), correlation (0.503487)*/,
    2,4, 3,9/*mean (0.0323324), correlation (0.501938)*/,
    10,-5, 12,3/*mean (0.0399235), correlation (0.494029)*/,
    -6,-5, -6,7/*mean (0.0420153), correlation (0.486579)*/,
    8,-3, 9,-8/*mean (0.0548021), correlation (0.484237)*/,
    2,-12, 2,8/*mean (0.0616622), correlation (0.496642)*/,
    -11,-2, -10,3/*mean (0.0627755), correlation (0.498563)*/,
    -12,-13, -7,-9/*mean (0.0829622), correlation (0.495491)*/,
    -11,0, -10,-5/*mean (0.0843342), correlation (0.487146)*/,
    5,-3, 11,8/*mean (0.0929937), correlation (0.502315)*/,
    -2,-13, -1,12/*mean (0.113327), correlation (0.48941)*/,
    -1,-8, 0,9/*mean (0.132119), correlation (0.467268)*/,
    -13,-11, -12,-5/*mean (0.136269), correlation (0.498771)*/,
    -10,-2, -10,11/*mean (0.142173), correlation (0.498714)*/,
    -3,9, -2,-13/*mean (0.144141), correlation (0.491973)*/,
    2,-3, 3,2/*mean (0.14892), correlation (0.500782)*/,
    -9,-13, -4,0/*mean (0.150371), correlation (0.498211)*/,
    -4,6, -3,-10/*mean (0.152159), correlation (0.495547)*/,
    -4,12, -2,-7/*mean (0.156152), correlation (0.496925)*/,
    -6,-11, -4,9/*mean (0.15749), correlation (0.499222)*/,
    6,-3, 6,11/*mean (0.159211), correlation (0.503821)*/,
    -13,11, -5,5/*mean (0.162427), correlation (0.501907)*/,
    11,11, 12,6/*mean (0.16652), correlation (0.497632)*/,
    7,-5, 12,-2/*mean (0.169141), correlation (0.484474)*/,
    -1,12, 0,7/*mean (0.169456), correlation (0.495339)*/,
    -4,-8, -3,-2/*mean (0.171457), correlation (0.487251)*/,
    -7,1, -6,7/*mean (0.175), correlation (0.500024)*/,
    -13,-12, -8,-13/*mean (0.175866), correlation (0.497523)*/,
    -7,-2, -6,-8/*mean (0.178273), correlation (0.501854)*/,
    -8,5, -6,-9/*mean (0.181107), correlation (0.494888)*/,
    -5,-1, -4,5/*mean (0.190227), correlation (0.482557)*/,
    -13,7, -8,10/*mean (0.196739), correlation (0.496503)*/,
    1,5, 5,-13/*mean (0.19973), correlation (0.499759)*/,
    1,0, 10,-13/*mean (0.204465), correlation (0.49873)*/,
    9,12, 10,-1/*mean (0.209334), correlation (0.49063)*/,
    5,-8, 10,-9/*mean (0.211134), correlation (0.503011)*/,
    -1,11, 1,-13/*mean (0.212), correlation (0.499414)*/,
    -9,-3, -6,2/*mean (0.212168), correlation (0.480739)*/,
    -1,-10, 1,12/*mean (0.212731), correlation (0.502523)*/,
    -13,1, -8,-10/*mean (0.21327), correlation (0.489786)*/,
    8,-11, 10,-6/*mean (0.214159), correlation (0.488246)*/,
    2,-13, 3,-6/*mean (0.216993), correlation (0.50287)*/,
    7,-13, 12,-9/*mean (0.223639), correlation (0.470502)*/,
    -10,-10, -5,-7/*mean (0.224089), correlation (0.500852)*/,
    -10,-8, -8,-13/*mean (0.228666), correlation (0.502629)*/,
    4,-6, 8,5/*mean (0.22906), correlation (0.498305)*/,
    3,12, 8,-13/*mean (0.233378), correlation (0.503825)*/,
    -4,2, -3,-3/*mean (0.234323), correlation (0.476692)*/,
    5,-13, 10,-12/*mean (0.236392), correlation (0.475462)*/,
    4,-13, 5,-1/*mean (0.236842), correlation (0.504132)*/,
    -9,9, -4,3/*mean (0.236977), correlation (0.497739)*/,
    0,3, 3,-9/*mean (0.24314), correlation (0.499398)*/,
    -12,1, -6,1/*mean (0.243297), correlation (0.489447)*/,
    3,2, 4,-8/*mean (0.00155196), correlation (0.553496)*/,
    -10,-10, -10,9/*mean (0.00239541), correlation (0.54297)*/,
    8,-13, 12,12/*mean (0.0034413), correlation (0.544361)*/,
    -8,-12, -6,-5/*mean (0.003565), correlation (0.551225)*/,
    2,2, 3,7/*mean (0.00835583), correlation (0.55285)*/,
    10,6, 11,-8/*mean (0.00885065), correlation (0.540913)*/,
    6,8, 8,-12/*mean (0.0101552), correlation (0.551085)*/,
    -7,10, -6,5/*mean (0.0102227), correlation (0.533635)*/,
    -3,-9, -3,9/*mean (0.0110211), correlation (0.543121)*/,
    -1,-13, -1,5/*mean (0.0113473), correlation (0.550173)*/,
    -3,-7, -3,4/*mean (0.0140913), correlation (0.554774)*/,
    -8,-2, -8,3/*mean (0.017049), correlation (0.55461)*/,
    4,2, 12,12/*mean (0.01778), correlation (0.546921)*/,
    2,-5, 3,11/*mean (0.0224022), correlation (0.549667)*/,
    6,-9, 11,-13/*mean (0.029161), correlation (0.546295)*/,
    3,-1, 7,12/*mean (0.0303081), correlation (0.548599)*/,
    11,-1, 12,4/*mean (0.0355151), correlation (0.523943)*/,
    -3,0, -3,6/*mean (0.0417904), correlation (0.543395)*/,
    4,-11, 4,12/*mean (0.0487292), correlation (0.542818)*/,
    2,-4, 2,1/*mean (0.0575124), correlation (0.554888)*/,
    -10,-6, -8,1/*mean (0.0594242), correlation (0.544026)*/,
    -13,7, -11,1/*mean (0.0597391), correlation (0.550524)*/,
    -13,12, -11,-13/*mean (0.0608974), correlation (0.55383)*/,
    6,0, 11,-13/*mean (0.065126), correlation (0.552006)*/,
    0,-1, 1,4/*mean (0.074224), correlation (0.546372)*/,
    -13,3, -9,-2/*mean (0.0808592), correlation (0.554875)*/,
    -9,8, -6,-3/*mean (0.0883378), correlation (0.551178)*/,
    -13,-6, -8,-2/*mean (0.0901035), correlation (0.548446)*/,
    5,-9, 8,10/*mean (0.0949843), correlation (0.554694)*/,
    2,7, 3,-9/*mean (0.0994152), correlation (0.550979)*/,
    -1,-6, -1,-1/*mean (0.10045), correlation (0.552714)*/,
    9,5, 11,-2/*mean (0.100686), correlation (0.552594)*/,
    11,-3, 12,-8/*mean (0.101091), correlation (0.532394)*/,
    3,0, 3,5/*mean (0.101147), correlation (0.525576)*/,
    -1,4, 0,10/*mean (0.105263), correlation (0.531498)*/,
    3,-6, 4,5/*mean (0.110785), correlation (0.540491)*/,
    -13,0, -10,5/*mean (0.112798), correlation (0.536582)*/,
    5,8, 12,11/*mean (0.114181), correlation (0.555793)*/,
    8,9, 9,-6/*mean (0.117431), correlation (0.553763)*/,
    7,-4, 8,-12/*mean (0.118522), correlation (0.553452)*/,
    -10,4, -10,9/*mean (0.12094), correlation (0.554785)*/,
    7,3, 12,4/*mean (0.122582), correlation (0.555825)*/,
    9,-7, 10,-2/*mean (0.124978), correlation (0.549846)*/,
    7,0, 12,-2/*mean (0.127002), correlation (0.537452)*/,
    -1,-6, 0,-11/*mean (0.127148), correlation (0.547401)*/
};

/*****************************************************私有函数*****************************************************/
//计算模板圆周像素和中心像素的坐标偏移
void cornerExtraction::makeOffsets(int pixel[25], int rowStride)
{
	//定义一个数组，用于表示圆周上16个像素对于圆心的相对坐标位置  
	static const int offsets16[][2] =
	{
		{0,  3}, { 1,  3}, { 2,  2}, { 3,  1}, { 3, 0}, { 3, -1}, { 2, -2}, { 1, -3},
		{0, -3}, {-1, -3}, {-2, -2}, {-3, -1}, {-3, 0}, {-3,  1}, {-2,  2}, {-1,  3}
	};
	//代入输入图像每行的像素个数，得到圆周像素的绝对坐标位置
	int k = 0;
	for( ; k < 16; k++ )
		pixel[k] = offsets16[k][0] + offsets16[k][1] * rowStride;
	for( ; k < 25; k++ )//由于要计算连续的像素，因此要循环的多列出一些值
		pixel[k] = pixel[k - 16];
}
//计算得分函数，它的值是特征点与其圆周上16个像素点的绝对差值中所有连续10个像素中的最小值的最大值，而且该值还要大于阈值threshold
int cornerExtraction::cornerScore(const uchar* ptr, const int pixel[], int threshold)
{
	const int K = 8, N = 25;
	int k, v = ptr[0];//v为当前像素值 582 --- 106

	short d[N];
	//计算当前像素值与其圆周像素值之间的差值
	for( k = 0; k < N; k++ )
		d[k] = (short)(v - ptr[pixel[k]]);
	int a0 = threshold;
	//满足角点条件2时，更新阈值
	for( k = 0; k < 16; k += 2 )
	{
		int a = min((int)d[k+1], (int)d[k+2]);
        	a = min(a, (int)d[k+3]);
		if( a <= a0 )
			continue;
		a = min(a, (int)d[k+4]);
		a = min(a, (int)d[k+5]);
		a = min(a, (int)d[k+6]);
		a = min(a, (int)d[k+7]);
		a = min(a, (int)d[k+8]);
		a0= max(a0, min(a, (int)d[k]));
		a0= max(a0, min(a, (int)d[k+9]));
	}
	//满足角点条件1时，更新阈值
	int b0 = -a0;
	for( k = 0; k < 16; k += 2 )
	{
		int b = max((int)d[k+1], (int)d[k+2]);
        	b = max(b, (int)d[k+3]);
        	b = max(b, (int)d[k+4]);
        	b = max(b, (int)d[k+5]);
		if( b >= b0 )
			continue;
		b = max(b, (int)d[k+6]);
        	b = max(b, (int)d[k+7]);
        	b = max(b, (int)d[k+8]);
		b0= min(b0, max(b, (int)d[k]));
		b0= min(b0, max(b, (int)d[k+9]));
	}
	threshold = -b0-1;
	return threshold;//更新后的阈值作为输出 
}
//计算某fast角点7*7邻域内协方差矩阵的最小值
void cornerExtraction::fastCornerMinEigenVal(const Mat& inputimg, const vector<Point>& fastcorners, Mat& eigen)
{
	float sobelX,sobelY;
	float covzero,covone,covtwo;
	float eigenvmax;
	float eigennum;
	int xcoord,ycoord;
	float cov[147];//存放各像素(49*3)的协方差元素值:IX2，IXIY,IY2
	int pointsnum=fastcorners.size();
	int xgoodsize=imgwidth-4;
	int ygoodsize=imgheight-4;
	for(int i=0;i<pointsnum;i++)
	{
		int x=fastcorners[i].x;
		int y=fastcorners[i].y;
		if((x>3 && x<xgoodsize) && (y>3 && y<ygoodsize))
		{
			int xgap=3;
			int ygap=3;
			int count=0;
			eigennum=0;
			eigenvmax=0;
			//计算fast角点7*7邻域的协方差矩阵
			int ycurrent = y-ygap;//当前行
			int xcurrcoord=x-xgap;//当前像素的x坐标
			for(int j=0;j<49;j++)
			{
				int ypre = ycurrent-1;//上一行
				int ynext = ycurrent+1;//下一行
				int xleftcoord=xcurrcoord-1;
				int xrightcoord=xcurrcoord+1;
				const uchar* previous=inputimg.ptr<const uchar>(ypre);//当前角点上一行的首地址
				const uchar* current=inputimg.ptr<const uchar>(ycurrent);//当前角点当前行的首地址
				const uchar* next=inputimg.ptr<const uchar>(ynext);//当前角点下一行的首地址
				sobelX=(previous[xrightcoord]-previous[xleftcoord])+2*(current[xrightcoord]-current[xleftcoord])+(next[xrightcoord]-next[xleftcoord]);
				sobelY=(next[xleftcoord]+2*next[xcurrcoord]+next[xrightcoord])-(previous[xleftcoord]+2*previous[xcurrcoord]+previous[xrightcoord]);
				cov[count*3]=sobelX*sobelX;
				cov[count*3+1]=sobelX*sobelY;
				cov[count*3+2]=sobelY*sobelY;
				++count;
				++xcurrcoord;
				if(count%7==0)
				{
					xcurrcoord=x-xgap;
					++ycurrent;
				}
			}
			//盒状滤波器求和
			xgap=2;
			ygap=2;
			count=0;
			ycurrent = y-ygap;//当前行
			xcurrcoord=x-xgap;//当前像素的x坐标
			int online=0;//确定当前处理的为哪一行像素
			for(int m=0;m<25;m++)
			{
				int basecoord=7*online+count;
				covzero=0.5f*(cov[(basecoord)*3]+cov[(basecoord+1)*3]+cov[(basecoord+2)*3]+cov[(basecoord+7)*3]+cov[(basecoord+8)*3]+
						cov[(basecoord+9)*3]+cov[(basecoord+14)*3]+cov[(basecoord+15)*3]+cov[(basecoord+16)*3]);
				covone=cov[(basecoord)*3+1]+cov[(basecoord+1)*3+1]+cov[(basecoord+2)*3+1]+cov[(basecoord+7)*3+1]+
						cov[(basecoord+8)*3+1]+cov[(basecoord+9)*3+1]+cov[(basecoord+14)*3+1]+
						cov[(basecoord+15)*3+1]+cov[(basecoord+16)*3+1];
				covtwo=0.5f*(cov[(basecoord)*3+2]+cov[(basecoord+1)*3+2]+cov[(basecoord+2)*3+2]+cov[(basecoord+7)*3+2]+
						cov[(basecoord+8)*3+2]+cov[(basecoord+9)*3+2]+cov[(basecoord+14)*3+2]+cov[(basecoord+15)*3+2]+
						cov[(basecoord+16)*3+2]);
				eigennum= (float)((covzero + covtwo) - sqrt((covzero - covtwo)*(covzero - covtwo) + covone*covone));
				++count;
				if(eigennum>eigenvmax)
				{
					eigenvmax=eigennum;
					xcoord=xcurrcoord;
					ycoord=ycurrent;
				}
				++xcurrcoord;
				if(count==5)
				{
					count=0;
					++online;
					xcurrcoord=x-xgap;
					++ycurrent;
				}
			}
			float* eigendata = (float*)(eigen.data +eigen.step*ycoord);
			eigendata[xcoord]=eigenvmax;
		}
	}
}

//计算图像上所有角点的主方向
void cornerExtraction::pointAngle(const Mat& inputimage, vector<KeyPoint>& corners)
{
    vector<KeyPoint> tempkp;
    tempkp.clear();
    int j=0;
    //模板圆每行像素长度一半值的确定
    int patchSize=31;
    int halfPatchSize = patchSize/2;
#if USE_SIMPLIFY
    int umax[17]={15,15,15,15,14,14,14,13,13,12,11,10,9,8,6,3,0};
#else
    int umax[halfPatchSize];//umax存储圆模板每行长度的一半
    int v, v0, vmax=cvFloor(halfPatchSize*sqrt(2.f)/2+1);//Rounds floating-point number to the nearest integer not larger than the original
    int vmin=cvCeil(halfPatchSize*sqrt(2.f)/2);//Rounds floating-point number to the nearest integer not smaller than the original
    for(v=0; v<=vmax; ++v)
        umax[v]=cvRound(sqrt((double)halfPatchSize*halfPatchSize-v*v));// 计算圆模板每行的长度一半
    // Make sure we are symmetric
    for(v=halfPatchSize, v0=0; v>=vmin; --v)
    {
        while(umax[v0] == umax[v0+1])
            ++v0;
        umax[v]=v0;
        ++v0;
    }
#endif
    int pointnumber=corners.size();//角点总数目
    //cout<<"pointnumber is: "<<pointnumber<<endl;
    for(int i=0; i<pointnumber;i++)
    {
        if((corners[i].pt.x > halfPatchSize) && (corners[i].pt.x < inputimage.cols-halfPatchSize) && 
                (corners[i].pt.y > halfPatchSize) && (corners[i].pt.x < inputimage.rows-halfPatchSize))
        {
            //统计模板圆内的m01,m10值
            int m_01=0, m_10=0;
            const uchar* center=&inputimage.at<uchar>(corners[i].pt.y, corners[i].pt.x);//center指向存储当前像素灰度值的地址
            //Treat the center line differently, v=0
            //cout<<"hello--1"<<endl;
            for(int u=-halfPatchSize; u<=halfPatchSize; ++u)
                m_10+=u*center[u];//统计v=0行的m10值，m01的值为0
            //Go line by line in the circular patch
            int step=(int)inputimage.step1();
            //cout<<"hello--2"<<endl;
            for(int v=1; v<=halfPatchSize; ++v)
            {
                //Proceed over the two lines
                int v_sum=0;
                int d=umax[v];
                    for(int u=-d; u<=d; ++u)
                {
                    //圆模板对称，统计上下部分的m10和m01值
                    int val_plus=center[u+v*step], val_minus=center[u-v*step];
                    v_sum+=(val_plus-val_minus);
                    m_10+=u*(val_plus+val_minus);//统计其他行的m10值
                }
                m_01+=v*v_sum;//统计m01值
            }
            //cout<<"hello--4"<<endl;
            //利用m01,m10计算该角点的方向
            float ax=abs(m_10), ay=abs(m_01);
            float result, c , c2;
            if(ax>=ay)
            {
                c=ay/(ax+(float)DBL_EPSILON);
                c2=c*c;
                result=(((atan2_p7*c2 + atan2_p5)*c2 + atan2_p3)*c2 + atan2_p1)*c;
            }   
            else
            {
                c=ax/(ay+(float)DBL_EPSILON);
                c2=c*c;
                result=90.f-(((atan2_p7*c2 + atan2_p5)*c2 + atan2_p3)*c2 + atan2_p1)*c;
            }
            if(m_10<0)
                result=180.f-result;
            if(m_01<0)
                result=360.f-result;
            corners[i].angle=result;
            tempkp.push_back(corners[i]);
            //cout<<"hello--4"<<endl;
        }
    }
    corners.clear();
    corners=tempkp;
    //cout<<"hello--3"<<endl;
}

/*****************************************************公有函数*****************************************************/
//获取fast角点
void cornerExtraction::fastCornerDetect(const Mat &inputimg, vector<Point>& fastcorners, int threshold)
{

	//cout<<"fast___1"<<endl;

	fastcorners.clear();
	bool nonmax_suppression=true;//进行非极大值抑制
	//K为圆周连续像素的个数,N用于循环圆周的像素点，因为要首尾连接，所以N要比实际圆周像素数量多K+1个  
	const int K = 8, N = 25;
	int i, j, k, pixel[25];
	makeOffsets(pixel, (int)inputimg.step);//找到圆周像素点相对于圆心的偏移量
	threshold = min(max(threshold, 0), 255);//保证阈值不大于255，不小于0
	uchar threshold_tab[512];//threshold_tab为阈值列表，在进行阈值比较的时候，只需查该表即可
	/* 
		阈值列表赋值，该表分为三段： 
		第一段从threshold_tab[0]至threshold_tab[255 - threshold]，值为1，落在该区域的值表示满足角点判断条件： 
			集合S由圆周上N个连续的像素x组成，Ix < Ip - t； 
		第二段从threshold_tab[255 – threshold]至threshold_tab[255 + threshold]，值为0，落在该区域的值表示不是角点； 
		第三段从threshold_tab[255 + threshold]至threshold_tab[511]，值为2，落在该区域的值表示满足角点判断条件： 
			集合S由圆周上N个连续的像素x组成，Ix > Ip + t； 
	*/
	for( i = -255; i <= 255; i++ )
        	threshold_tab[i+255] = (uchar)(i < -threshold ? 1 : i > threshold ? 2 : 0);

	//cout<<"fast___2"<<endl;

	AutoBuffer<uchar> _buf(imgwidth*3*(sizeof(int) + sizeof(uchar)));//开辟一段内存空间
	uchar* buf[3];
	/*
		buf[0、buf[1]和buf[2]分别表示图像的前一行、当前行和后一行。因为在非极大值抑制的步骤2中，是要在3×3的角点邻域内
		进行比较，因此需要三行的图像数据。因为只有得到了当前行的数据，所以对于上一行来说，才凑够了连续三行的数据，因此输出
		的非极大值抑制的结果是上一行数据的处理结果.
	*/ 
	buf[0] = _buf; buf[1] = buf[0] + imgwidth; buf[2] = buf[1] + imgwidth;
	int* cpbuf[3];//cpbuf存储角点的坐标位置，也是需要连续三行的数据
	cpbuf[0] = (int*)alignPtr(buf[2] + imgwidth, sizeof(int)) + 1;//+1腾出一个位置存放角点的数目：cornerpos[-1] = ncorners;
	cpbuf[1] = cpbuf[0] + imgwidth + 1;
	cpbuf[2] = cpbuf[1] + imgwidth + 1;
	memset(buf[0], 0, imgwidth*3);//buf数组内存清零
	//由于圆的半径为3个像素，因此图像的四周边界都留出3个像素的宽度
	//由于要计算特征点的ORB特征，需要考虑31*31邻域
	//for(i = 3; i < imgheight-2; i++)
	//cout<<"fast___3"<<endl;
	for(i = 31; i < imgheight-30; i++)
	{
		const uchar* ptr = inputimg.ptr<uchar>(i) + 31;//得到图像行的首地址指针
		uchar* curr = buf[(i - 31)%3];//得到buf的某个数组，用于存储当前行的得分函数的值V
		int* cornerpos = cpbuf[(i - 31)%3];//得到cpbuf的某个数组，用于存储当前行的角点坐标位置
		memset(curr, 0, imgwidth);
		int ncorners = 0;
		if(i < imgheight-31)
		{
			j = 31;
			//for( ; j < imgwidth - 3; j++, ptr++ )
			for( ; j < imgwidth-31; j++, ptr++ )
			{
				int v = ptr[0];//当前像素的灰度值
				const uchar* tab = &threshold_tab[0] - v + 255;//由当前像素的灰度值，确定其在阈值列表中的位置
				int d = tab[ptr[pixel[0]]] | tab[ptr[pixel[8]]];
				/*
					pixel[0]表示圆周上编号为0的像素相对于圆心坐标的偏移量,ptr[pixel[0]表示圆周上编号为0的像素值;
					tab[ptr[pixel[0]]]表示相对于当前像素（即圆心）圆周上编号为0的像素值在阈值列表threshold_tab中所查询得到的值;
					如果为1，说明I0 < Ip - t，如果为2，说明I0 > Ip + t，如果为0，说明 Ip – t < I0 < Ip + t。因此通过tab，就可以得到当前像素是否满足角点条件;
				*/
                		/*
					编号为0和8（即直径在圆周上的两个像素点）在列表中的值相或后得到d。d=0说明编号为0和8的值都是0；d=1说明编号为0和8的值至少有一个为1，而另一个不能为2；
					d=2说明编号为0和8的值至少有一个为2，而另一个不能为1；d=3说明编号为0和8的值有一个为1，另一个为2。只可能有这四种情况
				*/
				if( d == 0 )
					continue;
				//d=0说明圆周上不可能有连续12个像素满足角点条件，因此当前值一定不是角点，所以退出此次循环，进入下一次循环 
				d &= tab[ptr[pixel[2]]] | tab[ptr[pixel[10]]];
				d &= tab[ptr[pixel[4]]] | tab[ptr[pixel[12]]];
				d &= tab[ptr[pixel[6]]] | tab[ptr[pixel[14]]];

				if( d == 0 )
					continue;
				//继续进行其他直径上两个像素点的判断 
				d &= tab[ptr[pixel[1]]] | tab[ptr[pixel[9]]];
				d &= tab[ptr[pixel[3]]] | tab[ptr[pixel[11]]];
				d &= tab[ptr[pixel[5]]] | tab[ptr[pixel[13]]];
				d &= tab[ptr[pixel[7]]] | tab[ptr[pixel[15]]];

				if( d & 1 )//如果满足if条件，则说明有可能满足角点条件2
				{
					int vt = v - threshold, count = 0; //vt为真正的角点条件，即Ip – t，count为连续像素的计数值
					for( k = 0; k < N; k++ )//遍历整个圆周
					{
						int x = ptr[pixel[k]];//提取出圆周上的像素值
						if(x < vt)//如果满足条件2
						{
							if( ++count > K )//连续计数，并判断是否大于K（K为圆周像素的一半）
							{
								//进入该if语句，说明已经得到一个角点,保存该点的位置，并把当前行的角点数加1
								cornerpos[ncorners++] = j;
								if(nonmax_suppression)//进行非极大值抑制的第一步，计算得分函数
									curr[j] = (uchar)cornerScore(ptr, pixel, threshold);
  								break;
							}
						}
						else
							count = 0;
					}
				}
				if( d & 2 )//如果满足if条件，则说明有可能满足角点条件1
				{
					int vt = v + threshold, count = 0;//vt为真正的角点条件，即Ip + t，count为连续像素的计数值
					for( k = 0; k < N; k++ )
					{
						int x = ptr[pixel[k]];
						if(x > vt)
						{
							if( ++count > K )
							{
								cornerpos[ncorners++] = j;
								if(nonmax_suppression)
									curr[j] = (uchar)cornerScore(ptr, pixel, threshold);
								break;
							}
						}
						else
							count = 0;//连续像素的计数值清零
					}
				}
			}
		}
		//保存当前行所检测到的角点数 
		cornerpos[-1] = ncorners;
		//i=3说明只仅仅计算了一行的数据，还不能进行非极大值抑制的第二步，所以不进行下面代码的操作，直接进入下一次循环

		if( i == 31 )
			continue;
		/*
			以下代码是进行非极大值抑制的第二步，即在3×3的角点邻域内对得分函数的值进行非极大值抑制。
			因为经过上面代码的计算，已经得到了当前行的数据，所以可以进行上一行的非极大值抑制。因此下面的代码进行的是上一行的非极大值抑制。
		*/
		//提取出上一行和上两行的图像像素

		const uchar* prev = buf[(i - 29)%3];//32-3
		const uchar* pprev = buf[(i - 30)%3];//33-3
		//提取出上一行所检测到的角点位置
		cornerpos = cpbuf[(i - 29)%3];
		//提取出上一行的角点数 
        	ncorners = cornerpos[-1];
		//在上一行内遍历整个检测到的角点
        	for( k = 0; k < ncorners; k++ )
		{
			j = cornerpos[k];//得到角点的位置
			int score = prev[j];//得到该角点的得分函数值
			//在3×3的角点邻域内，计算当前角点是否为最大值
			if( !nonmax_suppression || (score > prev[j+1] && score > prev[j-1] &&
                		score > pprev[j-1] && score > pprev[j] && score > pprev[j+1] && score > curr[j-1] && score > curr[j] && score > curr[j+1]) )
			{
				fastcorners.push_back(Point(j,i-1));
			}
        }
	}
	//cout<<"fast___3"<<endl;
}
//Shi-Tomasi实现
void cornerExtraction::shiTomasiDetect(const Mat& inputimg, const vector<Point>& fastcorners,vector<Point2f>& point, vector<KeyPoint>& corners, int maxCorners, int minDistance)
{
	//cout<<"tomasi___1"<<endl;
	Mat eig(imgheight, imgwidth, CV_32FC1,Scalar(0));
	//cout<<"tomasi___2"<<endl;
	fastCornerMinEigenVal(inputimg, fastcorners, eig);
	//cout<<"tomasi___3"<<endl;
	int height=imgheight-4;
	int width=imgwidth-4;
	vector<const float*> tmpCorners;//存放粗选出的角点地址
	for( int y = 4; y <= height; y++ )
	{
		const float* eig_data = (const float*)eig.ptr(y);
		for( int x = 4; x <= width; x++ )
		{
			float val = eig_data[x];
			if(val!= 0)
				tmpCorners.push_back(eig_data + x);//保存其位置
		}
	}
	//cout<<"tomasi___4"<<endl;
	sort(tmpCorners.begin(),tmpCorners.end(), greaterThanPtr());//按特征值降序排列
	//cout<<"tomasi___5"<<endl;
	int i, j, total = tmpCorners.size(), ncorners = 0;
	if(minDistance >= 1)
	{
		// Partition the image into larger grids
		const int cell_size = minDistance;
		// 根据cell_size构建了一个矩形窗口grid，除以cell_size说明grid窗口里相差一个像素相当于_image里相差minDistance个像素
		const int grid_width = (imgwidth + cell_size - 1) / cell_size;
		const int grid_height = (imgheight + cell_size - 1) / cell_size;

		vector< vector<Point2f> > grid(grid_width*grid_height);// grid用来保存获得的强角点坐标 
		minDistance *= minDistance;//平方，方面后面计算，省的开根号
		//cout<<"tomasi___6"<<endl;
  		for( i = 0; i < total; i++ )// 刚刚粗选的弱角点，都要到这里来接收新一轮的考验
		{
			int ofs = (int)((const uchar*)tmpCorners[i] - eig.data);//tmpCorners中保存了角点的地址，eig.data返回eig内存块的首地址  
			int y = (int)(ofs / eig.step);//角点在原图像中的行
			int x = (int)((ofs - y*eig.step)/sizeof(float));//在原图像中的列

			bool good = true;//先认为当前角点能接收考验，即能被保留下来

			int x_cell = x / cell_size;//x_cell，y_cell是角点（y,x）在grid中的对应坐标
			int y_cell = y / cell_size;
	    		/* grid_width定义时要加上cell_size - 1，这是为了使得（y,x）在grid中的4邻域像素都存在，也就是说(y_cell，x_cell）不会成为边界像素 */ 
            		int x1 = x_cell - 1;//(y_cell，x_cell）的4邻域像素 
            		int y1 = y_cell - 1;
            		int x2 = x_cell + 1;
            		int y2 = y_cell + 1;
	    		// boundary check，再次确认x1,y1,x2或y2不会超出grid边界
            		x1 = max(0, x1);
            		y1 = max(0, y1);
            		x2 = min(grid_width-1, x2);
            		y2 = min(grid_height-1, y2);

            		//记住grid中相差一个像素，相当于_image中相差了minDistance个像素
            		for( int yy = y1; yy <= y2; yy++ )
			{
                		for( int xx = x1; xx <= x2; xx++ )
                		{
                    			vector <Point2f> &m = grid[yy*grid_width + xx];
                    			if( m.size() )//如果(y_cell，x_cell)的4邻域像素，也就是(y,x)的minDistance邻域像素中已有被保留的强角点
                    			{
                        			for(j = 0; j < m.size(); j++)//当前角点周围的强角点都拉出来跟当前角点比一比
                        			{
							float dx = x - m[j].x;
							float dy = y - m[j].y;
                           				/*注意如果(y,x)的minDistance邻域像素中已有被保留的强角点，则说明该强角点是在(y,x)之前就被测试过的，
			      				  又因为tmpCorners中已按照特征值降序排列（特征值越大说明角点越好），这说明先测试的一定是更好的角点，
                             				 也就是已保存的强角点一定好于当前角点，所以这里只要比较距离，如果距离满足条件，可以立马扔掉当前测试的角点*/  		
							if(dx*dx + dy*dy < minDistance)
							{
								good = false;
								goto break_out;
							}
						}
					}
				}
			}
			break_out:
			if(good)
			{
				grid[y_cell*grid_width + x_cell].push_back(Point2f((float)x, (float)y));
                point.push_back(Point2f((float)x, (float)y));
				corners.push_back(KeyPoint(Point2f((float)x, (float)y), 0, -1, 0, 0, -1));
				++ncorners;
				//由于前面已按降序排列，当ncorners超过maxCorners的时候跳出循环直接忽略tmpCorners中剩下的角点，反正剩下的角点越来越弱
				if( maxCorners > 0 && (int)ncorners == maxCorners )
					break;
			}
		}
		//cout<<"tomasi___7"<<endl;
	}
	else   //除了像素本身，没有哪个邻域像素能与当前像素满足minDistance < 1,因此直接保存粗选的角点
	{
		for( i = 0; i < total; i++ )
        	{
			int ofs = (int)((const uchar*)tmpCorners[i] - eig.data);
			int y = (int)(ofs / eig.step);//粗选的角点在原图像中的行
			int x = (int)((ofs - y*eig.step)/sizeof(float));
			corners.push_back(KeyPoint(Point2f((float)x, (float)y), 0, -1, 0, 0, -1));
			++ncorners;
			if( maxCorners > 0 && (int)ncorners == maxCorners )
				break;
		}
		//cout<<"tomasi___8"<<endl;
	}
}
//获取fast&Shi-Tomasi角点
void cornerExtraction::fastWithTomasiDetect(const Mat &inputimg, vector<KeyPoint>& corners, vector<Point2f>& point,int threshold, int maxCorners, int minDistance)
{
	vector<Point> fastcorners;
	fastCornerDetect(inputimg, fastcorners, threshold);
	shiTomasiDetect(inputimg, fastcorners, point,corners, maxCorners, minDistance);
}
//计算图像上每个角点的描述符

void cornerExtraction::computeOrbDescriptors(const Mat& inputimg, KeyPoint& corners, uchar* descriptors)
{
	//cout<<"hello1"<<endl;
	//pointAngle(inputimg, corners);
	//cout<<"hello2"<<endl;
	
	//cout<<"number i is: "<<i<<endl;
	//cout<<"Point is: "<<corners[i].pt.x<<"  "<<corners[i].pt.y<<endl;
	//uchar* desc=descriptors+32;
	const Point* patternpt = (const Point*)pattern_opencv;//训练好的256对数据点位置,通过查表来计算
	float angle = corners.angle;//特征点的主方向
	angle*=(float)(CV_PI/180.f);
	float a=(float)cos(angle), b=(float)sin(angle);
	const uchar* center = &inputimg.at<uchar>(corners.pt.y, corners.pt.x);
	int step=(int)inputimg.step;
	float x, y;
	int ix, iy;
	#define GET_VALUE(idx) \
		(x=patternpt[idx].x*a-patternpt[idx].y*b, \
		 y=patternpt[idx].x*b+patternpt[idx].y*a, \
		 ix=cvRound(x), \
		 iy=cvRound(y), \
		 *(center+iy*step+ix))//读取旋转后的图像灰度值
	//cout<<"ix and iy "<<ix<<"  "<<iy<<endl;
	//每个特征描述子长度为32个字节,样式集合内两点比较，循环一次得到一字节描述符，共循环32次
	for (int j=0; j<32; ++j, patternpt+=16)
	{
		int t0, t1, val;
		t0 = GET_VALUE(0); t1 = GET_VALUE(1);
		val = t0 < t1;
		t0 = GET_VALUE(2); t1 = GET_VALUE(3);
		val |= (t0 < t1) << 1;
		t0 = GET_VALUE(4); t1 = GET_VALUE(5);
		val |= (t0 < t1) << 2;
		t0 = GET_VALUE(6); t1 = GET_VALUE(7);
		val |= (t0 < t1) << 3;
		t0 = GET_VALUE(8); t1 = GET_VALUE(9);
		val |= (t0 < t1) << 4;
		t0 = GET_VALUE(10); t1 = GET_VALUE(11);
		val |= (t0 < t1) << 5;
		t0 = GET_VALUE(12); t1 = GET_VALUE(13);
		val |= (t0 < t1) << 6;
		t0 = GET_VALUE(14); t1 = GET_VALUE(15);
		val |= (t0 < t1) << 7;
		descriptors[j] = (uchar)val;//把获得的brief特征通过desc返回
	}
		#undef GET_VALUE
	
	//cout<<"hello3"<<endl;
}

void cornerExtraction::computeDescriptors(const Mat& inputimg, vector<KeyPoint>& keycorners, Mat& descriptors)
{
    pointAngle(inputimg, keycorners);
    descriptors = Mat::zeros((int)keycorners.size(), 32, CV_8UC1);

    for (size_t i = 0; i < keycorners.size(); i++)
        computeOrbDescriptors(inputimg, keycorners[i], descriptors.ptr((int)i));
}

void cornerExtraction::getFitCorners(const Mat &img,  vector<KeyPoint> &kpCorners, Mat& descriptors, int &cornererror)
{
    int threshold=10;
    int size=0;
    int thresholdcount=0;
    //图像FAST角点提取阈值确定
    vector<Point> corners;
   
    if(!img.empty())
    {
        while(1)//fast角点检测
        {
            //cout<<"do fast detect!"<<endl;
            fastCornerDetect(img, corners, threshold);
            //cout<<"hehe fast corners size is: "<<corners.size()<<endl;
            thresholdcount++;
            size=corners.size();
            if(thresholdcount>=3)
            {
                //cout<<"fast threshold is: "<<threshold<<endl;
                //cout<<"fast corners size is: "<<corners.size()<<endl;
                break;
            }
            if(size>=200 && size<=500)
            {
                //cout<<"fast threshold is: "<<threshold<<endl;
                //cout<<"fast corners size is: "<<corners.size()<<endl;
                break;
            }
            else if(size<=50)
                threshold-=5;
            else if(50<size && size<200)
                threshold-=5;
            else if(size>=1000)
                threshold+=5;
            else if(500<size && size<1000)
                threshold+=5;
        }
        vector<Point2f> pointa;
        shiTomasiDetect(img, corners, pointa, kpCorners, 100, 15);//Shi-Tomasi角点检测
        cout<<"image corners size is: "<<kpCorners.size()<<endl;
        if(kpCorners.size()<=20)
        {
            cornererror=-1;
            cout<<"Can not find enough corners!"<<endl;
        }
        else
        {
            computeDescriptors(img, kpCorners, descriptors);//计算图像上每个角点的描述符
            //cout<<"Have done computeDescriptors"<<endl;

        }
    }
    else
    {
        cornererror=-1;
        cout<<"the image is empty!"<<endl;
    }
}