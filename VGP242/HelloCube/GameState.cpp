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
	CreateShape();
	camera.SetPosition(Vector3( 0, 1, -3 ));
	camera.SetLookAt(Vector3::Zero);

	std::filesystem::path shaderFile = "../../Assets/Shaders/DoTransform.fx";

	vertexShader.Initalize(shaderFile, VE_Postition | VE_Color);
	pixelShader.Initalize(shaderFile);
	//MeshPC cube = MeshBuilder::CreateCubePC(1.f, Colors::Aqua);
	meshBuffer.Initialize(vertices);
	//meshBuffer.Initialize(cube);
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
	if (input->IsKeyPressed(NEng::Input::KeyCode::ONE))	App::ChangeState("TrifroceState");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::TWO)) App::ChangeState("SquareState");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::THREE)) App::ChangeState("HeartState");

	rotationY += NEng::HALF_PI * deltaTime * 0.5f;
}