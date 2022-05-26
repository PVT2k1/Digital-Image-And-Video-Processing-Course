#pragma once
#include "Convolution.h"
#include <math.h>

#define PI 3.14

class Blur
{
public:
	/*
	Hàm làm trơn ảnh xám
	sourceImage: ảnh input
	destinationImage: ảnh output
	method: phương pháp detect
	kWidth, kHeight: kích thước kernel
	0: Trung bình
	1: Trung vị
	2: Gaussian
	Hàm trả về
	0: nếu detect thành công
	1: nếu detect thất bại (không đọc được ảnh input,...)
	*/
	int BlurImage(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method);
	
	//sắp xếp không giảm (tăng dần) các phần tử thuộc kiểu uchar trong vector data
	void sortIncrease(vector<uchar>& data);

	Blur() { }

	~Blur() { }
};

int convertCharToInt(char* c);