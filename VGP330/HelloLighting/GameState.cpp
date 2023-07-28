#include "GameState.h"

using namespace NEng::Input;

void GameState::Render()
{
	renderTarget.BeginRender();
	standardEffect.Begin();
	standardEffect.Render(renderObject);
	standardEffect.End();
	renderTarget.EndRender();

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
	if (ImGui::CollapsingHeader("Lighting##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &directionalLight.direction.x, 0.01f, -10.f, 1.0f))
		{
			directionalLight.direction = directionalLight.direction.Normalize();
		}

		ImGui::ColorEdit4("Ambient##Light", &directionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &directionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &directionalLight.specular.r);
	}

	if (ImGui::CollapsingHeader("Material##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ambient##Material", &renderObject.material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Material", &renderObject.material.diffuse.r);
		ImGui::ColorEdit4("Specular##Material",&renderObject.material.specular.r);
		ImGui::ColorEdit4("Emissive##Material",&renderObject.material.emmisive.r);
		ImGui::DragFloat("Power##Material",&renderObject.material.specularPower);
	}

	ImGui::Text("Render Target");
	ImGui::Image(renderTarget.GetRawData(), { 128, 128 }, { 0, 0 }, { 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 });
	standardEffect.DebugUI();										   


	ImGui::End();

	SimpleDraw::Render(camera);
}

void GameState::Initialize()
{
	camera.SetPosition({0, 0, -3});
	camera.SetLookAt({});

	directionalLight.direction = Vector3(1.f, -1.f, 1.f).Normalize();
	directionalLight.ambient = { 0.4f, 0.4f, 0.4f, 1.f };
	directionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.f };
	directionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.f };

	std::filesystem::path shaderFile = "../../Assets/Shaders/Standard.fx";
	standardEffect.Initialize(shaderFile);
	standardEffect.SetCamera(camera);
	standardEffect.SetDirectionalLight(directionalLight);

	Mesh earth = MeshBuilder::CreateSphere(30, 30, 1);
	renderObject.meshBuffer.Initialize(earth);
	renderObject.diffuseMapID = TextureManager::Get()->LoadTexture("earth.jpg" );
	renderObject.normalMapID = TextureManager::Get()->LoadTexture("earth_normal.jpg" );

	auto gs = GraphicsSystem::Get();
	gs->SetClearColor(Colors::Black);
	uint32_t size = 512;

	renderTarget.Initialize(size, size, Texture::Format::RGBA_U8);

}

void GameState::Terminate()
{
	renderTarget.Terminate();
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