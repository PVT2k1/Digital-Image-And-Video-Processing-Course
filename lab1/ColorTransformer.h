#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

class ColorTransformer
{
public:
	/*
	Hàm thay đổi độ sáng của 1 ảnh và lưu kết quả vào 1 ảnh khác
	Tham số:
		sourceImage	: ảnh đầu vào
		destinationImage: ảnh kết quả
		b	: giá trị số nguyên để thay đổi độ sáng của ảnh
	Hàm trả về:
		1: Nếu thành công thì trả về ảnh kết quả
		0: Nếu lỗi: Không tạo được ảnh kết quả hoặc ảnh input bị lỗi
	*/
	int ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, short b);

	/*
	Hàm thay đổi độ tương phản của 1 ảnh và lưu kết quả vào 1 ảnh khác
	Tham số:
		sourceImage	: ảnh đầu vào
		destinationImage: ảnh kết quả
		c	: giá trị số nguyên để thay đổi độ tương phản của ảnh
	Hàm trả về:
		1: Nếu thành công thì trả về ảnh kết quả
		0: Nếu lỗi: Không tạo được ảnh kết quả hoặc ảnh input bị lỗi
	*/
	int ChangeContrast(const Mat& sourceImage, Mat& destinationImage, float c);


	/*
	Hàm tính lược đồ màu tổng quát cho ảnh bất kỳ
	Tham số:
		sourceImage : ảnh đầu vào
		histMatrix : ma trận histogram (nChannels x 256), mỗi dòng là 1 mảng 256 phần tử histogram của từng kênh màu
	Hàm trả về:
		1: Nếu thành công thì trả về matrix kết quả (ảnh gốc vẫn giữ nguyên giá trị)
		0: Nếu không tính được histogram hoặc ảnh input không tồn tại
	*/
	int CalcHistogram(const Mat& sourceImage, Mat& histMatrix);

	/*
	Hàm cân bằng lược đồ màu tổng quát cho ảnh bất kỳ
	Tham so :
		histMatrix : ma trận histogram đã tính được
		histImage : ảnh histogram được vẽ
	Hàm trả về:
		1: Nếu thành công vẽ được histogram
		0: Nếu không vẽ được histogram
	*/
	int DrawHistogram(const Mat& histMatrix, Mat& histImage);

	ColorTransformer()
	{

	}
	~ColorTransformer()
	{

	}
};

//chuyển từ kiểu char* sang kiểu short
short convertCharToShort(char* c);

//chuyển từ kiểu char* sang kiểu float
float convertCharToFloat(char* c);