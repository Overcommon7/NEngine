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
		throw CreateException("Texture -- Termiante must be called before detruction", __FILE__, __LINE__).what();
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
	if (!SUCCEEDED(hr))
		throw CreateException("Texture --- Couldn't Create Texture From File", __FILE__, __LINE__).what();
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

