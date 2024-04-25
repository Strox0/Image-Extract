#pragma once
#include "IMAF/Panel.h"

class GUI : public IMAF::Panel
{
public:

	GUI();

	void UiRender() override;

private:

	void RenderFaceDetectionUI();
	void HelpMarker(const char* desc);

	std::string m_output_path;
	std::string m_video_path;
	float m_img_intervals = 1.f;

	bool m_finished = false;
};

