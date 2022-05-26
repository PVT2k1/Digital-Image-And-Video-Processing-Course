#include "GeometricTransformer.h"

int GeometricTransformer::Transform(const Mat& beforeImage,
	Mat& afterImage,
	AffineTransform* transformer,
	PixelInterpolate* interpolator)
{
	if (!beforeImage.data)
		return 0;

	int beforeWidthStep = saturate_cast<int>(beforeImage.step[0]),
		afterWidthStep = saturate_cast<int>(afterImage.step[0]),
		beforeChannel = saturate_cast<int>(beforeImage.channels()),
		afterChannel = saturate_cast<int>(afterImage.channels());

	for (int row = 0; row < afterImage.rows; row++)
		for (int col = 0; col < afterImage.cols; col++)
		{
			float x = (float)col;
			float y = (float)row;

			transformer->TransformPoint(x, y);

			//kiểm tra xem điểm biến đổi có ngoài ảnh không, nếu có thì qua điểm khác
			if (x > beforeImage.cols - 1 || x < 0)
				continue;
			if (y > beforeImage.rows - 1 || y < 0)
				continue;

			uchar* pAfterCurrentData = afterImage.data + saturate_cast<int>(afterWidthStep * row) + saturate_cast<int>(afterChannel * col);

			uchar* pSrc = beforeImage.data;
			for (int i = 0; i < afterChannel; i++)
			{
				pAfterCurrentData[i] = interpolator->Interpolate(x, y, pSrc, beforeWidthStep, beforeChannel);
				pSrc++;
			}
		}
	return 1;
}

int GeometricTransformer::Scale(
	const Mat& srcImage,
	Mat& dstImage,
	float sx, float sy,
	PixelInterpolate* interpolator)
{
	if (!srcImage.data)
		return 0;

	if (sx < FLT_EPSILON || sy < FLT_EPSILON)
		return 0;

	int dstRows = (int)((float)srcImage.rows * sy + 0.5f);
	int dstCols = (int)((float)srcImage.cols * sx + 0.5f);

	dstImage = Mat(dstRows, dstCols, srcImage.type());

	int beforeWidthStep = saturate_cast<int>(srcImage.step[0]),
		afterWidthStep = saturate_cast<int>(dstImage.step[0]),
		beforeChannel = saturate_cast<int>(srcImage.channels()),
		afterChannel = saturate_cast<int>(dstImage.channels());

	//Cách 1: không dùng lại method Transform
	for (int row = 0; row < dstImage.rows; row++)
		for (int col = 0; col < dstImage.cols; col++)
		{
			float x = (float)col / sx;
			float y = (float)row / sy;

			if (x > srcImage.cols - 1 || x < 0)
				continue;
			if (y > srcImage.rows - 1 || y < 0)
				continue;
			//lấy con trỏ tại vị trí lưu giá trị của ảnh kết quả
			uchar* pAfterCurrentData = dstImage.data + saturate_cast<int>(afterWidthStep * row) + saturate_cast<int>(afterChannel * col);

			uchar* pSrc = srcImage.data;
			for (int i = 0; i < afterChannel; i++)
			{
				pAfterCurrentData[i] = interpolator->Interpolate(x, y, pSrc, beforeWidthStep, beforeChannel);
				pSrc++;			//trường hợp 3 kênh màu thì con trỏ sẽ dịch qua từng kênh màu
			}
		}
	return 1;

	//------------------đây là cách thứ 2 khi sử dụng lại method Transform, nhưng không hiểu vì sao mà 
	//					đoạn code của em lại không trả ra kết quả mong muốn, dù đã ngồi tìm nhiều cách.
	/*AffineTransform* affInverseScale = new AffineTransform;
	affInverseScale->Scale(1/sy, 1/sx);

	this->Transform(srcImage, dstImage, affInverseScale, interpolator);

	if (affInverseScale != nullptr)
	{
		delete affInverseScale;
		affInverseScale = nullptr;
	}
	return 1;*/
}

int GeometricTransformer::Resize(
	const Mat& srcImage,
	Mat& dstImage,
	int newWidth, int newHeight,
	PixelInterpolate* interpolator)
{
	if (!srcImage.data)
		return 0;

	//lấy tỉ lệ kích thước để áp dụng lại method scale
	float widthRatio = (float)newWidth / (float)srcImage.cols,
		heightRatio = (float)newHeight / (float)srcImage.rows;
	
	return GeometricTransformer::Scale(srcImage, dstImage, widthRatio, heightRatio, interpolator);
}

int GeometricTransformer::Flip(
	const Mat& srcImage,
	Mat& dstImage,
	bool direction,
	PixelInterpolate* interpolator)
{
	if (!srcImage.data)
		return 0;
	if (direction != 0 && direction != 1)
		return 0;

	dstImage = Mat(srcImage.rows, srcImage.cols, srcImage.type());

	//trong hàm lấy đối xứng ảnh này, sẽ không cần dùng bất cứ phép biến đổi affine nào
	for (int row = 0;row<dstImage.rows;row++)
		for (int col = 0; col < dstImage.cols; col++)
		{
			int srcX = 0, srcY = 0;
			if (direction == 0)
			{
				srcY = row;
				srcX = dstImage.cols - 1 - col;
			}

			if (direction == 1)
			{
				srcY = dstImage.rows - 1 - row;
				srcX = col;
			}

			uchar* pSrcCurrentData = srcImage.data + saturate_cast<int>(srcY * srcImage.step[0] + srcX * srcImage.step[1]);
			uchar* pDstCurrentData = dstImage.data + saturate_cast<int>(row * dstImage.step[0] + col * dstImage.step[1]);

			for (int i = 0; i < dstImage.channels(); i++)
				pDstCurrentData[i] = pSrcCurrentData[i];
		}
	return 1;
}

int GeometricTransformer::RotateUnkeepImage(
	const Mat& srcImage, Mat& dstImage, float angle, PixelInterpolate* interpolator)
{
	if (!srcImage.data)
		return 0;
	
	dstImage = Mat(srcImage.rows, srcImage.cols, srcImage.type());

	//chương trình dưới đây nó bị ra kết quả không mong muốn như đoạn code đã comment ở trong method Scale
	AffineTransform affineMatrix;
	//để xoay ảnh theo 1 góc cho trước thì đầu tiên phải đưa ảnh về gốc tọa độ
	affineMatrix.Translate(float(0) - float(dstImage.rows) / 2, float(0) - float(dstImage.cols) / 2);
	affineMatrix.Rotate(-angle);
	affineMatrix.Translate(float(dstImage.rows) / 2, float(dstImage.cols) / 2);
	
	return GeometricTransformer::Transform(srcImage, dstImage, &affineMatrix, interpolator);
}

int convertCharToInt(char* c)
{
	int result = 0;
	for (int i = 0; i < strlen(c); i++)
		result = result * 10 + saturate_cast<int>(c[i] - '0');
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