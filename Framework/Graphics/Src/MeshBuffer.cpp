#include "Precompiled.h"
#include "MeshBuffer.h"
#include "GraphicsSystem.h"

namespace NEng
{
	void MeshBuffer::Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertCount)
	{
		CreateVertexBuffer(vertices, vertexSize, vertCount);
	}
	void MeshBuffer::Terminate()
	{
		SafeRelease(vertexBuffer);
		SafeRelease(indexBuffer);
	}

	void MeshBuffer::Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertCount, const uint32_t* indicies, uint32_t indexCount)
	{
		CreateVertexBuffer(vertices, vertexSize, vertCount);
		CreateIndexBuffer(indicies, indexCount);
	}
	void MeshBuffer::SetTopology(const Topology& topology)
	{
		if (topology == Topology::Triangles)
			this->topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
	void MeshBuffer::Render()
	{
		auto context = GraphicsSystem::Get()->GetContext();

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		UINT offset = 0;

		context->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexSize, &offset);
		if (indexBuffer)
		{
			context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
			context->DrawIndexed(indexCount, 0, 0);
		}
		else context->Draw((UINT)vertexSize, 0);

		
	}
	void MeshBuffer::CreateVertexBuffer(const void* vertices, uint32_t vertexSize, uint32_t vertCount)
	{
		this->vertexCount = vertCount;
		this->vertexSize = vertexSize;

		auto device = GraphicsSystem::Get()->GetDevice();
		D3D11_BUFFER_DESC buffer{};

		buffer.ByteWidth = static_cast<UINT>(vertCount * vertexSize);
		buffer.Usage = D3D11_USAGE_DEFAULT;
		buffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		buffer.MiscFlags = 0;
		buffer.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA init{};
		init.pSysMem = vertices;

		HRESULT hr = device->CreateBuffer(&buffer, &init, &vertexBuffer);
	}
	void MeshBuffer::CreateIndexBuffer(const uint32_t* indicies, uint32_t indexCount)
	{
		this->indexCount = indexCount;

		auto device = GraphicsSystem::Get()->GetDevice();
		D3D11_BUFFER_DESC buffer{};

		buffer.ByteWidth = static_cast<UINT>(indexCount * sizeof(uint32_t));
		buffer.Usage = D3D11_USAGE_DEFAULT;
		buffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
		buffer.MiscFlags = 0;
		buffer.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA init{};
		init.pSysMem = indicies;

		HRESULT hr = device->CreateBuffer(&buffer, &init, &indexBuffer);
	}
}