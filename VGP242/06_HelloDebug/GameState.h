#pragma once

#include <SPEngine/Inc/SPEngine.h>

class GameState : public SPEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;
private:
	void UpdateCamera(float deltaTime);

	SPEngine::Graphics::Camera mCamera;
};