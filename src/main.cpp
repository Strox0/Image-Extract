#include "IMAF/Application.h"
#include <Windows.h>

#include "GUI.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	IMAF::AppProperties props;
	props.resizeable = true;
	props.name = "Image Extractor";

	IMAF::Application* app = new IMAF::Application(props);

	std::shared_ptr<GUI> ptr = std::make_shared<GUI>();
	app->AddPanel(ptr);
	
	app->Run();

	delete app;

	return 0;
}