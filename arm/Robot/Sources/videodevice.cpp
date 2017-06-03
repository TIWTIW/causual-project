#include "videodevice.h"
videoDevice::videoDevice(const char *devname, int fps)
{
	this->devname = devname;
	this->fd = -1;
	this->buffers = NULL;
	this->n_buffers = 0;
	this->index = -1;
	this->fps=fps;
	cout<<"We will directly extract Y component from YUV422!"<<endl;
	pptop = (unsigned char *)malloc(640 * 480 * 1 * sizeof(unsigned char));
        ppfront=(unsigned char *)malloc(640 * 240* 1 * sizeof(unsigned char));
	framefront.create(240,640,CV_8UC1);
        frametop.create(480,640,CV_8UC1);
	hasinit=0;
}
videoDevice::~videoDevice()
{
	freeDevice();
}
void videoDevice::freeDevice()
{
	stopCapturing();
	uninitDevice();
	closeDevice();
	cout<<"Free USB Camera sucess."<<endl;
}
int videoDevice::init()
{
	if(openDevice()== -1)
	{
		cout<<"Open device failed!"<<endl;
		return -1;
	}
	if(initDevice()== -1)
	{
		cout<<"Init device failed!"<<endl;
		return -1;
	}
	if(startCapturing()== -1)
	{
		cout<<"Start capturing failed!"<<endl;
		return -1;
	}
    hasinit=1;
	return 0;
}
int videoDevice::openDevice()//打开设备
{
	fd = open(devname, O_RDWR, 0);
	if(fd== -1)
	{
		cout<<"Error opening V4L2 interface!"<<endl;
		return -1;
	}
	return 0;
}
int videoDevice::closeDevice()//关闭设备
{
	close(fd);
	free(pptop);
        free(ppfront);
	return 0;
}
int videoDevice::initDevice()
{
	v4l2_capability cap;
	v4l2_format fmt;
	v4l2_streamparm setfps;
	v4l2_fmtdesc fmtdesc;
	if(ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
	{
		cout<<"Unable to query device: "<<devname<<"!"<<endl;
		return -1;
	}
	else
	{
		cout<<"driver: "<<cap.driver<<endl;
		cout<<"card: "<<cap.card<<endl;
		cout<<"bus_info: "<<cap.bus_info<<endl;
		cout<<"version: "<<cap.version<<endl;
        	cout<<"capability ties: "<<cap.capabilities<<endl;
        	if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
        	{
            		cout<<"Device "<<devname<<" supports capture."<<endl;
        	}
        	if ((cap.capabilities & V4L2_CAP_STREAMING))
        	{
			cout<<"Device "<<devname<<" supports streaming."<<endl;
        	}
	}
        // 列举摄像头所支持像素格式
    fmtdesc.index=0;
    fmtdesc.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	cout<<"Support format: "<<endl;
    while(ioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc)!=-1)
    {
	cout<<fmtdesc.index+1<<"."<<fmtdesc.description<<endl;
	fmtdesc.index++;
    }
	// 设置帧格式colormode
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.height = 480;
	fmt.fmt.pix.width = 640;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	if(ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
	{
		cout<<"Unable to set format!"<<endl;
		return -1;
	}
	if(ioctl(fd, VIDIOC_G_FMT, &fmt) == -1)
	{
		cout<<"Unable to get format!"<<endl;
		return -1;
	}
	// 设置帧率
	setfps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	setfps.parm.capture.timeperframe.numerator = 1;
	setfps.parm.capture.timeperframe.denominator = fps;
	if(ioctl(fd, VIDIOC_S_PARM, &setfps) == -1)
	{
		cout<<"Unable to set frame rate!"<<endl;
		return -1;
	}
	else
		cout<<"Set fps OK!"<<endl;
	if(ioctl(fd, VIDIOC_G_PARM, &setfps) == -1)
	{
		cout<<"Unable to get frame rate!"<<endl;
		return -1;
	}
	else
	{
		cout<<"Get fps OK!"<<endl;
		cout<<"Timeperframe.numerator: "<<setfps.parm.capture.timeperframe.numerator<<";"<<endl;
		cout<<"Timeperframe.denominator: "<<setfps.parm.capture.timeperframe.denominator<<";"<<endl;
	}
	/*ctrl.id=V4L2_CID_EXPOSURE_AUTO;
	if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)!=-1)
	{
		cout<<"exposure mode="<<ctrl.value<<endl;
	}
	ctrl.id=V4L2_CID_EXPOSURE_ABSOLUTE;
	if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)!=-1)
	{
		cout<<"exposure value="<<ctrl.value<<endl;
	}
	
	v4l2_queryctrl ctrlset;
	ctrlset.id=V4L2_CID_EXPOSURE_AUTO;
	if(ioctl(fd,VIDIOC_QUERYCTRL,&ctrlset)!=-1)
	{
		cout<<"exposure mode:"<<endl;
		cout<<"type="<<ctrlset.type<<endl;
		cout<<"name="<<ctrlset.name<<endl;
		cout<<"minimum="<<ctrlset.minimum<<endl;
		cout<<"maximum="<<ctrlset.maximum<<endl;
		cout<<"step="<<ctrlset.step<<endl;
		cout<<"default_value"<<ctrlset.default_value<<endl;
		cout<<"flag="<<ctrlset.flags<<endl;
	}
	ctrlset.id=V4L2_CID_EXPOSURE_ABSOLUTE;
	if(ioctl(fd,VIDIOC_QUERYCTRL,&ctrlset)!=-1)
	{
		cout<<"exposure value:"<<endl;
		cout<<"type="<<ctrlset.type<<endl;
		cout<<"name="<<ctrlset.name<<endl;
		cout<<"minimum="<<ctrlset.minimum<<endl;
		cout<<"maximum="<<ctrlset.maximum<<endl;
		cout<<"step="<<ctrlset.step<<endl;
		cout<<"default_value"<<ctrlset.default_value<<endl;
		cout<<"flag="<<ctrlset.flags<<endl;
	}*/
	/*ctrl.id=V4L2_CID_EXPOSURE_ABSOLUTE;
	ctrl.value=90;
	if(ioctl(fd,VIDIOC_S_CTRL,&ctrl)==-1)
	{
		cout<<"set exposure value error"<<endl;
	}*/
	
	// 内存映射mmap
	if(initMmap()== -1 )
	{
		cout<<"Cannot mmap!"<<endl;
		return -1;
	}
	return 0;
}
void videoDevice::setExposureMode(int i)
{
	// 1 hand set; 3--auto set
	v4l2_control ctrl;
	ctrl.id=V4L2_CID_EXPOSURE_AUTO;
	ctrl.value=i;
	if(ioctl(fd,VIDIOC_S_CTRL,&ctrl)==-1)
	{
		cout<<"set exposure MODE error"<<endl;
	}
	if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)!=-1)
	{
		cout<<"exposure mode="<<ctrl.value<<endl;
	}
}
int  videoDevice::getExposureValue()
{
	v4l2_control ctrl;
	ctrl.id=V4L2_CID_EXPOSURE_ABSOLUTE;
	if(ioctl(fd,VIDIOC_G_CTRL,&ctrl)!=-1)
	{
		//cout<<"exposure value="<<ctrl.value<<endl;
		return ctrl.value;
	}
	else 
		return -1;
}
void videoDevice::changeExposureValue(int value)
{
	v4l2_control ctrl;
	ctrl.id=V4L2_CID_EXPOSURE_ABSOLUTE;
	ctrl.value=value;
	if(ioctl(fd,VIDIOC_S_CTRL,&ctrl)==-1)
	{
		cout<<"set exposure value error"<<endl;
	}
}
int videoDevice::initMmap()//初始化内存映射
{
	v4l2_requestbuffers req;//向系统申请帧缓冲的请求，包括申请的个数
	CLEAR(req);
	req.count = 1;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	if(ioctl(fd, VIDIOC_REQBUFS, &req)== -1)
	{
		cout<<"VIDIOC_REQBUFS ERROR!"<<endl;
		return -1;
	}
	buffers = (buffer*)calloc(req.count, sizeof(*buffers));
	if(!buffers)
	{
		cout<<"Insufficient buffer memory!"<<endl;
		return -1;
	}
	for(n_buffers = 0; n_buffers < req.count; ++n_buffers)
	{
		v4l2_buffer buf;//驱动中的一帧
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;
		if(ioctl(fd, VIDIOC_QUERYBUF, &buf)== -1)
		{
			cout<<"VIDIOC_QUERYBUF ERROR!"<<endl;
			return -1;
		}
        	/*建立驱动缓冲到内存的映射*/
        	buffers[n_buffers].length = buf.length;
        	buffers[n_buffers].start = //建立内存映射
        	mmap(NULL,buf.length,PROT_READ | PROT_WRITE,MAP_SHARED,fd, buf.m.offset);
        	if(MAP_FAILED == buffers[n_buffers].start)//映射失败
            		return -1;
	}
	return 0;
}
int videoDevice::startCapturing()
{
	unsigned int i;
	for(i = 0; i < n_buffers; ++i)
	{
		v4l2_buffer buf;
        CLEAR(buf);
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory =V4L2_MEMORY_MMAP;
        buf.index = i;
		ioctl(fd, VIDIOC_QBUF, &buf);
	}
	v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(fd, VIDIOC_STREAMON, &type)== -1)
		return -1;
	return 0;
}
int videoDevice::stopCapturing()
{
	v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(fd, VIDIOC_STREAMOFF, &type)== -1)
		return -1;
	return 0;
}
int videoDevice::uninitDevice()
{
	unsigned int i;
	for(i = 0; i < n_buffers; ++i)
	{
		munmap(buffers[i].start, buffers[i].length);
	}
	free(buffers);
	return 0;
}

