#include "GameState.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;
using namespace SPEngine::Input;

enum class CameraTarget
{
	FreeCamera,
	Sun,
	Mercury,
	Venus,
	Earth,
	Mars,
	Jupiter,
	Saturn,
	Uranus,
	Neptune,
	Pluto,
	Moon,
};

CameraTarget gCurrentTarget = CameraTarget::FreeCamera;
const char* gTargetNames[] = { "Free Camera", "Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Pluto", "Moon" };

bool gDrawOrbit = true;
float gPlanetRotationSpeed = 0.01f;
float gOrbitalRotationSpeed = 0.01f;
float gCameraDistance = 3.0f;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	
	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderPath);
	mPixelShader.Initialize(shaderPath);
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	// initialize render object
	MeshPX space = MeshBuilder::CreateSkySpherePX(60, 60, 20.0f);
	mSpace.meshBuffer.Initialize(space);

	MeshPX sun = MeshBuilder::CreateSpherePX(60, 60, 1.0f);
	mSun.meshBuffer.Initialize(sun);

	MeshPX mercury = MeshBuilder::CreateSpherePX(60, 60, 0.2f);
	mMercury.meshBuffer.Initialize(mercury);

	MeshPX venus = MeshBuilder::CreateSpherePX(60, 60, 0.5f);
	mVenus.meshBuffer.Initialize(venus);

	MeshPX earth = MeshBuilder::CreateSpherePX(60, 60, 0.5f);
	mEarth.meshBuffer.Initialize(earth);

	MeshPX mars = MeshBuilder::CreateSpherePX(60, 60, 0.3f);
	mMars.meshBuffer.Initialize(mars);

	MeshPX jupiter = MeshBuilder::CreateSpherePX(60, 60, 0.8f);
	mJupiter.meshBuffer.Initialize(jupiter);

	MeshPX saturn = MeshBuilder::CreateSpherePX(60, 60, 0.6f);
	mSaturn.meshBuffer.Initialize(saturn);

	MeshPX uranus = MeshBuilder::CreateSpherePX(60, 60, 0.2f);
	mUranus.meshBuffer.Initialize(uranus);

	MeshPX neptune = MeshBuilder::CreateSpherePX(60, 60, 0.4f);
	mNeptune.meshBuffer.Initialize(neptune);

	MeshPX pluto = MeshBuilder::CreateSpherePX(60, 60, 0.1f);
	mPluto.meshBuffer.Initialize(pluto);

	MeshPX moon = MeshBuilder::CreateSpherePX(60, 60, 0.2f);
	mMoon.meshBuffer.Initialize(moon);

	// assign textures
	mSpace.textureId = TextureManager::Get()->LoadTexture(L"space.jpg");
	mSun.textureId = TextureManager::Get()->LoadTexture(L"sun.jpg");
	mMercury.textureId = TextureManager::Get()->LoadTexture(L"planets/mercury.jpg");
	mVenus.textureId = TextureManager::Get()->LoadTexture(L"planets/venus.jpg");
	mEarth.textureId = TextureManager::Get()->LoadTexture(L"earth.jpg");
	mMars.textureId = TextureManager::Get()->LoadTexture(L"planets/mars.jpg");
	mJupiter.textureId = TextureManager::Get()->LoadTexture(L"planets/jupiter.jpg");
	mSaturn.textureId = TextureManager::Get()->LoadTexture(L"planets/saturn.jpg");
	mUranus.textureId = TextureManager::Get()->LoadTexture(L"planets/uranus.jpg");
	mNeptune.textureId = TextureManager::Get()->LoadTexture(L"planets/neptune.jpg");
	mPluto.textureId = TextureManager::Get()->LoadTexture(L"planets/pluto.jpg");
	mMoon.textureId = TextureManager::Get()->LoadTexture(L"planets/pluto.jpg");

	// assign starting positions
	mMercury.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 2.0f });
	mVenus.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 3.5f });
	mEarth.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 5.0f });
	mMars.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 6.5f });
	mJupiter.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 8.0f });
	mSaturn.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 9.5f });
	mUranus.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 11.0f });
	mNeptune.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 12.5f });
	mPluto.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 14.0f });
	mMoon.matWorld = Math::Matrix4::Translation({ 0.0f, 0.0f, 0.8f });

	constexpr uint32_t size = 512;
}

