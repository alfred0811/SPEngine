#include <SPEngine/Inc/SPEngine.h>

using namespace SPEngine;

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Window";

	App& mainApp = MainApp();
	mainApp.Run(config);

	return 0;
}