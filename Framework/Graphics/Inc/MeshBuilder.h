#pragma once

#include "MeshTypes.h"

namespace NEng
{
	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC(float size);
		static MeshPX CreateCubePX(float size, bool reverseNormals = false);
		static Mesh CreateCube(float size);

		static MeshPC CreateRectPC(float width, float height, float depth);
		static MeshPX CreateRectPX(float width, float height, float depth);

		static MeshPC CreatePlanePC(int numRows, int numCols, float spacing);
		static MeshPC CreateCylinderPC(int slices, int rings);

		static MeshPC CreateSpherePC(int slices, int rings, float radius);
		static MeshPX CreateSpherePX(int slices, int rings, float radius);
		static MeshPX CreateSkySpherePX(int slices, int rings, float radius);

		MeshBuilder() = delete;
		MeshBuilder(const MeshBuilder& m) = delete;
		MeshBuilder& operator=(const MeshBuilder& m) = delete;
	};
}
