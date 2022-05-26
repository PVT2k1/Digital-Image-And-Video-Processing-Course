#include "EdgeDetector.h"

int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int method)
{
	if (!sourceImage.data)
		return 1;
	int srcChannels = sourceImage.channels();
	//nếu không phải ảnh xám
	if (srcChannels != 1)
		return 1;

	destinationImage = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());

	//bộ lọc Sobel
	if (method == 0)
	{
		//phương pháp này đạo hàm bậc nhất theo 2 phương x (theo chiều dọc) và y (theo chiều ngang)
		vector<float>Wx = { 1,0,-1,2,0,-2,1,0,-1 };
		vector<float>Wy = { -1,-2,-1,0,0,0,1,2,1 };
		for (int i = 0; i < Wx.size(); i++)
		{
			Wx[i] = (float)Wx[i] / (float)4;
			Wy[i] = (float)Wy[i] / (float)4;
		}

		Convolution cX, cY;
		cX.SetKernel(Wx, 3, 3);
		cY.SetKernel(Wy, 3, 3);

		Mat imageX, imageY;
		imageX = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());
		imageY = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());
		cX.DoConvolution(sourceImage, imageX);
		cY.DoConvolution(sourceImage, imageY);

		for (int row = 0; row < sourceImage.rows; row++)
			for (int col = 0; col < sourceImage.cols; col++)
			{
				uchar* pXdata = imageX.data + row * imageX.step[0] + col;
				uchar* pYdata = imageY.data + row * imageY.step[0] + col;
				uchar* pDstdata = destinationImage.data + row * destinationImage.step[0] + col;

				float tmp = sqrt(saturate_cast<float>(pXdata[0]) * saturate_cast<float>(pXdata[0]) + saturate_cast<float>(pYdata[0]) * saturate_cast<float>(pYdata[0]));
				if (tmp > THRESHOLD)
					pDstdata[0] = 255;
				else pDstdata[0] = 0;
			}
		return 0;
	}

	//bộ lọc Prewitt
	if (method == 1)
	{
		//phương pháp này đạo hàm bậc nhất theo 2 phương x (theo chiều dọc) và y (theo chiều ngang)
		vector<float>Wx = { 1,0,-1,1,0,-1,1,0,-1 };
		vector<float>Wy = { -1,-1,-1,0,0,0,1,1,1 };
		for (int i = 0; i < Wx.size(); i++)
		{
			Wx[i] = (float)Wx[i] / (float)3;
			Wy[i] = (float)Wy[i] / (float)3;
		}

		Convolution cX, cY;
		cX.SetKernel(Wx, 3, 3);
		cY.SetKernel(Wy, 3, 3);

		Mat imageX, imageY;
		imageX = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());
		imageY = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());
		cX.DoConvolution(sourceImage, imageX);
		cY.DoConvolution(sourceImage, imageY);

		for (int row = 0; row < sourceImage.rows; row++)
			for (int col = 0; col < sourceImage.cols; col++)
			{
				uchar* pXdata = imageX.data + row * imageX.step[0] + col;
				uchar* pYdata = imageY.data + row * imageY.step[0] + col;
				uchar* pDstdata = destinationImage.data + row * destinationImage.step[0] + col;

				float tmp = sqrt(saturate_cast<float>(pXdata[0]) * saturate_cast<float>(pXdata[0]) + saturate_cast<float>(pYdata[0]) * saturate_cast<float>(pYdata[0]));
				if (tmp > THRESHOLD)
					pDstdata[0] = 255;
				else pDstdata[0] = 0;
			}
		return 0;
	}
}