#pragma once

#include "VertexTypes.h"

namespace NEng
{
	template<class VertexT>
	struct MeshBase
	{
		using VertexType = VertexT;
		vector<VertexType> verticies;
		vector<uint32_t> indicies;
	};

	using MeshP = MeshBase<VertexP>;
	using MeshPC = MeshBase<VertexPC>;
	using MeshPX = MeshBase<VertexPX>;
	using Mesh = MeshBase<Vertex>;
}
