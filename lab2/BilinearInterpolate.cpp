#include "BilinearInterpolate.h"

uchar BilinearInterpolate::Interpolate(float tx, float ty, uchar* pSrc, int srcWidthStep, int nChannels)
{
	uchar res = saturate_cast<uchar>(0);
	int l = (int)tx,
		k = (int)ty;
	float a = tx - (float)l,
		b = ty - (float)k;
	for (int row = 0; row <= k; row++, pSrc += srcWidthStep);
	pSrc = pSrc + saturate_cast<int>(l * nChannels);
	if ((a == 0) && (b != 0))
	{
		uchar* tmp = pSrc;	//mục đích là giữ nguyên pSrc
		tmp += srcWidthStep;
		res = res + saturate_cast<uchar>(1 - b) * (*pSrc) + saturate_cast<uchar>(b) * (*tmp);
	}
	if ((a != 0) && (b == 0))
	{
		uchar* tmp = pSrc;	//mục đích là giữ nguyên pSrc
		tmp += nChannels;
		res = res + saturate_cast<uchar>(1 - a) * (*pSrc) + saturate_cast<uchar>(a) * (*tmp);
	}
	if ((a == 0) && (b == 0))
		res = *pSrc;
	if ((a != 0) && (b != 0))
	{
		uchar* tmp = pSrc;	//mục đích là giữ nguyên pSrc
		tmp += nChannels;
		res = res + saturate_cast<uchar>((1 - a)*(1-b)) * (*pSrc);
		res = res + saturate_cast<uchar>(a * (1 - b)) * (*tmp);
		pSrc += srcWidthStep;
		tmp += srcWidthStep;
		res = res + saturate_cast<uchar>(b * (1 - a)) * (*pSrc);
		res = res + saturate_cast<uchar>(a * b) * (*tmp);
	}
	return res;
}