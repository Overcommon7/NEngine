#include "Precompiled.h"
#include "GraphicsSystem.h"

namespace NEng
{
    namespace
    {
        std::unique_ptr<GraphicsSystem> sGraphicsSystem;
        WindowMessageHandler sWindowMessageHandler;
    }
}

void NEng::GraphicsSystem::Initatilze(HWND window, bool fullscreen)
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
    swapChainDesc.Windowed = !fullscreen;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (
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
        &mImmediateContext
    );

    mSwapChain->GetDesc(&mSwapChainDesc);
    Resize(GetBackBufferWidth(), GetBackBufferHeight());
    sWindowMessageHandler.Hook(window, GraphicsSystemMessageHandler);
}

void NEng::GraphicsSystem::Terminate()
{  
    SafeRelease(mDepthStencilView);
    SafeRelease(mDepthStencilBuffer);
    SafeRelease(mRenderTargetView);
    SafeRelease(mSwapChain);
    SafeRelease(mImmediateContext);
    SafeRelease(mD3DDevice);
}

void NEng::GraphicsSystem::BeginRender()
{
    mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
    mImmediateContext->ClearRenderTargetView(mRenderTargetView, (FLOAT*)(&mClearColor));
    mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0.0f);
}

void NEng::GraphicsSystem::EndRender()
{
    mSwapChain->Present(mVsync, 0);
}

void NEng::GraphicsSystem::ToggleFullscreen()
{
    BOOL fullscreen;
    mSwapChain->GetFullscreenState(&fullscreen, nullptr);
    mSwapChain->SetFullscreenState(!fullscreen, nullptr);
}

void NEng::GraphicsSystem::Resize(uint32_t width, uint32_t height)
{
    mImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);

    SafeRelease(mRenderTargetView);
    SafeRelease(mDepthStencilView);

    HRESULT hr;
    if (width != GetBackBufferWidth() || height != GetBackBufferHeight())
    {
        hr = mSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
        mSwapChain->GetDesc(&mSwapChainDesc);
    }

    ID3D11Texture2D* backBuffer = nullptr;
    hr = mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    hr = mD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView);

    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = GetBackBufferWidth();
    descDepth.Height = GetBackBufferHeight();
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;

    hr = mD3DDevice->CreateTexture2D(&descDepth, nullptr, &mDepthStencilBuffer);

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    
    hr = mD3DDevice->CreateDepthStencilView(mDepthStencilBuffer, &descDSV, &mDepthStencilView);

    mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

    mViewport.Width = (float)GetBackBufferWidth();
    mViewport.Height = (float)GetBackBufferHeight();
    mViewport.MaxDepth = 1.0f;
    mViewport.MinDepth = 0.0f;
    mViewport.TopLeftX = 0;
    mViewport.TopLeftY = 0;
    mImmediateContext->RSSetViewports(1, &mViewport);
}

void NEng::GraphicsSystem::ResetRenderTarget()
{
    mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}

void NEng::GraphicsSystem::ResetViewport()
{
    mImmediateContext->RSSetViewports(1, &mViewport);
}

void NEng::GraphicsSystem::SetClearColor(const Color& c)
{
    mClearColor = c;
}

void NEng::GraphicsSystem::SetVSync(bool vsync)
{
    mVsync = (int)vsync;
}

uint32_t NEng::GraphicsSystem::GetBackBufferWidth() const
{
    return mSwapChainDesc.BufferDesc.Width;
}

uint32_t NEng::GraphicsSystem::GetBackBufferHeight() const
{
    return mSwapChainDesc.BufferDesc.Height;
}

float NEng::GraphicsSystem::GetbackBufferRatio() const
{
    return (float)GetBackBufferWidth() / (float)GetBackBufferHeight();
}

LRESULT NEng::GraphicsSystem::GraphicsSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (sGraphicsSystem && message == WM_SIZE)
    {
        const uint32_t width = (uint32_t)(LOWORD(lParam));
        const uint32_t height  = (uint32_t)(HIWORD(lParam));
        sGraphicsSystem->Resize(width, height);
    }

    return sWindowMessageHandler.FowardMessage(window,  message,  wParam,  lParam);
}

ID3D11Device* NEng::GetDevice()
{
    return nullptr;
}

ID3D11DeviceContext* NEng::GetContext()
{
    return nullptr;
}

void NEng::GraphicsSystem::StaticInitialize(HWND window, bool fullscreen)
{
    sGraphicsSystem = std::make_unique<GraphicsSystem>();
    sGraphicsSystem->Initatilze(window, fullscreen);
}

void NEng::GraphicsSystem::StaticTerminate()
{
    sGraphicsSystem->Terminate();
    sGraphicsSystem.reset();
}

NEng::GraphicsSystem* NEng::GraphicsSystem::Get()
{
    return sGraphicsSystem.get();
}
