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