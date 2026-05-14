#include <SPEngine/Inc/SPEngine.h>
#include "ShapeStates.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	SPEngine::AppConfig config;
	config.appName = L"Hello Cube";

	SPEngine::App& myApp = SPEngine::MainApp();

	// need states
	myApp.AddState<ShapeStates>("ShapeStates");
	myApp.Run(config);

	return 0;
}