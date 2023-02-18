#include "Precompiled.h"
#include "Texture.h"

#include "GraphicsSystem.h"
#include "DirectXTK/Inc/WICTextureLoader.h"

void NEng::Texture::UnbindPS(uint32_t slot)
{
	static ID3D11ShaderResourceView* dummy = nullptr;
	GraphicsSystem::Get()->GetContext()->PSSetShaderResources(slot, 1, &dummy);
}

NEng::Texture::~Texture()
{
	if (mShaderResourceView != nullptr)
		throw std::exception("texture -- Termiante must be called before detruction");
}

NEng::Texture::Texture(Texture&& t) noexcept :
	mShaderResourceView(t.mShaderResourceView)
{
	t.mShaderResourceView = nullptr;
}

NEng::Texture& NEng::Texture::operator=(Texture&& t) noexcept 
	
{
	mShaderResourceView = t.mShaderResourceView;
	t.mShaderResourceView = nullptr;
	return *this;
}

void NEng::Texture::Initialize(const std::filesystem::path& filename)
{
	auto device = GraphicsSystem::Get()->GetDevice();
	auto context = GraphicsSystem::Get()->GetContext();
	auto hr = DirectX::CreateWICTextureFromFile(device, context, filename.generic_wstring().c_str(), nullptr, &mShaderResourceView);
}

void NEng::Texture::Initialize(uint32_t width, uint32_t height, Format format)
{
}

void NEng::Texture::Terminate()
{
	SafeRelease(mShaderResourceView);
}

void NEng::Texture::BindVS(uint32_t slot) const
{
	GraphicsSystem::Get()->GetContext()->VSSetShaderResources(slot, 1, &mShaderResourceView);
}

void NEng::Texture::BindPS(uint32_t slot) const
{
	GraphicsSystem::Get()->GetContext()->PSSetShaderResources(slot, 1, &mShaderResourceView);
}

inline DXGI_FORMAT NEng::Texture::GetDXGIFormat(const Format& format)
{
	switch (format)
	{
	default:
	case NEng::Texture::Format::RGBA_U8:   return DXGI_FORMAT_R8G8B8A8_UINT;	
	case NEng::Texture::Format::RGBA_U32:  return DXGI_FORMAT_R32G32B32A32_UINT;
	}
}
