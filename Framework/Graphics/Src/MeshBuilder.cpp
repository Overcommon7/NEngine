#include "Precompiled.h"
#include "MeshBuilder.h"

namespace NEng
{
	MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
	{
		MeshPC mesh;

		const float hs = size * 0.5f;
		//front
		mesh.verticies.push_back({ {-hs, -hs, -hs}, color });
		mesh.verticies.push_back({ {-hs, hs, -hs}, color });
		mesh.verticies.push_back({ {hs, hs, -hs}, color });
		mesh.verticies.push_back({ {hs, -hs, -hs}, color });

		//back
		mesh.verticies.push_back({ {-hs, -hs, hs}, color });
		mesh.verticies.push_back({ {-hs, hs, hs}, color });
		mesh.verticies.push_back({ {hs, hs, hs}, color });
		mesh.verticies.push_back({ {hs, -hs, hs}, color });

		mesh.indicies = {
			//front
			0, 1, 2,
			0, 2, 3,

			//back
			7, 6, 5,
			7, 5, 4,

			//right
			3, 2, 6,
			3, 6, 7,

			//left
			0, 5, 1,
			0, 4, 5,

			//top
			1, 5, 6,
			1, 6, 2,

			//bottom
			0, 3, 7,
			0, 7, 4
		};

		return mesh;
	}
	MeshPX MeshBuilder::CreateCubePX(float size, const Color& color)
	{
		return MeshPX();
	}
	Mesh MeshBuilder::CreateCube(float size)
	{
		return Mesh();
	}
	MeshPC MeshBuilder::CreateRectPC(float width, float height, float depth)
	{
		return MeshPC();
	}
	MeshPX MeshBuilder::CreateRectPX(float width, float height, float depth)
	{
		return MeshPX();
	}
	MeshPC MeshBuilder::CreatePlanePC(int numRows, int numCols, float spacing)
	{
		return MeshPC();
	}
	MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
	{
		return MeshPC();
	}
	MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
	{
		return MeshPC();
	}
	MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
	{
		return MeshPX();
	}
}