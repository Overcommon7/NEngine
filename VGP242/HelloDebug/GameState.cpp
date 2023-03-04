#include "GameState.h"

void GameState::Render()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	vertexShader.Bind();
	pixelShader.Bind();

	mSampler.BindPS(0);
	mDiffuseTexture.BindPS(0);

	mSampler.BindVS(0);
	mDiffuseTexture.BindVS(0);

	Matrix4 matWorld = Matrix4::RotationY(rotationY) * Matrix4::RotationX(rotationX);
	Matrix4 matFinal = (matWorld * camera.GetViewMatrix() * camera.GetProjectionMatrix()).Transpose();

	constantBuffer.Update(&matFinal);
	constantBuffer.BindVS(0);

	meshBuffer.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("DebugWindow", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Checkbox("Sphere", &Sphere.render);
	if (Sphere.render)
	{
		ImGui::DragFloat4("Color", &Sphere.color.r, 0.1f);
		ImGui::DragFloat3("Position", &Sphere.position.x, 0.1f);
		ImGui::DragFloat("Radius", &Sphere.size.x, 0.1f);
		SimpleDraw::AddSphere(10, 30, Sphere.size.x, Sphere.position, Sphere.color);
	}

	ImGui::Checkbox("AABB", &AABB.render);
	if (AABB.render)
	{
		ImGui::DragFloat4("Color", &AABB.color.r, 0.1f);
		ImGui::DragFloat3("Max", &AABB.position.x, 0.1f);
		ImGui::DragFloat3("Min", &AABB.size.x, 0.1f);
		SimpleDraw::AddAABB(AABB.size, AABB.position, AABB.color);
	}

	ImGui::Checkbox("Filled AABB", &FilledAABB.render);
	if (FilledAABB.render)
	{
		ImGui::DragFloat4("Color", &FilledAABB.color.r, 0.1f);
		ImGui::DragFloat3("Max", &FilledAABB.position.x, 0.1f);
		ImGui::DragFloat3("Min", &FilledAABB.size.x, 0.1f);
		SimpleDraw::AddFilledAABB(FilledAABB.size, FilledAABB.position, FilledAABB.color);
	}

	ImGui::End();


	
	SimpleDraw::Render(camera);
}

void GameState::Initialize()
{
	
	camera.SetPosition(Vector3( 0, 1, -3 ));
	camera.SetLookAt(Vector3::Zero);

	CreateShape();
	
	if (!std::filesystem::exists(texturePath))
		throw std::exception("Texture doenst exist");

	mSampler.Initialize(NEng::Sampler::Filter::Linear, NEng::Sampler::Addressmode::Wrap);
	mDiffuseTexture.Initialize(texturePath);

	vertexShader.Initalize<VertexPX>(shaderFile);
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
	mSampler.Terminate();
	mDiffuseTexture.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto input = NEng::Input::InputSystem::Get();
	if (input->IsKeyPressed(NEng::Input::KeyCode::ONE))	App::ChangeState("SphereState");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::TWO)) App::ChangeState("SkyBox");
		
	/*else if (input->IsKeyPressed(NEng::Input::KeyCode::THREE)) App::ChangeState("CylinderMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FOUR)) App::ChangeState("PlaneMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FIVE)) App::ChangeState("RectangleMesh");*/

	if (input->IsKeyDown(NEng::Input::KeyCode::UP))	 rotationX += NEng::HALF_PI * deltaTime * 0.5f;
	else if (input->IsKeyDown(NEng::Input::KeyCode::DOWN))  rotationX -= NEng::HALF_PI * deltaTime * 0.5f;
	if (input->IsKeyDown(NEng::Input::KeyCode::LEFT))  rotationY += NEng::HALF_PI * deltaTime * 0.5f;
	else if (input->IsKeyDown(NEng::Input::KeyCode::RIGHT))	rotationY -= NEng::HALF_PI * deltaTime * 0.5f;
	
}