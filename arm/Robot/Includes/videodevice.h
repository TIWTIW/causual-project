/*------------------------------------------------------------------------------------------*\
	功能描述：
		使用V4L2控制USB摄像头从YUV422视频流中提取Y分量得到灰度视频；
	输入参数：
		Linux设备描述符,帧率(帧/秒)；
	输出参数：
		Mat类型的灰度视频；
	(注：帧率控制需要摄像头的支持。)
\*------------------------------------------------------------------------------------------*/
#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H

#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <opencv2/features2d/features2d.hpp>
using namespace std;
using namespace cv;
#define CLEAR(x) memset(&(x), 0, sizeof(x))

class videoDevice
{
	public:
		videoDevice(const char *devname, int fps);
		~videoDevice();
		int init();
		int getExposureValue();
		void changeExposureValue(int value);
		void setExposureMode(int i);
        Mat getVideoFrameTop();
		Mat getVideoFrameFront();
		int hasinit;//1表示已经初始化了，0表示未初始化
	private:
       		int openDevice();
        	int initDevice();
        	int startCapturing();
        	int initMmap();
        	int stopCapturing();
		int uninitDevice();
		int closeDevice();
                void freeDevice();
		int getFrame(void **frame_buf, unsigned int *len);
		int ungetFrame();
        	struct buffer
        	{
			void *start;
			unsigned int length;
		};
                
        	const char *devname;//Linux设备描述符
        	int fd;
		int fps;//采集帧率
        	buffer *buffers;
        	unsigned int n_buffers;
        	int index;
		int convertYuvToGreyBufferTop(unsigned char *yuv, unsigned char *grey, unsigned int width, unsigned int height);
                int convertYuvToGreyBufferFront(unsigned char *yuv, unsigned char *grey, unsigned int width, unsigned int height);
        	unsigned char  *pptop;//指向灰度图的指针
                unsigned char  *ppfront;//指向灰度图的指针
        	Mat frametop;//返回的灰度图
                Mat framefront;//返回的灰度图
};

#endif // VIDEODEVICE_H