void GameState::Terminate()
{
	// Textures ===============================================================
	TextureManager::Get()->ReleaseTexture(mSpace.textureId);
	TextureManager::Get()->ReleaseTexture(mSun.textureId);
	TextureManager::Get()->ReleaseTexture(mMercury.textureId);
	TextureManager::Get()->ReleaseTexture(mVenus.textureId);
	TextureManager::Get()->ReleaseTexture(mEarth.textureId);
	TextureManager::Get()->ReleaseTexture(mMars.textureId);
	TextureManager::Get()->ReleaseTexture(mJupiter.textureId);
	TextureManager::Get()->ReleaseTexture(mSaturn.textureId);
	TextureManager::Get()->ReleaseTexture(mUranus.textureId);
	TextureManager::Get()->ReleaseTexture(mNeptune.textureId);
	TextureManager::Get()->ReleaseTexture(mPluto.textureId);
	TextureManager::Get()->ReleaseTexture(mMoon.textureId);
	// ==========================================================================

	// MeshBuffers ===============================================================
	mSpace.meshBuffer.Terminate();
	mSun.meshBuffer.Terminate();
	mMercury.meshBuffer.Terminate();
	mVenus.meshBuffer.Terminate();
	mEarth.meshBuffer.Terminate();
	mMars.meshBuffer.Terminate();
	mJupiter.meshBuffer.Terminate();
	mSaturn.meshBuffer.Terminate();
	mUranus.meshBuffer.Terminate();
	mNeptune.meshBuffer.Terminate();
	mPluto.meshBuffer.Terminate();
	mMoon.meshBuffer.Terminate();
	// ==========================================================================

	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

Math::Vector3 GameState::GetPlanetPosition(int planetIndex) const
{
	switch (static_cast<CameraTarget>(planetIndex))
	{
	case CameraTarget::Sun:
		return Math::GetTranslation(mSun.matWorld);
	case CameraTarget::Mercury:
		return Math::GetTranslation(mMercury.matWorld);
	case CameraTarget::Venus:
		return Math::GetTranslation(mVenus.matWorld);
	case CameraTarget::Earth:
		return Math::GetTranslation(mEarth.matWorld);
	case CameraTarget::Mars:
		return Math::GetTranslation(mMars.matWorld);
	case CameraTarget::Jupiter:
		return Math::GetTranslation(mJupiter.matWorld);
	case CameraTarget::Saturn:
		return Math::GetTranslation(mSaturn.matWorld);
	case CameraTarget::Uranus:
		return Math::GetTranslation(mUranus.matWorld);
	case CameraTarget::Neptune:
		return Math::GetTranslation(mNeptune.matWorld);
	case CameraTarget::Pluto:
		return Math::GetTranslation(mPluto.matWorld);
	case CameraTarget::Moon:
		return Math::GetTranslation(mMoon.matWorld);
	default:
		return Math::Vector3::Zero;
	}
}

float GameState::GetPlanetViewDistance(int planetIndex) const
{
	switch (static_cast<CameraTarget>(planetIndex))
	{
	case CameraTarget::Sun:
		return 3.5f;
	case CameraTarget::Jupiter:
		return 2.5f;
	case CameraTarget::Saturn:
		return 2.0f;
	case CameraTarget::Neptune:
		return 1.5f;
	case CameraTarget::Venus:
	case CameraTarget::Earth:
		return 1.5f;
	case CameraTarget::Mars:
	case CameraTarget::Uranus:
		return 1.2f;
	case CameraTarget::Mercury:
	case CameraTarget::Moon:
	case CameraTarget::Pluto:
		return 0.8f;
	default:
		return 3.0f;
	}
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	// Orbit circles ===============================================================
	if (gDrawOrbit)
	{
		SimpleDraw::AddGroundCircle(60, 2.0f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 3.5f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 5.0f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 6.5f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 8.0f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 9.5f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 11.0f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 12.5f, Math::Vector3::Zero, Colors::White);
		SimpleDraw::AddGroundCircle(60, 14.0f, Math::Vector3::Zero, Colors::White);
	}
	// ==========================================================================


	// local rotation ===============================================================
	mSun.matWorld = Math::Matrix4::RotationY((0.005f + gPlanetRotationSpeed) * deltaTime) * mSun.matWorld;
	mMercury.matWorld = Math::Matrix4::RotationY((0.1f + gPlanetRotationSpeed) * deltaTime) * mMercury.matWorld;
	mVenus.matWorld = Math::Matrix4::RotationY((0.05f + gPlanetRotationSpeed) * deltaTime) * mVenus.matWorld;
	mEarth.matWorld = Math::Matrix4::RotationY((0.174533f + gPlanetRotationSpeed) * deltaTime) * mEarth.matWorld;
	mMars.matWorld = Math::Matrix4::RotationY((0.2f + gPlanetRotationSpeed) * deltaTime) * mMars.matWorld;
	mJupiter.matWorld = Math::Matrix4::RotationY((0.5f + gPlanetRotationSpeed) * deltaTime) * mJupiter.matWorld;
	mSaturn.matWorld = Math::Matrix4::RotationY((0.3f + gPlanetRotationSpeed) * deltaTime) * mSaturn.matWorld;
	mUranus.matWorld = Math::Matrix4::RotationY((0.1f + gPlanetRotationSpeed) * deltaTime) * mUranus.matWorld;
	mNeptune.matWorld = Math::Matrix4::RotationY((0.05f + gPlanetRotationSpeed) * deltaTime) * mNeptune.matWorld;
	mPluto.matWorld = Math::Matrix4::RotationY((0.008f + gPlanetRotationSpeed) * deltaTime) * mPluto.matWorld;
	// ==========================================================================


	// rotate around the sun ===============================================================
	mMercury.matWorld = mMercury.matWorld * Math::Matrix4::RotationY((0.4787f + gOrbitalRotationSpeed) * deltaTime);
	mVenus.matWorld = mVenus.matWorld * Math::Matrix4::RotationY((0.3502f + gOrbitalRotationSpeed) * deltaTime);
	mEarth.matWorld = mEarth.matWorld * Math::Matrix4::RotationY((0.2978f + gOrbitalRotationSpeed) * deltaTime);
	mMars.matWorld = mMars.matWorld * Math::Matrix4::RotationY((0.24077f + gOrbitalRotationSpeed) * deltaTime);
	mJupiter.matWorld = mJupiter.matWorld * Math::Matrix4::RotationY((0.1307f + gOrbitalRotationSpeed) * deltaTime);
	mSaturn.matWorld = mSaturn.matWorld * Math::Matrix4::RotationY((0.0969f + gOrbitalRotationSpeed) * deltaTime);
	mUranus.matWorld = mUranus.matWorld * Math::Matrix4::RotationY((0.0681f + gOrbitalRotationSpeed) * deltaTime);
	mNeptune.matWorld = mNeptune.matWorld * Math::Matrix4::RotationY((0.0543f + gOrbitalRotationSpeed) * deltaTime);
	mPluto.matWorld = mPluto.matWorld * Math::Matrix4::RotationY((0.0474f + gOrbitalRotationSpeed) * deltaTime);
	// =======================================================================================
	
	// Moon Rotation around the Earth ========================================================
	mMoonOrbitAngle += (0.0103f + gOrbitalRotationSpeed) * deltaTime;
	mMoonOrbitAngle += (0.0103f + gOrbitalRotationSpeed) * deltaTime;

	Math::Vector3 earthPos = Math::GetTranslation(mEarth.matWorld);
	Math::Matrix4 moonOrbit = Math::Matrix4::RotationY(mMoonOrbitAngle);
	Math::Matrix4 moonOffset = Math::Matrix4::Translation({ 0.0f, 0.0f, 0.8f });

	mMoon.matWorld = moonOffset * moonOrbit * Math::Matrix4::Translation(earthPos);
	// =======================================================================================

	// Camera transition logic ===============================================================
	if (mIsTransitioning)
	{
		mTransitionTime += deltaTime;
		float t = Math::Min(mTransitionTime / mTransitionDuration, 1.0f);

		// Smooth interpolation (ease in-out)
		t = t * t * (3.0f - 2.0f * t);

		Math::Vector3 newPosition = Math::Lerp(mCameraStartPos, mCameraTargetPos, t);
		mCamera.SetPosition(newPosition);

		if (t >= 1.0f)
		{
			mIsTransitioning = false;
		}
	}
	// ==========================================================================

	// Camera following logic ===============================================================
	if (gCurrentTarget != CameraTarget::FreeCamera)
	{
		Math::Vector3 targetPosition = GetPlanetPosition(static_cast<int>(gCurrentTarget));
		mRenderTargetCamera.SetLookAt(targetPosition);
		mCamera.SetLookAt(targetPosition);

		// Update camera position to maintain distance while following
		if (!mIsTransitioning)
		{
			Math::Vector3 cameraPos = mCamera.GetPosition();
			Math::Vector3 directionToPlanet = Math::Normalize(targetPosition - cameraPos);
			float currentDistance = Math::Distance(cameraPos, targetPosition);
			float desiredDistance = GetPlanetViewDistance(static_cast<int>(gCurrentTarget));
			float maxDistance = desiredDistance * 3.0f; // Allow moving back up to 3x the default distance

			// Only push camera back if it exceeds the maximum distance
			if (currentDistance > maxDistance)
			{
				Math::Vector3 desiredPosition = targetPosition - directionToPlanet * maxDistance;
				mCamera.SetPosition(Math::Lerp(cameraPos, desiredPosition, deltaTime * 2.0f));
			}
		}
	}
	// =======================================================================================
}

void GameState::Render()
{
	// prepare the GPU ===============================================================
	mVertexShader.Bind();
	mPixelShader.Bind();

	// sync buffer information
	mConstantBuffer.BindVS(0);
	mSampler.BindPS(0);

	// update buffer data
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	// ===============================================================

	// Render Space (background)
	Math::Matrix4 wvp = mSpace.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mSpace.textureId, 0);
	mSpace.meshBuffer.Render();

	// Render Sun
	wvp = mSun.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mSun.textureId, 0);
	mSun.meshBuffer.Render();

	// Render Mercury
	wvp = mMercury.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mMercury.textureId, 0);
	mMercury.meshBuffer.Render();

	// Render Venus
	wvp = mVenus.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mVenus.textureId, 0);
	mVenus.meshBuffer.Render();

	// Render Earth
	wvp = mEarth.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mEarth.textureId, 0);
	mEarth.meshBuffer.Render();

	// Render Moon
	wvp = mMoon.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mMoon.textureId, 0);
	mMoon.meshBuffer.Render();

	// Render Mars
	wvp = mMars.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mMars.textureId, 0);
	mMars.meshBuffer.Render();

	// Render Jupiter
	wvp = mJupiter.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mJupiter.textureId, 0);
	mJupiter.meshBuffer.Render();

	// Render Saturn
	wvp = mSaturn.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mSaturn.textureId, 0);
	mSaturn.meshBuffer.Render();

	// Render Uranus
	wvp = mUranus.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mUranus.textureId, 0);
	mUranus.meshBuffer.Render();

	// Render Neptune
	wvp = mNeptune.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mNeptune.textureId, 0);
	mNeptune.meshBuffer.Render();

	// Render Pluto
	wvp = mPluto.matWorld * matView * matProj;
	wvp = Math::Transpose(wvp);
	mConstantBuffer.Update(&wvp);
	TextureManager::Get()->BindPS(mPluto.textureId, 0);
	mPluto.meshBuffer.Render();

	SimpleDraw::Render(mCamera);
}
// float myVariable = 0.0f;
void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	// Planet Selection
	ImGui::Text("Camera Target");
	int currentTarget = static_cast<int>(gCurrentTarget);
	if (ImGui::Combo("##CameraTarget", &currentTarget, gTargetNames, IM_ARRAYSIZE(gTargetNames)))
	{
		gCurrentTarget = static_cast<CameraTarget>(currentTarget);
	}
	
	ImGui::Separator();

	// Orbit Toggle
	ImGui::Checkbox("Draw Orbits", &gDrawOrbit);

	ImGui::Separator();

	// Rotation Speed
	ImGui::SliderFloat("Orbital Rotation Speed", &gOrbitalRotationSpeed, 0.0f, 1.0f);
	// Reset button for orbital rotation speed
	if (ImGui::Button("Reset Orbital Rotation Speed"))
	{
		gOrbitalRotationSpeed = 0.01f;
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