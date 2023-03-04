#pragma once

#include "Colors.h"
#include "Texture.h"

namespace NEng
{
    class RenderTarget final : public Texture
    {
    public:
        virtual void Initialize(const std::filesystem::path& filename) override;
        virtual void Initialize(uint32_t width, uint32_t height, Format format) override;
        virtual void Terminate() override;

        void BeginRender(const Color& clearColor = Colors::Black);
        void EndRender();

        virtual ~RenderTarget();

    private:
        ID3D11RenderTargetView* mOldRenderTargetView = nullptr;
        ID3D11DepthStencilView* mOldDepthStencilView = nullptr;
        D3D11_VIEWPORT mOldViewport = {};
       
        ID3D11RenderTargetView* mRenderTargetView = nullptr;
        ID3D11DepthStencilView* mDepthStencilView = nullptr;
        D3D11_VIEWPORT mViewport = {};
    };
}
