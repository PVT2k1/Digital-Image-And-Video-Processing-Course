#include "Converter.h"

int Converter::RGB2GrayScale(const Mat& sourceImage, Mat& destinationImage)
{
	if (!sourceImage.data)
		return 1;
	int rows = sourceImage.rows,
		cols = sourceImage.cols;

	destinationImage = Mat(rows, cols, CV_8UC1);

	//lấy số kênh màu ở ảnh nguồn và ảnh đích
	int srcChannels = sourceImage.channels(),
		dstChannels = destinationImage.channels();

	int srcWidthStep = sourceImage.step[0],
		dstWidthStep = destinationImage.step[0];

	uchar* pSrcData = (uchar*)sourceImage.data;
	uchar* pDstData = (uchar*)destinationImage.data;

	for (int x = 0; x < rows; x++, pSrcData += srcWidthStep, pDstData += dstWidthStep)
	{
		//mục đích: khi dịch con trỏ row đi thì con trỏ data vẫn không đổi vị trí
		uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;

		for (int y = 0; y < cols; y++, pSrcRow += srcChannels, pDstRow += dstChannels)
		{
			uchar blueChannel = pSrcRow[0],
				greenChannel = pSrcRow[1],
				redChannel = pSrcRow[2];
			pDstRow[0] = (uchar)((blueChannel + greenChannel + redChannel) / 3);
		}
	}
	return 0;
}

int Converter::RGB2HSV(const Mat& sourceImage, Mat& destinationImage)
{
	if (!sourceImage.data)
		return 1;
	int rows = sourceImage.rows,
		cols = sourceImage.cols;

	destinationImage = Mat(rows, cols, CV_32FC3);

	//lấy số kênh màu ở ảnh nguồn và ảnh đích
	int srcChannels = sourceImage.channels(),
		dstChannels = destinationImage.channels();

	int srcWidthStep = sourceImage.step[0],
		dstWidthStep = destinationImage.step[0];

	uchar* pSrcData = (uchar*)sourceImage.data;
	uchar* pDstData = (uchar*)destinationImage.data;

	for (int x = 0; x < rows; x++, pSrcData += srcWidthStep, pDstData += dstWidthStep)
	{
		//mục đích: khi dịch con trỏ row đi thì con trỏ data vẫn không đổi vị trí
		uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;

		for (int y = 0; y < cols; y++, pSrcRow += srcChannels, pDstRow += dstChannels)
		{
			uchar B = pSrcRow[0],
				G = pSrcRow[1],
				R = pSrcRow[2];

			float V1 = saturate_cast<float>(G) / sqrt(2) - saturate_cast<float>(B) / sqrt(2),
				V2 = saturate_cast <float>(2 * R) / sqrt(6) - saturate_cast<float>(G) / sqrt(6) - saturate_cast<float>(B) / sqrt(6);

			pDstRow[0] = saturate_cast<uchar>(atan(V2 / V1));
			pDstRow[1] = saturate_cast<uchar>(sqrt(V1 * V1 + V2 * V2));
			pDstRow[2] = saturate_cast<uchar>((R / sqrt(3) + G / sqrt(3) + B / sqrt(3)));
		}
	}
	return 0;
}

int Converter::Convert(Mat& sourceImage, Mat& destinationImage, int type)
{
	if (!sourceImage.data)
		return 1;
	if (type == 0)
		RGB2GrayScale(sourceImage, destinationImage);
	else if (type == 1)
		RGB2HSV(sourceImage, destinationImage);
	else return 1;
	return 0;
}