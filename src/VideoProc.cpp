#include "VideoProc.h"
#include "Helper.h"
#include <thread>
#include <Windows.h>

static const char* allowed_extensions = ".mp4";

void VideoProc::RunProc(std::filesystem::path video_path, std::filesystem::path output_path, float image_intervals)
{
	m_video_path = video_path;
	m_output_path = output_path;

	if (!std::filesystem::exists(m_output_path))
		std::filesystem::create_directories(m_output_path);

	if (FindVideos())
	{
		m_current_step = 1;
		m_total_steps = 1;
		return;
	}

	for (const auto& video : m_videos)
	{
		cv::VideoCapture cap(video.string());

		if (!cap.isOpened())
		{
			continue;
		}

		int frame_count = cap.get(cv::CAP_PROP_FRAME_COUNT);
		uint64 fps = cap.get(cv::CAP_PROP_FPS);
				
		cv::Mat frame;
		int frame_number = 0;

		while (cap.grab())
		{
			if (m_img_intervals == 0)
			{
				cv::Mat frame;
				cap.retrieve(frame);

				std::string img_name = (m_output_path / video.stem()).string();
				img_name += "_" + std::to_string(frame_number) + ".png";
				cv::imwrite(img_name, frame);
			}
			else if (frame_number % lround(fps * m_img_intervals) == 0)
			{
				cv::Mat frame;
				cap.retrieve(frame);

				std::string img_name = (m_output_path / video.stem()).string();
				img_name += "_" + std::to_string(frame_number) + ".png";
				cv::imwrite(img_name, frame);
			}

			frame_number++;
			m_current_step++;
		}
		
		m_current_step += frame_count - frame_number;
		cap.release();
	}
}

void VideoProc::ProcessVideos(std::filesystem::path video_path, std::filesystem::path output_path, float image_intervals)
{
	std::thread proc_thread(&VideoProc::RunProc, this, video_path, output_path, image_intervals);
	proc_thread.detach();
}

uint64 VideoProc::GetTotalSteps()
{
	return m_total_steps.load();
}

uint64 VideoProc::GetCurrentSteps()
{
	return m_current_step.load();
}

bool VideoProc::FindVideos()
{
	std::error_code ec;
	for (const auto& entry : std::filesystem::directory_iterator(m_video_path,std::filesystem::directory_options::skip_permission_denied,ec)) 
	{
		if (entry.is_regular_file()) 
		{
			if (Helper::CheckExtensions(allowed_extensions, entry.path().string())) 
			{
				m_videos.push_back(entry.path());

				cv::VideoCapture cap(entry.path().string());

				if (!cap.isOpened())
				{
					continue;
				}

				m_total_steps += (uint64)cap.get(cv::CAP_PROP_FRAME_COUNT);
			}
		}
	}

	if (ec)
	{
		MessageBoxA(NULL, ec.message().c_str(), "Error", MB_OK | MB_ICONERROR);
		return true;
	}

	return false;
}