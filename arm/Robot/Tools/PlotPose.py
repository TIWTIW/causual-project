#! /usr/bin/python3
# -*- coding: UTF-8 -*-

import sys
import re
import numpy as np
import matplotlib.pyplot as plt

# Read the file and return the list of Vision Pose
def read_VisionPose(filename):
	fs = open(filename,'r') # open the <filename> to read
	text = fs.read() # read all the contents
	regexValidLine = r'Confused Pose(.*)[0-9](.*)'
	numReg = r'[+-]?\d+\.?\d*'
	x = []
	y = []
	theta = []
	for line in text.split('\n'):
		matchObj = re.search(regexValidLine, line)
		if matchObj:
			validLine = matchObj.group()
			pose = re.findall(numReg, validLine)
			#print(pose)
			if len(pose)==3:
				x.append(pose[0])
				y.append(pose[1])
				theta.append(pose[2])
	return x,y,theta

# Read the file and return the list of IMU Pose
def read_IMUPose(filename):
	fs = open(filename,'r') # open the <filename> to read
	text = fs.read() # read all the contents
	regexValidLine = r'IMU Pose New(.*)[0-9](.*)'
	numReg = r'[+-]?\d+\.?\d*'
	x = []
	y = []
	theta = []
	for line in text.split('\n'):
		matchObj = re.search(regexValidLine, line)
		if matchObj:
			validLine = matchObj.group()
			pose = re.findall(numReg, validLine)
			#print(pose)
			if len(pose)==3:
				x.append(pose[0])
				y.append(pose[1])
				theta.append(pose[2])
	return x,y,theta
# Read the file and return the list of IMU Pose
def read_IMUPose2(filename):
	fs = open(filename,'r') # open the <filename> to read
	text = fs.read() # read all the contents
	regexValidLine = r'(.*)[0-9](.*)'
	numReg = r'[+-]?\d+\.?\d*'
	x = []
	y = []
	theta = []
	for line in text.split('\n'):
		matchObj = re.search(regexValidLine, line)
		if matchObj:
			validLine = matchObj.group()
			pose = re.findall(numReg, validLine)
			#print(pose)
			if len(pose)==3:
				x.append(pose[0])
				y.append(pose[1])
				theta.append(pose[2])
			if len(pose)==4:
				x.append(pose[1])
				y.append(pose[2])
				theta.append(pose[3])
	return x,y,theta



# Read the file and return the list of Kalman Pose
def read_KalmanPose(filename):
	fs = open(filename,'r') # open the <filename> to read
	text = fs.read() # read all the contents
	regexValidLine = r'Kalman Pose(.*)[0-9](.*)'
	numReg = r'[+-]?\d+\.?\d*'
	x = []
	y = []
	theta = []
	for line in text.split('\n'):
		matchObj = re.search(regexValidLine, line)
		if matchObj:
			validLine = matchObj.group()
			pose = re.findall(numReg, validLine)
			#print(pose)
			if len(pose)==3:
				x.append(pose[0])
				y.append(pose[1])
				theta.append(pose[2])
	return x,y,theta

if __name__ == '__main__':
	print("Program Name: ", sys.argv[0])
	if len(sys.argv) != 3 :
		print("Usage: PlotPose <logfile_IMU> <logfile_Confuse>")
		sys.exit(-1)
	filename1 = sys.argv[1]
	filename2 = sys.argv[2]
	print("reading file: ", filename1, filename2)
	#x1,y1,t1 = read_VisionPose(filename)
	#x2,y2,t2 = read_KalmanPose(filename)
	x0,y0,t0 = read_IMUPose2(filename1)
	x1,y1,t1 = read_VisionPose(filename2)
	x2,y2,t2 = read_KalmanPose(filename2)
	x3,y3,t3 = read_IMUPose(filename2)
	#plt.plot(x1, y1, 'ro', label='Vision')
	#plt.plot(x2, y2, 'b^', label='Kalman')
	#plt.plot(x3, y3, 'g', label='IMU')
	plt.plot(x0, y0, 'r', linewidth=2.0, label="path his")
	plt.plot(x1, y1, 'b^', label='vision pose')
	plt.plot(x1, y1, 'b')
	plt.plot(x2, y2, 'gs', label='kalman pose')
	plt.plot(x2, y2, 'g')
	plt.plot(x3, y3, 'ro', label='IMU pose')
	plt.grid(True)
	plt.legend(loc='best')
	#plt.axis([-500,500,500,500])
	plt.show()
	