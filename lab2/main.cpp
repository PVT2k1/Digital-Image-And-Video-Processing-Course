#include "GeometricTransformer.h"

int main(int arg, char* argv[])
{
	cout << "Program: " << argv[0] << "\n";
	GeometricTransformer transform;
	if (arg != 5 && arg!=7)
	{
		cout << "Must be 5 or 7 parameters\n";
		return 0;
	}

	if ((string)argv[2] != "-bl" && (string)argv[2] != "-nn")
	{
		cout << "The third parameter must be '-bl' or '-nn'\n";
		return 0;
	}
	PixelInterpolate* interp=nullptr;
	if ((string)argv[2] != "-bl")
		interp = new BilinearInterpolate;
	else interp = new NearestNeighborInterpolate;

	//zoom, resize
	if (arg == 7)
	{
		Mat srcImage = imread(argv[5],IMREAD_ANYCOLOR);

		if (!srcImage.data)
		{
			cout << "inexistent image\n";
			if (interp != nullptr)
			{
				delete interp;
				interp = nullptr;
			}
			return 0;
		}

		if (((string)argv[1] != "-zoom") && ((string)argv[1] != "-resize"))
		{
			cout << "If you enter 7 parameters, the second parameter must be '-zoom' or '-resize'\n";
			if (interp != nullptr)
			{
				delete interp;
				interp = nullptr;
			}
			return 0;
		}
		else
		{
			Mat dstImage;
			if ((string)argv[1] == "-zoom")
			{
				float Sx = convertCharToFloat(argv[3]),
					Sy = convertCharToFloat(argv[4]);
				transform.Scale(srcImage, dstImage, Sx, Sy, interp);
			}
			else
			{
				int Nw = convertCharToFloat(argv[3]),
					Nh = convertCharToFloat(argv[4]);
				transform.Resize(srcImage, dstImage, Nw, Nh, interp);
			}
			imwrite(argv[6], dstImage);
		}
	}

	//-bright, -contrast
	else if (arg == 5)
	{
		Mat srcImage;
		srcImage = imread(argv[3],IMREAD_ANYCOLOR);

		if (!srcImage.data)
		{
			cout << "inexistent image\n";
			if (interp != nullptr)
			{
				delete interp;
				interp = nullptr;
			}
			return 0;
		}

		if ((string)argv[1] != "-flipV" && (string)argv[1] != "-flipH")
		{
			cout << "The second parameter must be '-flipV' or '-flipH'\n";
			if (interp != nullptr)
			{
				delete interp;
				interp = nullptr;
			}
			return 0;
		}
		else
		{
			Mat dstImage;
			if ((string)argv[1] == "-flipV")
				transform.Flip(srcImage, dstImage, 0, interp);
			else
				transform.Flip(srcImage, dstImage, 1, interp);
			imwrite(argv[4], dstImage);
		}
	}

	if (interp != nullptr)
	{
		delete interp;
		interp = nullptr;
	}
	return 0;
}