#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <atomic>
#include <queue>
#include <mutex>
#include <thread>

class VideoProc
{
public:

	void ProcessVideos(std::filesystem::path video_path, std::filesystem::path output_path, float image_intervals);

	uint64 GetTotalSteps();
	uint64 GetCurrentSteps();

private:

	void RunProc(std::filesystem::path video_path, std::filesystem::path output_path, float image_intervals);
	void FindVideos();

	std::filesystem::path m_video_path;
	std::filesystem::path m_output_path;
	float m_img_intervals = 1.f;
	std::atomic<uint64> m_total_steps = 0;
	std::atomic<uint64> m_current_step = 0;

	std::vector<std::filesystem::path> m_videos;
};