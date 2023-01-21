#pragma once

#include "Common.h"
#include "Colors.h"

namespace NEng
{
	class GraphicsSystem final
	{
	public:
		static void StaticInitialize(HWND window, bool fullscreen);
		static void StaticTerminate();
		static GraphicsSystem* Get();

		GraphicsSystem() = default;
		~GraphicsSystem() {}

		GraphicsSystem(const GraphicsSystem& g) = delete;
		GraphicsSystem(const GraphicsSystem&& g) = delete;
		GraphicsSystem& operator=(const GraphicsSystem& g) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&& g) = delete;

		void Initatilze(HWND window, bool fullscreen);
		void Terminate();

		void BeginRender();
		void EndRender();

		void ToggleFullscreen();
		void Resize(uint32_t width, uint32_t height);

		void ResetRenderTarget();
		void ResetViewport();

		void SetClearColor(const Color& c);
		void SetVSync(bool vsync);

		uint32_t GetBackBufferWidth() const;
		uint32_t GetBackBufferHeight() const;
		float GetbackBufferRatio() const;

	private:
		static LRESULT CALLBACK GraphicsSystemMessageHandler(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

		friend ID3D11Device* GetDevice();
		friend ID3D11DeviceContext* GetContext();

		ID3D11Device* mD3DDevice = nullptr;
		ID3D11DeviceContext* mImmediateContext = nullptr;

		IDXGISwapChain* mSwapChain = nullptr;
		ID3D11RenderTargetView* mRenderTargetView = nullptr;

		ID3D11Texture2D* mDepthStencilBuffer = nullptr;
		ID3D11DepthStencilView* mDepthStencilView = nullptr;

		DXGI_SWAP_CHAIN_DESC mSwapChainDesc{};
		D3D11_VIEWPORT mViewport{};

		Color mClearColor = Colors::Black;
		UINT mVsync = 1;

	public:
		ID3D11Device* GetDevice() const { return mD3DDevice; }
		ID3D11DeviceContext* GetContext() const { return mImmediateContext; };

	};
}
