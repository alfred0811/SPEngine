#include "Precompiled.h"
#include "SPEngine.h"

SPEngine::App& SPEngine::MainApp()
{
	static App sApp;
	return sApp;
}