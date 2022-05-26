#include "Blur.h"

int Blur::BlurImage(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method)
{
	if (!sourceImage.data)
		return 1;
	int srcChannels = sourceImage.channels();
	//nếu không phải ảnh xám
	if (srcChannels != 1)
		return 1;

	destinationImage = Mat(sourceImage.rows, sourceImage.cols, sourceImage.type());

	//Lọc trung bình
	if (method == 0)
	{
		//ma trận lọc trung bình
		vector <float> mean;
		for (int i = 0; i < (kWidth * kHeight); i++)
		{
			float element = (float)(1) / (float)(kWidth * kHeight);
			mean.push_back(element);
		}

		Convolution c;
		c.SetKernel(mean, kWidth, kHeight);
		return c.DoConvolution(sourceImage, destinationImage);
	}

	//Lọc trung vị, không cần tính tích chập
	else if (method == 1)
	{
		//duyệt qua ảnh nguồn
		for (int row = 0; row < sourceImage.rows; row++)
			for (int col = 0; col < sourceImage.cols; col++)
			{
				vector<uchar> data;	//lưu các giá trị của điểm ảnh nguồn tương ứng với các ô trên Kernel

				//duyệt qua các vị trí trên Kernel để suy ra vị trí tương ứng trên ảnh nguồn
				for (int rowKernel = 0; rowKernel < kHeight; rowKernel++)
					for (int colKernel = 0; colKernel < kWidth; colKernel++)
					{
						int i = row - kHeight / 2 + rowKernel;
						int j = col - kWidth / 2 + colKernel;

						//khi ra điểm ảnh tương ứng không nằm trong ảnh nguồn thì cho giá trị mặc định của pixel là 0
						if (i < 0 || i >= sourceImage.rows || j < 0 || j >= sourceImage.cols)
							data.push_back(saturate_cast<uchar>(0));
						else
						{
							uchar* pSrcData = sourceImage.data + sourceImage.step[0] * i + j;
							data.push_back(pSrcData[0]);
						}
					}
				Blur::sortIncrease(data);
				uchar* pDstData = destinationImage.data + destinationImage.step[0] * row + col;
				pDstData[0] = data[data.size() / 2 + 1];
			}
		return 0;
	}

	//Lọc Gauss
	else if (method == 2)
	{
		//giả sử phân phối Gauss là phân phối chuẩn tắc => độ lệch chuẩn = 1, trung bình = 0
		int sigma = 1;	//độ lệch chuẩn
		float tmp = (float)1 / ((float)sqrt(2 * PI) * (float)sigma);
		float tmp1 = (float)1 / (float)(sigma * sigma);

		//ma trận lọc gauss
		vector<float> gauss;
		for (int i = -kHeight / 2; i <= (kHeight  / 2); i++)
			for (int j = -kWidth / 2; j <= (kWidth / 2); j++)
				gauss.push_back(tmp * exp(-(i*i + j*j) * tmp1));

		Convolution c;
		c.SetKernel(gauss, kWidth, kHeight);
		return c.DoConvolution(sourceImage, destinationImage);
	}
	else
	{
		//nhập sai giá trị method
		return 1;
	}
}

void Blur::sortIncrease(vector<uchar>& data)
{
	for (int i = 0; i < data.size() - 1; i++)
		for (int j = i + 1; j < data.size(); j++)
			if (data[i] > data[j])
				swap(data[i], data[j]);
}

int convertCharToInt(char* c)
{
	int result = 0;
	for (int i = 0; i < strlen(c); i++)
		result = result * 10 + saturate_cast<int>(c[i] - '0');
	return result;
}