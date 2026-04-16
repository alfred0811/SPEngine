#include "Precompiled.h"
#include "App.h"

using namespace SPEngine;
using namespace SPEngine::Core;

void App::Run(const AppConfig& config)
{
	// start the application
	LOG("App Started");

	// for all systems we build, initialize all singletons
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight);

	// run the application
	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();
		if (!myWindow.IsActive())
		{
			Quit();
			continue;
		}
	}

	// for all systems we build, terminate all singletons
	// close the application
	myWindow.Terminate();
	LOG("App Ended");
}

void App::Quit()
{
	mRunning = false;
}