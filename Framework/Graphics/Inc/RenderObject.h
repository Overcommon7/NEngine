#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"
#include "Material.h"

namespace NEng
{
	class RenderObject
	{
	public:
		void Terminate()
		{
			meshBuffer.Terminate();
		}

		Transform transform;
		Material material;
		MeshBuffer meshBuffer;
		TextureID diffuseMapID;
		TextureID normalMapID;
	};
}
