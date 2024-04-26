#include "IMAF/Application.h"
#include <Windows.h>
#include "imgui.h"
#include "GUI.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IMAF::AppProperties props;
	props.resizeable = false;

	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	props.width = screen_width * 0.50;
	props.height = screen_height * 0.65;

	props.name = "Image Extractor";

	IMAF::Application* app = new IMAF::Application(props);

	std::shared_ptr<GUI> ptr = std::make_shared<GUI>();
	app->AddPanel(ptr);
	
	app->SetUp([]() 
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.ItemSpacing = ImVec2(12, 12);
			style.WindowPadding = ImVec2(15, 15);
			style.ItemInnerSpacing = ImVec2(12, 12);
			style.FramePadding = ImVec2(20, 12);
		}
	);

	app->Run();

	delete app;

	return 0;
}