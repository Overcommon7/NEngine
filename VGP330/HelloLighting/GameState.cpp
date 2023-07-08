#include "GameState.h"

using namespace NEng::Input;

void GameState::Render()
{
	standardEffect.Begin();
	standardEffect.Render(renderObject);
	standardEffect.End();
}

void GameState::RenderMesh(Camera& camera, const float& aspectRatio, const bool& usetransfrom)
{

}

void GameState::DebugUI()
{
	ImGui::Begin("DebugWindow", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::DragFloat("Sensitivity", &sensitivity, 0.02f, 0, 5.f);
	ImGui::DragFloat("WalkSpeed", &walkSpeed, 0.02f, 0, sprintSpeed);
	ImGui::DragFloat("SprintSpeed", &sprintSpeed, 0.02f, 0, 50.f);

	ImGui::End();

	SimpleDraw::Render(camera);
}

void GameState::Initialize()
{
	camera.SetPosition({0, 0, -3});
	camera.SetLookAt({});

	std::filesystem::path shaderFile = "../../Assets/Shaders/Standard.fx";
	standardEffect.Initialize(shaderFile);
	standardEffect.SetCamera(camera);

	Mesh earth = MeshBuilder::CreateSphere(30, 30, 1);
	renderObject.meshBuffer.Initialize(earth);
	renderObject.diffuseMapID = TextureManager::Get()->LoadTexture("earth.jpg");

	GraphicsSystem::Get()->SetClearColor(Colors::White);
}

void GameState::Terminate()
{
	renderObject.Terminate();
	standardEffect.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto input = NEng::Input::InputSystem::Get();

	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? sprintSpeed : walkSpeed) * deltaTime;
	const float turnSpeed = sensitivity * deltaTime;

	if (input->IsKeyDown(KeyCode::W))
	{
		camera.Walk(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		camera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		camera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		camera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		camera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		camera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		camera.Yaw(input->GetMouseMoveX() * turnSpeed);
		camera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}