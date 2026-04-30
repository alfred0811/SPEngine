#include "Precompiled.h"
#include "GraphicsSystem.h"

using namespace SPEngine;
using namespace SPEngine::Graphics;

namespace
{
	std::unique_ptr<GraphicsSystem> sGraphicsSystem;
	Core::WindowMessageHandler sWindowMessageHandler;
}

LRESULT CALLBACK GraphicsSystem::GraphicsSystemMessageHandler(HWND win, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (sGraphicsSystem != nullptr)
	{
		switch (msg)
		{
			case WM_SIZE:
			{
				const uint32_t width = static_cast<uint32_t>(LOWORD(lParam));
				const uint32_t height = static_cast<uint32_t>(HIWORD(lParam));
				sGraphicsSystem->Resize(width, height);
				break;
			}
		}
	}
	return sWindowMessageHandler.ForwardMessage(win, msg, wParam, lParam);
}

// singleton setup/manage code
void GraphicsSystem::StaticInitialize(HWND window, bool fullScreen)
{
	ASSERT(sGraphicsSystem == nullptr, "GraphicsSystem: is already initialized!");
	sGraphicsSystem = std::make_unique<GraphicsSystem>();
	sGraphicsSystem->Initialize(window, fullScreen);
}
void GraphicsSystem::StaticTerminate()
{
	if (sGraphicsSystem != nullptr)
	{
		sGraphicsSystem->Terminate();
		sGraphicsSystem.reset();
	}
}
GraphicsSystem* GraphicsSystem::Get()
{
	ASSERT(sGraphicsSystem != nullptr, "GraphicsSystem: is not initialized!");
	return sGraphicsSystem.get();
}

GraphicsSystem::~GraphicsSystem()
{
	ASSERT(mD3DDevice == nullptr && mImmediateContext == nullptr, "GraphicsSystem: must be terminated!");
}

void GraphicsSystem::Initialize(HWND window, bool fullScreen)
{
	RECT clientRect = {};
	GetClientRect(window, &clientRect);
	UINT width = (UINT)(clientRect.right - clientRect.left);
	UINT height = (UINT)(clientRect.bottom - clientRect.top);

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !fullScreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&mSwapChain,
		&mD3DDevice,
		nullptr,
		&mImmediateContext);

	ASSERT(SUCCEEDED(hr), "GraphicsSystem: failed to initialized device or swap chain");
	mSwapChain->GetDesc(&mSwapChainDesc);

	Resize(GetBackBufferWidth(), GetBackBufferHeight());

	sWindowMessageHandler.Hook(window, GraphicsSystemMessageHandler);
}

void GraphicsSystem::Terminate()
{
	SafeRelease(mDepthStencilView);
	SafeRelease(mDepthStencilBuffer);
	SafeRelease(mRenderTargetView);
	SafeRelease(mSwapChain);
	SafeRelease(mImmediateContext);
	SafeRelease(mD3DDevice);
}

void GraphicsSystem::BeginRender()
{
	mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	mImmediateContext->ClearRenderTargetView(mRenderTargetView, (FLOAT*)(&mClearColor));
	mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}

void GraphicsSystem::EndRender()
{
	mSwapChain->Present(mVSync, 0);
}

void GraphicsSystem::ToggleFullScreen()
{
	BOOL fullScreen;
	mSwapChain->GetFullscreenState(&fullScreen, nullptr);
	mSwapChain->SetFullscreenState(!fullScreen, nullptr);
}
void GraphicsSystem::Resize(uint32_t width, uint32_t height)
{

}

void GraphicsSystem::ResetRenderTarget()
{

}

void GraphicsSystem::ResetViewport()
{

}

void GraphicsSystem::SetClearColor(const Color& color)
{

}

void GraphicsSystem::SetVSync(bool vSync)
{

}

uint32_t GraphicsSystem::GetBackBufferWidth() const
{

}

uint32_t GraphicsSystem::GetBackBufferHeight() const
{

}

float GraphicsSystem::GetBackBufferAspectRatio() const
{

}

ID3D11Device* GraphicsSystem::GetDevice()
{

}

ID3D11DeviceContext* GraphicsSystem::GetContext()
{

}