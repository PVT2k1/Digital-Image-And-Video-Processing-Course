#include "Convolution.h"

int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage)
{
	if (!sourceImage.data)
		return 1;
	int srcChannels = sourceImage.channels();
	//nếu không phải ảnh xám
	if (srcChannels != 1)
		return 1;

	uchar* pSrcData = sourceImage.data;
	uchar* pDstData = destinationImage.data;
	int srcWidthStep = sourceImage.step[0];
	int dstWidthStep = destinationImage.step[0];

	//duyệt qua ảnh nguồn, tính trên từng vị trí trên ảnh nguồn và đưa kết quả vào vị trí tương ứng trên ảnh đích
	for (int row = 0; row < sourceImage.rows; row++)
		for (int col = 0; col < sourceImage.cols; col++)
		{
			float sumConvolution = (float)0;

			//duyệt qua Kernel và các điểm ảnh lân cận với điểm ảnh đang xét trên ảnh nguồn
			//LƯU Ý: điểm ảnh của ảnh nguồn đang xét hiện tại tương ứng với giá trị ô ở giữa Kernel
			//là ô (_kernelHeight / 2, _kernelWidth / 2)
			for (int rowKernel = 0; rowKernel < _kernelHeight; rowKernel++)
				for (int colKernel = 0; colKernel < _kernelWidth; colKernel++)
				{
					int i = row - _kernelHeight / 2 + rowKernel;
					int j = col - _kernelWidth / 2 + colKernel;

					//khi ra điểm ảnh tương ứng không nằm trong ảnh nguồn thì cho giá trị mặc định của pixel là 0
					if (i < 0 || i >= sourceImage.rows || j < 0 || j >= sourceImage.cols)
						sumConvolution += (float)0 * _kernel[rowKernel * _kernelWidth + colKernel];
					else
					{
						uchar* pImageData = pSrcData + srcWidthStep * i + j;
						sumConvolution += _kernel[rowKernel * _kernelWidth + colKernel] * saturate_cast<float>(pImageData[0]);
					}
				}

			if (sumConvolution < 0)
			{
				sumConvolution = 0;
			}
			int gray = saturate_cast<int>(sumConvolution + 0.5);
			uchar* pImageData = pDstData + dstWidthStep * row + col;
			pImageData[0] = saturate_cast<uchar>(gray);
		}
	return 0;
}