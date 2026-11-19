#include "GameState.h"

using namespace SPEngine;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Shadow";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);
	return 0;
}