#include "Precompiled.h"
#include "RenderTarget.h"

#include "GraphicsSystem.h"

namespace NEng
{
	void RenderTarget::Initialize(const std::filesystem::path& filename)
	{

	}

	void RenderTarget::Initialize(uint32_t width, uint32_t height, Format format)
	{
		D3D11_TEXTURE2D_DESC desc;
		desc.Width = width;
		desc.Height = height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = GetDXGIFormat(format);
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		ID3D11Texture2D* texture = nullptr;
		auto device = GraphicsSystem::Get()->GetDevice();
		auto hr = device->CreateTexture2D(&desc, nullptr, &texture);
		if (!SUCCEEDED(hr))
			throw CreateException("RenderTarget -- Failed To Create Texture resource", __FILE__, __LINE__).what();

		hr = device->CreateShaderResourceView(texture, nullptr, &mShaderResourceView);
		if (!SUCCEEDED(hr))
			throw CreateException("RenderTarget -- Failed To Create Shader resource", __FILE__, __LINE__).what();

		hr = device->CreateRenderTargetView(texture, nullptr, &mRenderTargetView);
		if (!SUCCEEDED(hr))
			throw CreateException("RenderTarget -- Failed To Target View", __FILE__, __LINE__).what();

		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		hr = device->CreateTexture2D(&desc, nullptr, &texture);
		if (!SUCCEEDED(hr))
			throw CreateException("RenderTarget -- Failed To Create Texture resource", __FILE__, __LINE__).what();

		hr = device->CreateDepthStencilView(texture, nullptr, &mDepthStencilView);
		if (!SUCCEEDED(hr))
			throw CreateException("RenderTarget -- Failed To Create Depth Stencil resource", __FILE__, __LINE__).what();

		SafeRelease(texture);


		mViewport.TopLeftX = 0.0f;
		mViewport.TopLeftY = 0.0f;
		mViewport.Width = (float)width;
		mViewport.Height = (float)height;
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;
	}

	void RenderTarget::Terminate()
	{
		Texture::Terminate();

		SafeRelease(mRenderTargetView);
		SafeRelease(mDepthStencilView);
	}

	void RenderTarget::BeginRender(const Color& clearColor)
	{
		auto context = GraphicsSystem::Get()->GetContext();

		UINT numViewports = 1;
		context->OMGetRenderTargets(1, &mOldRenderTargetView, &mOldDepthStencilView);
		context->RSGetViewports(&numViewports, &mOldViewport);

		context->ClearRenderTargetView(mRenderTargetView, &clearColor.r);
		context->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		context->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
		context->RSSetViewports(1, &mViewport);
	}


	void RenderTarget::EndRender()
	{
		auto context = GraphicsSystem::Get()->GetContext();
		context->OMSetRenderTargets(1, &mOldRenderTargetView, mOldDepthStencilView);
		context->RSSetViewports(1, &mOldViewport);
	}
	RenderTarget::~RenderTarget()
	{
		if (mRenderTargetView != nullptr)
			throw CreateException("Render Target has not been released", __FILE__, __LINE__).what();
	}
}
