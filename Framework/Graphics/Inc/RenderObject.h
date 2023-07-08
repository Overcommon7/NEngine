#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"

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
		MeshBuffer meshBuffer;
		TextureID diffuseMapID;
	};
}
