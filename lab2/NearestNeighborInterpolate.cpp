#include "NearestNeighborInterpolate.h"

uchar NearestNeighborInterpolate::Interpolate(float tx, float ty, uchar* pSrc, int srcWidthStep, int nChannels)
{
	int Y = int(ty + 0.5f);
	int X = int (tx +0.5f);

	uchar* tmp = pSrc;
	tmp = pSrc + saturate_cast<int>(Y * srcWidthStep + X* nChannels);

	return *tmp;
}