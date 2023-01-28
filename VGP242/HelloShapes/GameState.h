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

	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;

	ID3D11PixelShader* pixelShader = nullptr;

};

class Hexagon : public GameState
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

	}
};

class HeartState : public GameState
{
public:
	inline void CreateShape() override
	{

	}
};
