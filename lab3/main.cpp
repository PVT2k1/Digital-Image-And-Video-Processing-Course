//#include "Convolution.h"
//#include "Blur.h"
//#include "EdgeDetector.h"
//
//int main(int arg, char* argv[])
//{
//	cout << "Program: " << argv[0] << "\n";
//
//	//blur: trung bình, trung vị, gauss
//	if (arg == 6)
//	{
//		//xử lý ảnh đầu vào
//		Mat srcImage = imread(argv[4], IMREAD_ANYCOLOR);
//		if (!srcImage.data)
//		{
//			cout << "Read image failed!\n";
//			return 0;
//		}
//
//		if (srcImage.channels() == 3)
//		{
//			cout << "Input is a Color image, then convert to gray_scale\n";
//			srcImage = imread(argv[4], IMREAD_GRAYSCALE);
//		}
//
//		int kx = convertCharToInt(argv[2]);
//		int ky = convertCharToInt(argv[3]);
//
//		Mat dstImage;
//		Blur blur;
//		if ((string)argv[1] == "-avg")
//		{
//			if (blur.BlurImage(srcImage, dstImage, kx, ky, 0) == 1)
//			{
//				cout << "ERROR!";
//				return 0;
//			}
//			else cout << "Detect successfully\n";
//		}
//
//		else if ((string)argv[1] == "-med")
//		{
//			if (blur.BlurImage(srcImage, dstImage, kx, ky, 1) == 1)
//			{
//				cout << "ERROR!";
//				return 0;
//			}
//			else cout << "Detect successfully\n";
//		}
//
//		else if ((string)argv[1] == "-gau")
//		{
//			if (blur.BlurImage(srcImage, dstImage, kx, ky, 2) == 1)
//			{
//				cout << "ERROR!";
//				return 0;
//			}
//			else cout << "Detect successfully\n";
//		}
//
//		else
//		{
//			cout << "If enter 6 parameters, the second parameter must be '-avg' or '-med' or '-gau'\n";
//			return 0;
//		}
//		imwrite(argv[5], dstImage);
//	}
//
//	//edge detector: sobel, prewitt
//	else if (arg == 4)
//	{
//		//xử lý ảnh đầu vào
//		Mat srcImage = imread(argv[2], IMREAD_ANYCOLOR);
//		if (!srcImage.data)
//		{
//			cout << "Read image failed!\n";
//			return 0;
//		}
//		if (srcImage.channels() == 3)
//		{
//			cout << "Input is a Color image, then convert to gray_scale\n";
//			srcImage = imread(argv[2], IMREAD_GRAYSCALE);
//		}
//
//		Mat dstImage;
//		EdgeDetector e;
//		if ((string)argv[1] == "-sobel")
//		{
//			if (e.DetectEdge(srcImage, dstImage, 0) == 1)
//			{
//				cout << "ERROR!";
//				return 0;
//			}
//			else cout << "Detect successfully\n";
//		}
//
//		else if ((string)argv[1] == "-prew")
//		{
//			if (e.DetectEdge(srcImage, dstImage, 1) == 1)
//			{
//				cout << "ERROR!";
//				return 0;
//			}
//			else cout << "Detect successfully\n";
//		}
//
//		else
//		{
//			cout << "If enter 4 parameters, the second parameter must be '-sobel' or '-prew'\n";
//			return 0;
//		}
//		imwrite(argv[3], dstImage);
//	}
//
//	else
//	{
//		cout << "Must enter 4 or 6 parameters\n";
//		return 0;
//	}
//}

#include <iostream>
#include <Windows.h>

int main()
{
	SYSTEM_INFO infor;
	GetSystemInfo(&infor);
	std::cout << infor.dwPageSize;
	return 0;
}