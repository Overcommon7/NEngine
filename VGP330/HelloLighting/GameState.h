#pragma once

#include <../NEngine/Inc/NEngine.h>

using namespace NEng;

class GameState : public AppState
{
public :
	void DebugUI();
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:

	void RenderMesh(Camera& camera, const float& aspectRatio = 0.0f, const bool& usetransfrom = true);

	Camera camera;
	StandardEffect standardEffect;
	RenderObject renderObject;

	float sensitivity = 0.35;
	float walkSpeed = 10;
	float sprintSpeed = 20;

};


