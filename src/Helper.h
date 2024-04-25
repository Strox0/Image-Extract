#pragma once
#include <string>
#include <opencv2/opencv.hpp>

namespace Helper 
{
	std::string SelectFile(const char* filter);
	std::wstring SelectFolder(bool has_to_exist);
	bool CheckExtensions(const std::string& allowed, const std::string& path);
	void CheckSize(const cv::Mat& img, cv::Rect& cropping_rect);
	std::string WStrToStr(const std::wstring& wstr);
}