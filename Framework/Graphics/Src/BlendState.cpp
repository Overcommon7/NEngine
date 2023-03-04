#include "Precompiled.h"
#include "BlendState.h"

#include "GraphicsSystem.h"

namespace
{
	D3D11_BLEND GetSrcBlend(NEng::BlendState::Mode mode)
	{
		switch (mode)
		{
		case NEng::BlendState::Mode::Additive:			 return D3D11_BLEND_SRC_ALPHA;
		case NEng::BlendState::Mode::AlphaBlend:		 return D3D11_BLEND_SRC_ALPHA;
		case NEng::BlendState::Mode::AlphaPremulitplied: return D3D11_BLEND_ONE;
		default:
		case NEng::BlendState::Mode::Opaque:			 return D3D11_BLEND_ONE;
		}
	}

	D3D11_BLEND GetDestBlend(NEng::BlendState::Mode mode)
	{
		switch (mode)
		{
		case NEng::BlendState::Mode::Additive:			 return D3D11_BLEND_ONE;
		case NEng::BlendState::Mode::AlphaBlend:		 return D3D11_BLEND_INV_SRC_ALPHA;
		case NEng::BlendState::Mode::AlphaPremulitplied: return D3D11_BLEND_INV_SRC_ALPHA;
		default:
		case NEng::BlendState::Mode::Opaque:			 return D3D11_BLEND_ZERO;
		}
	}
}

void NEng::BlendState::ClearState()
{
	GraphicsSystem::Get()->GetContext()->OMSetBlendState(nullptr, nullptr, UINT_MAX);
}

NEng::BlendState::~BlendState()
{
	if (mBlendState != nullptr)
		throw CreateException("Blend State -- Blend state not released", __FILE__, __LINE__).what();
}

void NEng::BlendState::Initialize(Mode mode)
{
	auto srcBlend = GetSrcBlend(mode);
	auto destBlend = GetDestBlend(mode);

	D3D11_BLEND_DESC desc{};
	desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE) || (destBlend != D3D11_BLEND_ZERO);
	desc.RenderTarget[0].SrcBlend = desc.RenderTarget[0].SrcBlendAlpha = srcBlend;
	desc.RenderTarget[0].DestBlend = desc.RenderTarget[0].DestBlendAlpha = destBlend;
	desc.RenderTarget[0].BlendOp = desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	GraphicsSystem::Get()->GetDevice()->CreateBlendState(&desc, &mBlendState);
	
}

void NEng::BlendState::Terminate()
{
	SafeRelease(mBlendState);
}

void NEng::BlendState::Set()
{
	auto context = GraphicsSystem::Get()->GetContext();
	context->OMSetBlendState(mBlendState, nullptr, UINT_MAX);
}
