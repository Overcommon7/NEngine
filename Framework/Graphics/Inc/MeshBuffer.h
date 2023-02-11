#pragma once

namespace NEng
{
	class MeshBuffer final
	{
	public:
		enum class Topology
		{
			Points,
			Lines,
			Triangles
		};


		void Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertCount);
		void Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertCount, const uint32_t* indicies, uint32_t indexCount);


		template<class VertexType>
		void Initialize(const std::vector<VertexType>& verticies)
		{
			Initialize(verticies.data(), (uint32_t)sizeof(VertexType), (uint32_t)verticies.size());
		}

		template<class MeshType>
		void Initialize(const MeshType& mesh)
		{
			Initialize(mesh.verticies.data(), (uint32_t)sizeof(MeshType::VertexType), (uint32_t)mesh.verticies.size(), mesh.indicies.data(), (uint32_t)mesh.indicies.size());
		}

		
		void Terminate();

		void SetTopology(const Topology& topology);
		void Render();

	private:

		void CreateVertexBuffer(const void* vertices, uint32_t vertexSize, uint32_t vertCount);
		void CreateIndexBuffer(const uint32_t* indicies, uint32_t indexCount);

		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;

		D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		uint32_t vertexSize;
		uint32_t vertexCount;
		uint32_t indexCount;


	};
}
