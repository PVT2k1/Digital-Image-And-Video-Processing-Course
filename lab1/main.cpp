#include "Converter.h"
#include "ColorTransformer.h"

//int main(int arg, char* argv[])
//{
//	cout << "Program: " << argv[0] << "\n";
//
//	//-rgb2gray, -rgb2hsv, -drawhist
//	if (arg == 4)
//	{
//		Mat srcImage = imread(argv[2]);
//
//		if (!srcImage.data)
//		{
//			cout << "Image didn't exist\n";
//			return 0;
//		}
//
//		if (srcImage.channels() == 1)
//		{
//			cout << "Image must be color image\n";
//			return 0;
//		}
//
//		if (((string)argv[1] != "-rgb2gray") && ((string)argv[1] != "-rgb2hsv"))
//		{
//			cout << "The second parameter must be '-rgb2gray' or '-rgb2hsv'\n";
//			return 0;
//		}
//		else
//		{
//			Converter convert;
//			Mat dstImage;
//			if ((string)argv[1] == "-rgb2gray")
//				convert.Convert(srcImage, dstImage, 0);
//			else
//				convert.Convert(srcImage, dstImage, 1);
//			imwrite(argv[3], dstImage);
//		}
//	}
//
//	//-bright, -contrast
//	else if (arg == 5)
//	{
//		Mat srcImage;
//		srcImage = imread(argv[3]);
//
//		if (!srcImage.data)
//		{
//			cout << "Image didn't exist\n";
//			return 0;
//		}
//
//		if ((string)argv[1] != "-bright" && (string)argv[1] != "-contrast")
//		{
//			cout << "The second parameter must be '-bright' or '-contrast'\n";
//			return 0;
//		}
//		else
//		{
//			ColorTransformer color;
//			Mat dstImage;
//			short b;	//brightness intensity
//			float c;	//contrast coefficient
//			if ((string)argv[1] == "-bright")
//			{
//				b = convertCharToShort(argv[2]);
//				color.ChangeBrighness(srcImage, dstImage, b);
//			}
//			else
//			{
//				c = convertCharToFloat(argv[2]);
//				color.ChangeContrast(srcImage, dstImage, c);
//			}
//			imwrite(argv[4], dstImage);
//		}
//	}
//
//	else
//		cout << "Must be 4 or 5 parameters\n";
//
//	return 0;
//}