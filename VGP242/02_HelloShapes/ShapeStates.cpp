#include "ShapeStates.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;
using namespace SPEngine::Input;

void ShapeStates::Initialize()
{
	// create shape
	CreateShape();
	mMeshBuffer.Initialize(mVertices.data(), sizeof(VertexPC), mVertices.size());

	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoColor.fx";
	mVertexShader.Initialize<VertexPC>(shaderPath);
	mPixelShader.Initialize(shaderPath);
}
void ShapeStates::Terminate()
{
	mVertices.clear();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mMeshBuffer.Terminate();
	
}
void ShapeStates::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::UP))
	{
		MainApp().ChangeState("QuadState");
	}
}
void ShapeStates::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mMeshBuffer.Render();
}
void ShapeStates::CreateShape()
{
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f }, { SPEngine::Graphics::Colors::Red } });
	mVertices.push_back({ { 0.0f,  0.5f, 0.0f }, { SPEngine::Graphics::Colors::Green } });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f }, { SPEngine::Graphics::Colors::Blue } });
}

void QuadState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::DOWN))
	{
		MainApp().ChangeState("ShapeStates");
	}
}

void QuadState::CreateShape()
{
	// 3 vertices is a triangle
	// vertices are clockwise (otherwise normal is away from camera
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f }, { SPEngine::Graphics::Colors::Red } });
	mVertices.push_back({ {-0.5f,  0.5f, 0.0f }, { SPEngine::Graphics::Colors::Green } });
	mVertices.push_back({ { 0.5f,  0.5f, 0.0f }, { SPEngine::Graphics::Colors::Blue } });

	// second triangle
	mVertices.push_back({ {-0.5f, -0.5f, 0.0f }, { SPEngine::Graphics::Colors::Red } });
	mVertices.push_back({ { 0.5f,  0.5f, 0.0f }, { SPEngine::Graphics::Colors::Blue } });
	mVertices.push_back({ { 0.5f, -0.5f, 0.0f }, { SPEngine::Graphics::Colors::Green } });
}