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

	struct Vertex
	{
		SPEngine::Math::Vector3 position;
		SPEngine::Graphics::Color color;
	};
	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	// info to pass to the graphics card
	// stores the data for the shape
	ID3D11Buffer* mVertexBuffer = nullptr;
	// what functions are called on the shader file
	ID3D11VertexShader* mVertexShader = nullptr;
	// what data am I expecting on the shader (position, color, texture...)
	ID3D11InputLayout* mInputLayout = nullptr;
	// what functions called on the shader file per pixel
	ID3D11PixelShader* mPixelShader = nullptr;
};