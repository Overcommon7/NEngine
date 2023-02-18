#include "GameState.h"

void GameState::Render()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	vertexShader.Bind();
	pixelShader.Bind();

	Matrix4 matWorld = Matrix4::RotationY(rotationY);
	Matrix4 matFinal = (matWorld * camera.GetViewMatrix() * camera.GetProjectionMatrix()).Transpose();

	constantBuffer.Update(&matFinal);
	constantBuffer.BindVS(0);

	meshBuffer.Render();
}

void GameState::Initialize()
{
	
	camera.SetPosition(Vector3( 0, 1, -10 ));
	camera.SetLookAt(Vector3::Zero);

	std::filesystem::path shaderFile = "../../Assets/Shaders/DoTransform.fx";

	CreateShape();

	vertexShader.Initalize(shaderFile, VE_Postition | VE_Color);
	pixelShader.Initalize(shaderFile);
	constantBuffer.Initialize(sizeof(Matrix4));
}

void GameState::Terminate()
{
	vertices.clear();
	vertexShader.Terminate();
	pixelShader.Terminate();
	meshBuffer.Terminate();
	constantBuffer.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto input = NEng::Input::InputSystem::Get();
	if (input->IsKeyPressed(NEng::Input::KeyCode::ONE))	App::ChangeState("SphereMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::TWO)) App::ChangeState("CubeMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::THREE)) App::ChangeState("CylinderMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FOUR)) App::ChangeState("PlaneMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FIVE)) App::ChangeState("RectangleMesh");

	rotationY += NEng::HALF_PI * deltaTime * 0.5f;
}