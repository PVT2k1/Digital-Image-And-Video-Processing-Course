#include "ColorTransformer.h"

int ColorTransformer::ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, short b)
{
	if (!sourceImage.data)
		return 0;
	int rows = sourceImage.rows,
		cols = sourceImage.cols;
	int srcChannels = sourceImage.channels();
	destinationImage = Mat(rows, cols, sourceImage.type());

	//không cần lấy dstWidthStep
	int srcWidthStep = sourceImage.step[0];

	uchar* pSrcData = (uchar*)sourceImage.data;
	uchar* pDstData = (uchar*)destinationImage.data;

	for (int x = 0; x < rows; x++)
	{
		for (int y = 0; y < cols; y++)
		{
			uchar* pSrcCurrentData = pSrcData + x.srcWidthStep + y.srcChannels;
			uchar* pDstCurrentData = pDstData + x.srcWidthStep + y.srcChannels;
			for (int i=1; i < srcChannels; i++)
				pDstCurrentData[i] = saturate_cast<uchar>(pSrcCurrentData[i] + b);
		}
	}
	return 1;
}

int ColorTransformer::ChangeContrast(const Mat& sourceImage, Mat& destinationImage, float c)
{
	if (!sourceImage.data)
		return 0;
	int rows = sourceImage.rows,
		cols = sourceImage.cols;
	int srcChannels = sourceImage.channels();
	if (srcChannels == 1)
		destinationImage = Mat(rows, cols, CV_8UC1);
	else destinationImage = Mat(rows, cols, CV_8UC3);

	//không cần lấy dstWidthStep
	int srcWidthStep = sourceImage.step[0];

	uchar* pSrcData = (uchar*)sourceImage.data;
	uchar* pDstData = (uchar*)destinationImage.data;

	for (int x = 0; x < rows; x++, pSrcData += srcWidthStep, pDstData += srcWidthStep)
	{
		//mục đích: khi dịch con trỏ row đi thì con trỏ data vẫn không đổi vị trí
		uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;

		for (int y = 0; y < cols; y++, pSrcRow += srcChannels, pDstRow += srcChannels)
		{
			if (srcChannels == 1)
				pDstRow[0] = saturate_cast<uchar>(pSrcRow[0] * c);
			else
			{
				pDstRow[0] = saturate_cast<uchar>(pSrcRow[0] * c);
				pDstRow[1] = saturate_cast<uchar>(pSrcRow[1] * c);
				pDstRow[2] = saturate_cast<uchar>(pSrcRow[2] * c);
			}
		}
	}
	return 1;
}

int ColorTransformer::CalcHistogram(const Mat& sourceImage, Mat& histMatrix)
{
	if (!sourceImage.data)
		return 0;
	histMatrix = Mat::zeros(256, 1, CV_32F);
	Mat sourceImage1;
	sourceImage.convertTo(sourceImage1, CV_32F);

	//lấy số kênh màu ở ảnh nguồn
	int srcChannels = sourceImage1.channels();

	uchar* pSrcData = (uchar*)sourceImage1.data;

	//không cần lấy dstWidthStep
	int srcWidthStep = sourceImage1.step[0];

	for (int x = 0; x < sourceImage1.rows; x++, pSrcData += srcWidthStep)
	{
		//mục đích: khi dịch con trỏ row đi thì con trỏ data vẫn không đổi vị trí
		uchar* pSrcRow = pSrcData;

		for (int y = 0; y < sourceImage1.cols; y++, pSrcRow += srcChannels)
		{
			for ( int i=0;i<srcChannels;i++)
				histMatrix.at<float>((double)sourceImage1.at<float>(i, pSrcRow[i])) += 1;
		}
	}
	return 1;
}

int ColorTransformer::DrawHistogram(const Mat& histMatrix, Mat& histImage)
{
	histImage = Mat(400, 512*3, CV_32FC1, Scalar(255, 255, 255));
	Mat normalize_his;
	normalize(histMatrix, normalize_his, 0, 400, NORM_MINMAX, -1, Mat());
	for (int i = 0; i < 256; i++)
	{
		rectangle(histImage, Point(2 * i, histImage.rows - normalize_his.at<float>(i)),
			Point(2 * (i + 1), histImage.rows), Scalar(0, 0, 0));
	}
	for (int i = 0; i < 256; i++)
	{
		rectangle(histImage, Point(2 * i+512, histImage.rows - normalize_his.at<float>(i)),
			Point(2 * (i + 1) + 512, histImage.rows), Scalar(0, 0, 0));
	}
	for (int i = 0; i < 256; i++)
	{
		rectangle(histImage, Point(2 * i+512*2, histImage.rows - normalize_his.at<float>(i)),
			Point(2 * (i + 1) +512, histImage.rows), Scalar(0, 0, 0));
	}
	return 1;
}

//int ColorTransformer::DrawHistogram(const Mat& histMatrix, Mat& histImage)
//{
//	if (histMatrix.data == NULL)
//		return 0;
//
//	int height = histMatrix.rows;
//
//
//	histImage = Mat(400, 512 * 3, CV_32FC1, Scalar(0, 0, 0));
//
//	for (int j = 0; j < height; j++)
//	{
//		int max_value = 0;
//		int i = 0;
//		for (i; i < 256; i++)
//		{
//			if (histMatrix.at<float>(j, i) > max_value)
//				max_value = histMatrix.at<float>(j, i);
//		}
//
//		for (int i = 0; i < 256; i++)
//		{
//			rectangle(histImage, Point(2 * i + 512 * j, 400 - histMatrix.at<float>(j, i) * 380 / max_value),
//				Point(2 * (i + 1) + 512 * j, 400), Scalar(100, 200, 255));
//		}
//
//		rectangle(histImage, Point(2 * i + 512 * j, 0),
//			Point(2 * (i + 1) + 512 * j, 400), Scalar(100, 200, 255));
//	}
//	return 1;
//}

short convertCharToShort(char* c)
{
	short result = 0;
	for (int i = 0; i < strlen(c); i++)
		result = result * 10 + saturate_cast<short>(c[i] - '0');
	return result;
}

float convertCharToFloat(char* c)
{
	float result = 0;
	int i = 0;
	for (i; i < strlen(c); i++)
		if (c[i] == '.')
			break;
		else result = result * 10 + saturate_cast<float>(c[i] - '0');
	for (int j = i + 1; j < strlen(c); j++)
		result += pow(10, -(j - i)) * saturate_cast<float>(c[j] - '0');
	return result;
}