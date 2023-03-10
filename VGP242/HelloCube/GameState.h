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
	float rotationY;
};

class TriForce : public GameState
{
public:
    inline void CreateShape() override
	{
		
	}
};

class DoubleSqaureState : public GameState
{
public:
	inline void CreateShape() override
	{
		vertices.push_back(Vertex({ Vector3(-0.5f, 0.5f, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(0, 0.5f, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(-0.5f, 0, 0.5f), Colors::Red }));
		
		vertices.push_back(Vertex({ Vector3(0, 0, 0.5f), Colors::Blue }));
		vertices.push_back(Vertex({ Vector3(-0.5f, 0, 0.5f), Colors::Blue }));
		vertices.push_back(Vertex({ Vector3(0, 0.5f, 0.5f), Colors::Blue }));
		
		vertices.push_back(Vertex({ Vector3(0, 0, 0.5f), Colors::Green }));
		vertices.push_back(Vertex({ Vector3(0, 0.5f, 0.5f), Colors::Green }));
		vertices.push_back(Vertex({ Vector3(0.5f, 0, 0.5f), Colors::Green }));

		vertices.push_back(Vertex({ Vector3(0.5f, 0.5f, 0.5f), Colors::Yellow }));
		vertices.push_back(Vertex({ Vector3(0.5f, 0, 0.5f), Colors::Yellow }));
		vertices.push_back(Vertex({ Vector3(0, 0.5f, 0.5f), Colors::Yellow }));		
	}
};

class HeartState : public GameState
{
public:
	inline void CreateShape() override
	{
		vertices.push_back(Vertex({ Vector3(-0.2f, 0.4f, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(-0.1f, 0.5f, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(0, 0.4f, 0.5f), Colors::Red }));

		vertices.push_back(Vertex({ Vector3(0, 0.4f, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(0.1f, 0.5f, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(0.2f, 0.4f, 0.5f), Colors::Red }));

		vertices.push_back(Vertex({ Vector3(0.2f, 0.4f, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(0, 0, 0.5f), Colors::Red }));
		vertices.push_back(Vertex({ Vector3(-0.2f, 0.4f, 0.5f), Colors::Red}));
	}
};
