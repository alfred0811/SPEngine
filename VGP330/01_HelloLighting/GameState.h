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
	// Camera
	void UpdateCamera(float deltaTime);

	SPEngine::Graphics::Camera mCamera;
	SPEngine::Graphics::DirectionalLight mDirectionalLight;
	SPEngine::Graphics::StandardEffect mStandardEffect;
	SPEngine::Graphics::StandardEffect mStandardEffectCel;

	SPEngine::Graphics::RenderObject mRenderObject;
	bool mUseCellShading = false;
};