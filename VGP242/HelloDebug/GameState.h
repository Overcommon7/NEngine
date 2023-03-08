#pragma once

#include <../NEngine/Inc/NEngine.h>
#include "RenderObject.h"

using namespace NEng;

class GameState : public AppState
{
public :
	//virtual void CreateShape() = 0;
	void DebugUI();
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:

	void RenderMesh(Camera& camera, const float& aspectRatio = 0.0f, const bool& usetransfrom = true);

	struct Vertex
	{
		Vector3 position;
		Color color;
	};

	struct SimpleDebug
	{
		bool render = false;
		Color color = Colors::HotPink;
		Vector3 size = { 1, 1, 1 };
		Vector3 position = { 0, 0, 0.5 };
	};

	vector<Vertex> vertices;
	VertexShader vertexShader;
	PixelShader pixelShader;
	/*MeshBuffer meshBuffer;
	MeshBuffer skyBuffer;*/
	Camera camera;
	Camera mRenderTargetCamera;
	ConstantBuffer constantBuffer;

	float sensitivity = 0.75f;
	float walkSpeed = 20.f;
	float sprintSpeed = 40.f;

	//Texture mDiffuseTexture;
	Sampler mSampler;
	RenderTarget mRenderTarget;

	SkySphere skySphere;
	unordered_map<string, Planet> planets;

	std::filesystem::path shaderFile = "../../Assets/Shaders/DoTexturing.fx";
	std::filesystem::path texturePath = "../../Assets/Textures/earth.jpg";

	float rotationY = 0;
	float rotationX = 0;

	SimpleDebug AABB;
	SimpleDebug FilledAABB;
	SimpleDebug Sphere;
};

//class SkyBox : public GameState
//{
//public:
//	void CreateShape() override
//	{
//		auto cube = MeshBuilder::CreateCubePX(1000, true);
//		meshBuffer.Initialize(cube);
//
//		texturePath = "../../Assets/Images/skybox/skybox_texture.jpg";
//	}	
//};
//
//class SphereMesh : public GameState
//{
//	void CreateShape() override
//	{
//		auto sphere = MeshBuilder::CreateSpherePX(30, 30, 1);
//		meshBuffer.Initialize(sphere);
//
//
//	}
//};


