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
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoColor.fx";

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(
		shaderFile.c_str(), 
		nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		"VS", "vs_5_0", 
		shaderFlags, 0, 
		&shaderBlob,
		&errorBlob);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "VertexShader: failed to compile vertex shader");

	hr = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(), 
		shaderBlob->GetBufferSize(), 
		nullptr, 
		&mVertexShader);
	ASSERT(SUCCEEDED(hr), "VertexShader: failed to create vertex shader");
	//=============================================================================

	// State what the vertex variables are
	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT});
	vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

	hr = device->CreateInputLayout(
		vertexLayout.data(), 
		static_cast<UINT>(vertexLayout.size()), 
		shaderBlob->GetBufferPointer(), 
		shaderBlob->GetBufferSize(), 
		&mInputLayout);
	ASSERT(SUCCEEDED(hr), "VertexShader: failed to create vertex input");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
	//=============================================================================

	// pixel shader
	hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hr), "PixelShader: failed to compile pixel shader");

	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	ASSERT(SUCCEEDED(hr), "PixelShader: failed to create pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}
void ShapeStates::Terminate()
{
	mVertices.clear();
	SafeRelease(mPixelShader);
	SafeRelease(mInputLayout);
	SafeRelease(mVertexShader);
	SafeRelease(mVertexBuffer);
}
void ShapeStates::Update(float deltaTime)
{
	
}
void ShapeStates::Render()
{
	auto context = GraphicsSystem::Get()->GetContext();
	// bind buffers
	context->VSSetShader(mVertexShader, nullptr, 0);
	context->IASetInputLayout(mInputLayout);
	context->PSSetShader(mPixelShader, nullptr, 0);

	// define the object data (how to read vertices)
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	context->Draw(static_cast<UINT>(mVertices.size()), 0);
}
void ShapeStates::CreateShape()
{
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f }, { SPEngine::Graphics::Colors::Red } });
	mVertices.push_back({ { 0.0f,  0.5f, 0.0f }, { SPEngine::Graphics::Colors::Green } });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f }, { SPEngine::Graphics::Colors::Blue } });
}