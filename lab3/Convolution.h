#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <vector>

using namespace std;
using namespace cv;

class Convolution
{
	vector<float> _kernel;// lưu giá trị của ma trận kernel dùng để tích chập
	int _kernelWidth;//chiều rộng kernel
	int _kernelHeight;//chiều dài kernel
public:
	//trả về kernel 
	vector<float> GetKernel()
	{
		return _kernel;
	}

	//set kernel, chiều rộng, chiều dài kernel phải là số lẻ
	void SetKernel(vector<float> kernel, int kWidth, int kHeight)
	{
		_kernelWidth = kWidth;
		_kernelHeight = kHeight;

		int n = kWidth * kHeight;
		for (int i = 0; i < n; i++)
		{
			_kernel.push_back(kernel[i]);
		}
	}

	/*
	Hàm tính convolution của 1 ảnh xám với kernel được xác định trước
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu tính thành công
	1: nếu tính thất bại (không đọc được ảnh input,...)
	*/
	int DoConvolution(const Mat& sourceImage, Mat& destinationImage);

	Convolution()
	{
		_kernelWidth = _kernelHeight = 0;
		_kernel = { };
	}

	~Convolution()
	{

	}
};

