#include "Precompiled.h"
#include "Sampler.h"

#include "GraphicsSystem.h"

namespace
{
	constexpr D3D11_FILTER GetFilter(const NEng::Sampler::Filter& filter)
	{
		switch (filter)
		{
		default:
		case NEng::Sampler::Filter::Point:       return D3D11_FILTER_MIN_MAG_MIP_POINT;	
		case NEng::Sampler::Filter::Linear:	     return D3D11_FILTER_MIN_MAG_MIP_LINEAR;	
		case NEng::Sampler::Filter::Anistropic:	 return D3D11_FILTER_ANISOTROPIC;	
		}
	}

	constexpr D3D11_TEXTURE_ADDRESS_MODE GetAddressMode(const NEng::Sampler::Addressmode addressmode)
	{
		switch (addressmode)
		{
		default:
		case NEng::Sampler::Addressmode::Border: return D3D11_TEXTURE_ADDRESS_BORDER;
		case NEng::Sampler::Addressmode::Clmap:	 return D3D11_TEXTURE_ADDRESS_CLAMP;
		case NEng::Sampler::Addressmode::Mirri:	 return D3D11_TEXTURE_ADDRESS_MIRROR;
		case NEng::Sampler::Addressmode::Wrap:	 return D3D11_TEXTURE_ADDRESS_WRAP;
		}
	}
}

namespace NEng
{
	Sampler::Sampler(Sampler&& t) noexcept :
		mSamplerState(t.mSamplerState)
	{
		t.mSamplerState = nullptr;
	}
	Sampler& Sampler::operator=(Sampler&& t) noexcept
	{
		mSamplerState = t.mSamplerState;
		t.mSamplerState = nullptr;
		return* this;
	}
	void Sampler::Initialize(Filter filter, Addressmode addressMode)
	{
		mSamplerState = nullptr;
		auto dFilter = GetFilter(filter);
		auto dMode = GetAddressMode(addressMode);

		D3D11_SAMPLER_DESC desc{};
		desc.Filter = dFilter;
		desc.AddressU = dMode;
		desc.AddressV = dMode;
		desc.AddressW = dMode;

		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;

		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.MaxLOD = 0;
		desc.MaxLOD = D3D11_FLOAT32_MAX;

		auto hr = GraphicsSystem::Get()->GetDevice()->CreateSamplerState(&desc, &mSamplerState);
		if (!SUCCEEDED(hr)) throw std::exception("Sampler - Failed to Create Sampler State");
	}

	void Sampler::Terminate()
	{
		SafeRelease(mSamplerState);
	}

	void Sampler::BindVS(uint32_t slot) const
	{
		GraphicsSystem::Get()->GetContext()->VSSetSamplers(slot, 1, &mSamplerState);
	}

	void Sampler::BindPS(uint32_t slot) const
	{
		GraphicsSystem::Get()->GetContext()->PSSetSamplers(slot, 1, &mSamplerState);
	}
}


