#include "Precompiled.h"
#include "ConstantBuffer.h"
#include <GraphicsSystem.h>

namespace NEng
{
	ConstantBuffer::~ConstantBuffer()
	{
		
	}
	void ConstantBuffer::Initialize(uint32_t bufferSize)
	{
		D3D11_BUFFER_DESC desc{};

		desc.ByteWidth = bufferSize;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;

		GraphicsSystem::Get()->GetDevice()->CreateBuffer(&desc, nullptr, &mConstantBuffer);
	}
	void ConstantBuffer::Terminate()
	{
		SafeRelease(mConstantBuffer);
	}
	void ConstantBuffer::Update(const void* data)
	{
		GraphicsSystem::Get()->GetContext()->UpdateSubresource(mConstantBuffer, 0, nullptr, data, 0, 0);
	}
	void ConstantBuffer::BindVS(uint32_t slot)
	{
		GraphicsSystem::Get()->GetContext()->VSSetConstantBuffers(slot, 1, &mConstantBuffer);
	}
	void ConstantBuffer::BindPS(uint32_t slot)
	{
		GraphicsSystem::Get()->GetContext()->PSSetConstantBuffers(slot, 1, &mConstantBuffer);
	}
}