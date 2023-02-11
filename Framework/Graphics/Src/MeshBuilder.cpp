#include "Precompiled.h"
#include "MeshBuilder.h"

namespace
{
	Color GetNextColor()
	{
		constexpr Color colorTable[] = {
		   Colors::Aquamarine,
		   Colors::DarkSlateGray,
		   Colors::DarkCyan,
		   Colors::DarkViolet,
		   Colors::PapayaWhip,
		   Colors::Salmon,
		   Colors::MediumPurple,
		   Colors::Bisque,
		   Colors::WhiteSmoke,
		   Colors::WhiteSmoke,
		   Colors::Fuchsia,
		   Colors::YellowGreen,
		   Colors::Aqua

		};

		return colorTable[rand() % (sizeof(Color) / sizeof(colorTable))];
		
	}
	void CreateCubeIndicies(vector<uint32_t>& indicies)
	{
		indicies = {
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
	}

	void CreatePlaneIndicies(vector<uint32_t> indices, int numRows, int numColunms)
	{
		for (int r = 0; r <= numRows; r++)
		{
			for (int c = 0; c < numColunms; c++)
			{
				int i = r * (numColunms + 1) + c;

				//triangle 1
				indices.push_back(i);
				indices.push_back(i + numColunms + 1);
				indices.push_back(i + 1);

				//trinagle 2
				indices.push_back(i);
				indices.push_back(i + numColunms);
				indices.push_back(i + numColunms + 1);
			}
		}
	}

	void CreateCapIndicies(vector<uint32_t> indices, int slices, int topIndex, int bottomIndex)
	{
		for (int s = 0; s < slices; s++)
		{
			//Bottom Triangle 
			indices.push_back(s);
			indices.push_back(s + 1);
			indices.push_back(bottomIndex);

			int topRowIndex = topIndex - slices - 1 + s;
			indices.push_back(topIndex);
			indices.push_back(topRowIndex + 1);
			indices.push_back(topRowIndex);
		}
	}
}

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

		CreateCubeIndicies(mesh.indicies);

		return mesh;
	}
	MeshPX MeshBuilder::CreateCubePX(float size, const Color& color)
	{
		MeshPX mesh;

		const float hs = size * 0.5f;
		//front
		mesh.verticies.push_back({ {-hs, -hs, -hs}, {0.25f, 0.66f} });
		mesh.verticies.push_back({ {-hs, hs, -hs}, {0.25f, 0.33f} });
		mesh.verticies.push_back({ {hs, hs, -hs}, {0.5f, 0.33f} });
		mesh.verticies.push_back({ {hs, -hs, -hs}, {0.5f, 0.66f} });

		//back
		mesh.verticies.push_back({ {-hs, -hs, hs}, {0.25f, 1.f} });
		mesh.verticies.push_back({ {-hs, hs, hs}, {0.f, 0.33f} });
		mesh.verticies.push_back({ {hs, hs, hs}, {0.5f, 0.f} });
		mesh.verticies.push_back({ {hs, -hs, hs}, {0.5f, 1.f} });

		CreateCubeIndicies(mesh.indicies);

		return mesh;
	}
	Mesh MeshBuilder::CreateCube(float size)
	{
		return Mesh();
	}
	MeshPC MeshBuilder::CreateRectPC(float width, float height, float depth)
	{
		MeshPC mesh;

		const float hw = width * 0.5f;
		const float hh = height * 0.5f;
		const float hd = depth * 0.5f;

		mesh.verticies.push_back({ {-hw, -hh, -hd}, GetNextColor()});
		mesh.verticies.push_back({ {-hw, hh, -hd}, GetNextColor() });
		mesh.verticies.push_back({ {hw, hh, -hd}, GetNextColor() });
		mesh.verticies.push_back({ {hw, -hh, -hd},GetNextColor() });

		//back
		mesh.verticies.push_back({ {-hw, -hh, hd}, GetNextColor() });
		mesh.verticies.push_back({ {-hw, hh, hd}, GetNextColor() });
		mesh.verticies.push_back({ {hw, hh, hd}, GetNextColor() });
		mesh.verticies.push_back({ {hw, -hh, hd}, GetNextColor() });

		CreateCubeIndicies(mesh.indicies);

		return mesh;
	}
	MeshPX MeshBuilder::CreateRectPX(float width, float height, float depth)
	{
		return MeshPX();
	}
	MeshPC MeshBuilder::CreatePlanePC(int numRows, int numCols, float spacing)
	{
		MeshPC mesh;

		const float hpw = (float)numCols * spacing * 0.5f;
		const float hph = (float)numRows * spacing * 0.5f;

		float x = -hpw;
		float y = -hph;

		mesh.verticies.reserve(numCols * numRows);

		for (int r = 0; r <= numRows; r++)
		{
			for (int c = 0; c <= numCols; c++)
			{
				mesh.verticies.push_back({ {x, y, 0}, GetNextColor() });
				x += spacing;
			}
			x = -hpw;
			y += spacing;
		}

		CreatePlaneIndicies(mesh.indicies, numRows, numCols);

		return mesh;
	}
	MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
	{
		MeshPC mesh;

		const float hh = (float)rings * 0.5f;
		const float sls = (float)slices;
		for (int r = 0; r <= rings; r++)
		{
			float ring = (float)r;
			for (int s = 0; s < slices + 1; s++)
			{
				float slice = (float)s;
				float rotation = (slice / slices) * TWO_PI;

				mesh.verticies.push_back({ { sin(rotation), ring - hh, -cos(rotation) }, GetNextColor() });
			}	
		}

		mesh.verticies.push_back({ {0.0f, hh, 0.0f}, GetNextColor() });
		mesh.verticies.push_back({ {0.0f, -hh, 0.0f}, GetNextColor() });

		CreatePlaneIndicies(mesh.indicies, rings, slices);
		CreateCapIndicies(mesh.indicies, slices, mesh.indicies.size() - 2, mesh.indicies.size() - 1);
		return mesh;
	}
	MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
	{
		MeshPC mesh;

		float vertRotation = PI / float(rings - 1);
		float horzRotation = TWO_PI / float(slices);

		for (int r = 0; r <= rings; r++)
		{
			float ring = (float)r;
			float phi = ring * vertRotation;

			for (int s = 0; s <= slices; s++)
			{
				float slice = (float)s;
				float rotation = slices * horzRotation;

				mesh.verticies.push_back({ {radius * sin(rotation) * sin(phi), radius * cos(phi), radius * cos(rotation) * sin(phi) }, GetNextColor() });

			}

		}

		CreatePlaneIndicies(mesh.indicies, rings, slices);

		return mesh;
	}
	MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
	{
		return MeshPX();
	}
}