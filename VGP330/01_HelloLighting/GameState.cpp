#include "GameState.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;
using namespace SPEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.4f, 0.4f, 0.4f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };


	// set up render object
	Mesh mesh = MeshBuilder::CreateSphere(30, 30, 1.0f);
	TextureManager* tm = TextureManager::Get();

	// Earth sphere
	mEarthRenderObject.meshBuffer.Initialize(mesh);
	mEarthRenderObject.transform.position = { -2.5f, 1.0f, 0.0f };
	mEarthRenderObject.diffuseMapId = tm->LoadTexture("earth.jpg");
	mEarthRenderObject.specMapId = tm->LoadTexture("earth_spec.jpg");
	mEarthRenderObject.normMapId = tm->LoadTexture("earth_normal.jpg");
	mEarthRenderObject.bumpMapId = tm->LoadTexture("earth_bump.jpg");

	// Brick wall sphere
	mBrickRenderObject.meshBuffer.Initialize(mesh);
	mBrickRenderObject.transform.position = { 0.0f, 1.0f, 0.0f };
	mBrickRenderObject.diffuseMapId = tm->LoadTexture("broken_brick_wall_diff.jpg");
	mBrickRenderObject.normMapId = tm->LoadTexture("broken_brick_wall_norm.png");

	// brown mud dry sphere
	mMudRenderObject.meshBuffer.Initialize(mesh);
	mMudRenderObject.transform.position = { 2.5f, 1.0f, 0.0f };
	mMudRenderObject.diffuseMapId = tm->LoadTexture("brown_mud_dry_diff.jpg");
	mMudRenderObject.normMapId = tm->LoadTexture("brown_mud_dry_norm.png");
	mMudRenderObject.bumpMapId = tm->LoadTexture("brown_mud_dry_bump.jpg");


	// set up the effect
	std::filesystem::path shaderPath = L"../../Assets/Shaders/Standard.fx";
	mStandardEffect.Initialize(shaderPath);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	// set up cel effect
	shaderPath = L"../../Assets/Shaders/CelShader.fx";
	mStandardEffectCel.Initialize(shaderPath);
	mStandardEffectCel.SetCamera(mCamera);
	mStandardEffectCel.SetDirectionalLight(mDirectionalLight);

	// initialize render target
	const uint32_t size = 512;
	mRenderTarget.Initialize(size, size, RenderTarget::Format::RGBA_U32);
}
void GameState::Terminate()
{
	mRenderTarget.Terminate();
	mStandardEffect.Terminate();
	mStandardEffectCel.Terminate();
	mEarthRenderObject.Terminate();
	mBrickRenderObject.Terminate();
	mMudRenderObject.Terminate();
}
void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
}
void GameState::Render()
{
	SimpleDraw::AddGroundPlane(20.0f, Colors::LightGray);
	SimpleDraw::Render(mCamera);

	if (mUseCellShading)
	{
		mStandardEffectCel.Begin();
			mStandardEffectCel.Render(mEarthRenderObject);
			mStandardEffectCel.Render(mBrickRenderObject);
			mStandardEffectCel.Render(mMudRenderObject);
		mStandardEffectCel.End();
	}
	else
	{
		mStandardEffect.Begin();
			mStandardEffect.Render(mEarthRenderObject);
			mStandardEffect.Render(mBrickRenderObject);
			mStandardEffect.Render(mMudRenderObject);
		mStandardEffect.End();
	}

	// render target render
	mRenderTarget.BeginRender(); // tell gpu to render here
		mStandardEffect.Begin();
			mStandardEffect.Render(mEarthRenderObject);
			mStandardEffect.Render(mBrickRenderObject);
			mStandardEffect.Render(mMudRenderObject);
		mStandardEffect.End();
	mRenderTarget.EndRender(); // tell gpu to render to window again
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
	if (ImGui::CollapsingHeader("Earth Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Emissive##EarthMaterial", &mEarthRenderObject.material.emissive.r);
		ImGui::ColorEdit4("Ambient##EarthMaterial", &mEarthRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##EarthMaterial", &mEarthRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##EarthMaterial", &mEarthRenderObject.material.specular.r);
		ImGui::DragFloat("Shininess##EarthMaterial", &mEarthRenderObject.material.shininess, 0.01f, 0.0f, 1000.0f);
	}
	if (ImGui::CollapsingHeader("Brick Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Emissive##BrickMaterial", &mBrickRenderObject.material.emissive.r);
		ImGui::ColorEdit4("Ambient##BrickMaterial", &mBrickRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##BrickMaterial", &mBrickRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##BrickMaterial", &mBrickRenderObject.material.specular.r);
		ImGui::DragFloat("Shininess##BrickMaterial", &mBrickRenderObject.material.shininess, 0.01f, 0.0f, 1000.0f);
	}
	if (ImGui::CollapsingHeader("Mud Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Emissive##MudMaterial", &mMudRenderObject.material.emissive.r);
		ImGui::ColorEdit4("Ambient##MudMaterial", &mMudRenderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##MudMaterial", &mMudRenderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##MudMaterial", &mMudRenderObject.material.specular.r);
		ImGui::DragFloat("Shininess##MudMaterial", &mMudRenderObject.material.shininess, 0.01f, 0.0f, 1000.0f);
	}
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 128, 128 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 });
	ImGui::Checkbox("UseCelShading", &mUseCellShading);
	if (mUseCellShading)
	{
		mStandardEffectCel.DebugUI();
	}
	else
	{
		mStandardEffect.DebugUI();
	}
	
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