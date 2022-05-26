#pragma once
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>

#define Pi 3.14

using namespace std;
using namespace cv;

/*
Lớp biểu diễn pháp biến đổi affine
*/
class AffineTransform
{
	Mat _matrixTransform;//ma trận 3x3 biểu diễn phép biến đổi affine
public:
	void Translate(float dx, float dy);// xây dựng matrix transform cho phép tịnh tiến theo vector (dx,dy)
	void Rotate(float angle);//xây dựng matrix transform cho phép xoay 1 góc angle
	void Scale(float sx, float sy);//xây dựng matrix transform cho phép tỉ lệ theo hệ số 		
	void TransformPoint(float& x, float& y);//transform 1 điểm (x,y) theo matrix transform đã có

	AffineTransform()
	{
		_matrixTransform = Mat::eye(3, 3, CV_32FC1);
	}
	~AffineTransform()
	{

	}
};