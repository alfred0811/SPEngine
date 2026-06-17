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
	struct Object
	{
		SPEngine::Math::Matrix4 matWorld = SPEngine::Math::Matrix4::Identity;
		SPEngine::Graphics::MeshBuffer meshBuffer;
		SPEngine::Graphics::TextureId textureId = 0;
	};

	// Camera
	void UpdateCamera(float deltaTime);

	SPEngine::Graphics::Camera mCamera;
	SPEngine::Graphics::Camera mRenderTargetCamera;
	
	// GPU
	SPEngine::Graphics::VertexShader mVertexShader;
	SPEngine::Graphics::PixelShader mPixelShader;
	SPEngine::Graphics::Sampler mSampler;
	SPEngine::Graphics::ConstantBuffer mConstantBuffer;

	// Render objects
	Object mSpace;
	Object mSun;
	Object mMercury;
	Object mVenus;
	Object mEarth;
	Object mMars;
	Object mJupiter;
	Object mSaturn;
	Object mUranus;
	Object mNeptune;
	Object mPluto;
	Object mMoon;
};