#include "AffineTransform.h"

void AffineTransform::Translate(float dx, float dy)
{
	float value[3][3] = { {1.0f, 0.0f, dx},{0.0f, 1.0f, dy}, {0.0f, 0.0f, 1.0f} };
	Mat matTranslate = Mat(3, 3, CV_32FC1, value);
	_matrixTransform = matTranslate * _matrixTransform;
}

void AffineTransform::Rotate(float angle)
{	
	//vì angle là đơn vị độ (theo các yêu cầu bài tập sau này)
	//nên được chuyển sang radian để tính cos và sin
	float cosAngle = cos(angle * Pi / (float)180);
	float sinAngle = sin(angle * Pi / (float)180);
	float value[3][3] = { {cosAngle, -sinAngle, 0.0f},{sinAngle, cosAngle, 0.0f}, {0.0f, 0.0f, 1.0f} };
	Mat matRotate = Mat(3, 3, CV_32FC1, value);
	_matrixTransform = matRotate * _matrixTransform;
}

void AffineTransform::Scale(float sx, float sy)
{
	_matrixTransform.at<float>(0, 0) *= sx;
	_matrixTransform.at<float>(0, 0) *= sy;
}

void AffineTransform::TransformPoint(float& x, float& y)
{
	float point[3] = { x,y,0.0f };
	Mat pointMatrix = Mat(3, 1, CV_32FC1, point);

	Mat result = _matrixTransform * pointMatrix;
	x = result.at<float>(0, 1);
	y = result.at<float>(0, 2);
}