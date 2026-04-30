#include "ShapeStates.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;

void ShapeStates::Initialize()
{
	// create shape
	CreateShape();

	auto device = GraphicsSystem::Get()->GetDevice();

	// create a buffer to store the vertices (mesh buffer)
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = static_cast<UINT>(mVertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = mVertices.data();
	HRESULT hr = device->CreateBuffer(&bufferDesc, &initData, &mVertexBuffer);
	ASSERT(SUCCEEDED(hr), "ShapeStates: failed to create mesh buffer");
	//===========================================================================

	// Bind the shader file functions to the appropiate shader objects
	// vertex shader
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoSomething.fx";
}
void ShapeStates::Terminate()
{

}
void ShapeStates::Update(float deltaTime)
{

}
void ShapeStates::Render()
{

}
void ShapeStates::CreateShape()
{
	mVertices.push_back({ { -0.5f, -0.5f, 0.0f } });
	mVertices.push_back({ { 0.0f, -0.5f, 0.0f } });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f } });
}