#include "GUI.h"
#include <IMAF/Application.h>
#include <imgui.h>
#include "Helper.h"
#include <filesystem>

GUI::GUI()
{
	m_output_path.resize(_MAX_PATH);
	m_video_path.resize(_MAX_PATH);
}

void GUI::UiRender()
{
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos, ImGuiCond_Once);
	ImGui::SetNextWindowSize(viewport->Size, ImGuiCond_Once);

	IMAF::Begin("window", NULL, { 0 | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar });

	ImVec2 window_size = ImGui::GetWindowSize();

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Open Output Folder"))
			{
				if (!m_output_path.empty())
				{
					if (!std::filesystem::exists(m_output_path))
						std::filesystem::create_directories(m_output_path);
					ShellExecuteA(NULL, "open", "explorer.exe", m_output_path.c_str(), NULL, SW_SHOWNORMAL);
				}
			}
			if (ImGui::BeginMenu("Theme"))
			{
				if (ImGui::MenuItem("Purple-Dark Theme")) 
					IMAF::Application::SetPrurpleDarkColorTheme();

				if (ImGui::MenuItem("Dark Theme")) 
					IMAF::Application::SetDarkColorTheme();
				
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::InputTextWithHint("##", "Enter video folder path", (char*)m_video_path.c_str(), m_video_path.capacity() + 1);

	ImGui::SameLine();
	if (ImGui::Button("Browse", { 100,0 }))
		m_video_path = Helper::WStrToStr(Helper::SelectFolder(true));

	ImGui::InputTextWithHint("##", "Enter output path", (char*)m_output_path.c_str(), m_output_path.capacity() + 1);

	ImGui::SameLine();
	if (ImGui::Button("Browse##", { 100,0 }))
		m_output_path = Helper::WStrToStr(Helper::SelectFolder(false));

	if (m_img_intervals < 0)
		m_img_intervals = 0;
	ImGui::InputFloat("Image Intervals", &m_img_intervals, 0.1f, 1.0f, "%.2f");
	ImGui::SameLine(); HelpMarker("Will capture a frame from the video(s) within the specified time intervals (seconds)");

	ImGui::Separator();

	static bool face_detection = false;
	ImGui::Checkbox("Face-Detection", &face_detection);

	if (face_detection)
		RenderFaceDetectionUI();

	static bool clicked = false;

	ImVec2 button_size;
	button_size.x = window_size.x * 0.8f;
	button_size.y = ImGui::CalcTextSize("Start").y + 50;

	// Center on th X axis, and place it at the bottom of the window with 2% padding
	ImGui::SetCursorPos({ (window_size.x - button_size.x) / 2.f, (window_size.y - button_size.y) - window_size.y * 0.02f });

	if (!clicked)
	{
		if (ImGui::Button("Start", button_size))
		{
			clicked = true;
			bool error = false;

			m_video_path.push_back('\\');
			if (m_video_path.empty() || !std::filesystem::exists(m_video_path))
				error = true;

			if (m_output_path.empty())
			{
				m_output_path = ".\\output\\";
				if (!std::filesystem::exists(m_output_path))
					std::filesystem::create_directories(m_output_path);
			}

			//if (face_detection)
			//{
			//	m_max_faces = faces_slider;
			//	m_image_padding = imgpad_value;
			//	m_forceuse_usable = forceuse_usable;
			//	m_facemodel_path = model_path;
			//	m_minface_size.x = min_face[0];
			//	m_minface_size.y = min_face[1];
			//	if (m_facemodel_path.empty())
			//		error = true;
			//}

			if (!error)
			{
				if (face_detection)
					MessageBoxA(NULL,"Processing Video (Face Detection Enabled)", "Processing", MB_OK | MB_ICONINFORMATION);
				else
					MessageBoxA(NULL, "Processing Video", "Processing", MB_OK | MB_ICONINFORMATION);
			}
			else
				clicked = false;
		}
	}
	else
	{
		static float progress = 0.0f;

		//double currs = GetCurrentSteps();
		//double total = GetTotalSteps();
		//double fraction = currs / total;

		//progress = fraction;

		ImGui::ProgressBar(progress, ImVec2{ button_size.x,0 });

		if (progress >= 1.0f || m_finished) 
		{
			progress = 0.0f;
			clicked = false;
		}
	}

	IMAF::End();
}

void GUI::RenderFaceDetectionUI()
{
	static char model_path[_MAX_PATH] = "";
	static int imgpad_slider = 0;
	static int imgpad_value;
	static int faces_slider = 1;
	static bool forceuse_usable = false;
	static int min_face[2] = { 100,100 };

	static bool c = false;
	if (!c) {
//		std::string tmp = CheckModelFile();
//		strcpy_s(model_path, tmp.data());
		c = true;
	}

	ImGui::InputTextWithHint("####1##", "Enter face-detection model path (.xml)", model_path, IM_ARRAYSIZE(model_path));

	ImGui::SameLine();
	if (ImGui::Button("Browse###", { 80,0 }))
	{
//		std::string tmp = GetFile("XML File(*.xml)\0*.xml\0");
//		strcpy_s(model_path, tmp.data());
	}

	imgpad_value = imgpad_slider * 100;
	if (imgpad_slider == 0)
		ImGui::SliderInt("Image Padding", &imgpad_slider, 0, 10, "%d px", ImGuiSliderFlags(0 | ImGuiSliderFlags_NoInput));
	else
		ImGui::SliderInt("Image Padding", &imgpad_slider, 0, 10, "%d00 px", ImGuiSliderFlags(0 | ImGuiSliderFlags_NoInput));

	ImGui::SliderInt2("Minimum Face Size", min_face, 50, 2000, "%d px", ImGuiSliderFlags(0 | ImGuiSliderFlags_AlwaysClamp));

	ImGui::SliderInt("Max Faces", &faces_slider, 1, 12, "%d", ImGuiSliderFlags(0 | ImGuiSliderFlags_NoInput));

	ImGui::Checkbox("Force Use Valid Frame", &forceuse_usable);
	ImGui::SameLine(); HelpMarker("If the selected frame is invalid based on the parameters provided it will keep searching until a valid one is found");
}

void GUI::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
