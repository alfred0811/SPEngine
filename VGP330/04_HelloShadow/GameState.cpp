#include "GameState.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;
using namespace SPEngine::Input;

void GameState::Initialize()
{
	// set up camera
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// set up light
	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.4f, 0.4f, 0.4f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };


	// set up render object
	mCharacter.Initialize(L"Character01/Ty.model");
	mCharacter.transform.position = { 0.0f, 0.0f, 0.0f };

	mCharacter2.Initialize(L"Character02/Ch14_nonPBR.model");
	mCharacter2.transform.position = { -2.0f, 0.0f, 0.0f };

	mCharacter3.Initialize(L"Character03/Big_Vegas.model");
	mCharacter3.transform.position = { 2.0f, 0.0f, 0.0f };

	Mesh goundMesh = MeshBuilder::CreatePlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(goundMesh);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture("misc/concrete.jpg");

	// set up the effect
	std::filesystem::path shaderPath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderPath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);
	mStandardEffect.SetShadowMap(mShadowEffect.GetDepthMap());
	mStandardEffect.SetLightCamera(mShadowEffect.GetLightCamera());

	// set up shadow effect
	mShadowEffect.Initialize();
	mShadowEffect.SetDirectionalLight(mDirectionalLight);
}
void GameState::Terminate()
{
	mShadowEffect.Terminate();
	mGround.Terminate();
	mCharacter.Terminate();
	mCharacter2.Terminate();
	mCharacter3.Terminate();
	mStandardEffect.Terminate();
}
void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}
void GameState::Render()
{
	// render the scene into the render target
	mShadowEffect.Begin();
		mShadowEffect.Render(mCharacter);
		mShadowEffect.Render(mCharacter2);
		mShadowEffect.Render(mCharacter3);
	mShadowEffect.End();

	mStandardEffect.Begin();
		mStandardEffect.Render(mGround);
		mStandardEffect.Render(mCharacter);
		mStandardEffect.Render(mCharacter2);
		mStandardEffect.Render(mCharacter3);
	mStandardEffect.End();
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.1f))
		{
			mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
		}
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}
	
	mStandardEffect.DebugUI();
	mShadowEffect.DebugUI();
	ImGui::End();
}
void GameState::UpdateCamera(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}

	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}