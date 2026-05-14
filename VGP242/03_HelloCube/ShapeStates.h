#pragma once

#include <SPEngine/Inc/SPEngine.h>

class ShapeStates : public SPEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();

	using Vertices = std::vector<SPEngine::Graphics::VertexPC>;
	Vertices mVertices;

	SPEngine::Graphics::MeshBuffer mMeshBuffer;
	SPEngine::Graphics::VertexShader mVertexShader;
	SPEngine::Graphics::PixelShader mPixelShader;

	SPEngine::Graphics::Camera mCamera;
	SPEngine::Graphics::ConstantBuffer mConstantBuffer;
};