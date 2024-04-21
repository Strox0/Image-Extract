#pragma comment(lib, "opencv_core4d.lib")
#pragma comment(lib, "opencv_highgui4d.lib")
#pragma comment(lib, "opencv_imgcodecs4d.lib")
#pragma comment(lib, "opencv_imgproc4d.lib")
#pragma comment(lib, "opencv_videoio4d.lib")
#pragma comment(lib, "opencv_calib3d4d.lib")
#pragma comment(lib, "opencv_features2d4d.lib")
#pragma comment(lib, "opencv_flann4d.lib")
#pragma comment(lib, "opencv_ml4d.lib")
#pragma comment(lib, "opencv_photo4d.lib")
#pragma comment(lib, "opencv_stitching4d.lib")
#pragma comment(lib, "opencv_video4d.lib")
#pragma comment(lib, "opencv_dnn4d.lib")
#pragma comment(lib, "opencv_objdetect4d.lib")

#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "openjp2.lib")
#pragma comment(lib, "libpng16d.lib")
#pragma comment(lib, "libwebp.lib")
#pragma comment(lib, "tiffd.lib")
#pragma comment(lib, "gif.lib")
#pragma comment(lib, "zlibd.lib")
#pragma comment(lib, "turbojpeg.lib")
#pragma comment(lib, "lzma.lib")
#pragma comment(lib, "libsharpyuv.lib")

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	cv::Mat img = cv::imread("./test.jpg");
	cv::imshow("TEST", img);
	cv::waitKey(0);

	return 0;
}