int videoDevice::getFrame(void **frame_buf, unsigned int *len)
{
	v4l2_buffer queue_buf;
	CLEAR(queue_buf);
	queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	queue_buf.memory = V4L2_MEMORY_MMAP;
	ioctl(fd, VIDIOC_DQBUF, &queue_buf);
	*frame_buf = buffers[queue_buf.index].start;
	*len = buffers[queue_buf.index].length;
	index = queue_buf.index;
	return 0;
}
int videoDevice::ungetFrame()
{
	if(index != -1)
	{
        	v4l2_buffer queue_buf;
       		CLEAR(queue_buf);
        	queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        	queue_buf.memory = V4L2_MEMORY_MMAP;
        	queue_buf.index = index;
		ioctl(fd, VIDIOC_QBUF, &queue_buf);
        	return 0;
    	}
	else
		return -1;
}
int videoDevice::convertYuvToGreyBufferTop(unsigned char *yuv, unsigned char *grey, unsigned int width, unsigned int height)
{
	unsigned int in, out = 0;
	for(in = 0; in < width * height * 2; in += 4)
	{
 		grey[out++]=yuv[in];
		grey[out++]=yuv[in+2];
	}
	return 0;
}
int videoDevice::convertYuvToGreyBufferFront(unsigned char *yuv, unsigned char *grey, unsigned int width, unsigned int height)
{
	unsigned int in, out = 0;
	for(in = width * height; in < width * height * 2; in += 4)
	{
 		grey[out++]=yuv[in];
		grey[out++]=yuv[in+2];
	}
	return 0;
}

Mat videoDevice::getVideoFrameTop()
{
    if(hasinit==1)
    {
        uchar *p;
	unsigned int len;
	this->getFrame((void**)&p,&len);
	this->convertYuvToGreyBufferTop(p,pptop,640,480);
	memcpy(frametop.data, (uchar*)pptop, 640 * 480 *1* sizeof(unsigned char));
	ungetFrame();
	return frametop;
    }
    else
    {
        cout<<"don't ust getVideoFrameTop() before init()"<<endl;
        exit(-1);
    }
}

Mat videoDevice::getVideoFrameFront()
{
    if(hasinit==1)
    {
	uchar *p;
	unsigned int len;
	this->getFrame((void**)&p,&len);
        this->convertYuvToGreyBufferFront(p,ppfront,640,480);
	memcpy(framefront.data, (uchar*)ppfront, 640 * 240 *1* sizeof(unsigned char));
	ungetFrame();
	return framefront;
    }
    else
    {
        cout<<"dong't use getVideoFrameFront() before init()"<<endl;
        exit(-1);
    }
}
