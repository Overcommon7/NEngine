#pragma once

#include <../NEngine/Inc/NEngine.h>

using namespace NEng;

class GameState : public AppState
{
public :
	virtual void CreateShape() = 0;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	struct Vertex
	{
		Vector3 position;
		Color color;
	};

	vector<Vertex> vertices;
	VertexShader vertexShader;
	PixelShader pixelShader;
	MeshBuffer meshBuffer;
	Camera camera;
	ConstantBuffer constantBuffer;

	Texture mDiffuseTexture;
	Sampler mSampler;

	std::filesystem::path shaderFile = "../../Assets/Shaders/DoTexturing.fx";
	std::filesystem::path texturePath = "../../Assets/Textures/earth.jpg";

	float rotationY;
	float rotationX;
};

class SkyBox : public GameState
{
public:
	void CreateShape() override
	{
		auto cube = MeshBuilder::CreateCubePX(1000, true);
		meshBuffer.Initialize(cube);

		texturePath = "../../Assets/Images/skybox/skybox_texture.jpg";
	}	
};

class SphereMesh : public GameState
{
	void CreateShape() override
	{
		auto sphere = MeshBuilder::CreateSpherePX(30, 30, 1);
		meshBuffer.Initialize(sphere);
	}
};

class CylinderMesh : public GameState
{
	void CreateShape() override
	{
		auto sphere = MeshBuilder::CreateCylinderPC(10, 4);
		meshBuffer.Initialize(sphere);
	}
};

class PlaneMesh : public GameState
{
	void CreateShape() override
	{
		auto sphere = MeshBuilder::CreatePlanePC(5, 5, 2);
		meshBuffer.Initialize(sphere);
	}
};

class RectangleMesh : public GameState
{
	void CreateShape() override
	{
		auto sphere = MeshBuilder::CreateRectPC(1, 3, 2);
		meshBuffer.Initialize(sphere);
	}
};


