#include <SPEngine/Inc/SPEngine.h>

using namespace SPEngine;
using namespace SPEngine::Core;
using namespace SPEngine::Input;

class MainState : public AppState
{
public:
	void Initialize() override
	{
		LOG("MainState: Initialize");
	}
	void Update(float deltaTime) override
	{
		if (InputSystem::Get()->IsKeyPressed(KeyCode::G))
		{
			MainApp().ChangeState("GameState");
		}
	}
	void Terminate() override
	{
		LOG("MainState: Terminate");
	}
};

class GameState : public AppState
{
public:
	void Initialize() override
	{
		LOG("GameState: Initialize");
	}
	void Update(float deltaTime) override
	{
		if (InputSystem::Get()->IsKeyPressed(KeyCode::M))
		{
			MainApp().ChangeState("MainState");
		}
	}
	void Terminate() override
	{
		LOG("GameState: Terminate");
	}
};

int WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello Window";

	App& mainApp = MainApp();
	mainApp.AddState<MainState>("MainState");
	mainApp.AddState<GameState>("GameState");
	mainApp.Run(config);

	return 0;
}