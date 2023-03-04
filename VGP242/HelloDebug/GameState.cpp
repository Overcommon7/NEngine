#include "GameState.h"

using namespace NEng::Input;

void GameState::Render()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);

	vertexShader.Bind();
	pixelShader.Bind();

	mSampler.BindPS(0);
	//mDiffuseTexture.BindPS(0);

	mSampler.BindVS(0);
	//mDiffuseTexture.BindVS(0);

	
	mRenderTarget.BeginRender();
		RenderMesh(mRenderTargetCamera, 1, true);
	mRenderTarget.EndRender();

	RenderMesh(camera);
}

void GameState::RenderMesh(Camera& camera, const float& aspectRatio, const bool& usetransfrom)
{
	/*camera.SetAspectRatio(aspectRatio);

	Matrix4 matFinal = (camera.GetViewMatrix() * camera.GetProjectionMatrix()).Transpose();

	constantBuffer.Update(&matFinal);
	constantBuffer.BindVS(0);

	meshBuffer.Render();*/

	skySphere.Render(camera, constantBuffer, aspectRatio, usetransfrom);
	earth.Render(camera, constantBuffer, aspectRatio, usetransfrom);
}

void GameState::DebugUI()
{
	ImGui::Begin("DebugWindow", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::DragFloat("Sensitivity", &sensitivity, 0.02f, 0, 5.f);
	ImGui::DragFloat("WalkSpeed", &walkSpeed, 0.02f, 0, sprintSpeed);
	ImGui::DragFloat("SprintSpeed", &sprintSpeed, 0.02f, 0, 10.f);

	ImGui::Checkbox("Sphere", &Sphere.render);
	if (Sphere.render)
	{
		ImGui::ColorEdit4("Color0", &Sphere.color.r, 0.1f);
		ImGui::DragFloat3("Position", &Sphere.position.x, 0.1f);
		ImGui::DragFloat("Radius", &Sphere.size.x, 0.1f);
		SimpleDraw::AddSphere(10, 30, Sphere.size.x, Sphere.position, Sphere.color);
	}

	ImGui::Checkbox("AABB", &AABB.render);
	if (AABB.render)
	{
		ImGui::ColorEdit4("Color1", &AABB.color.r, 0.1f);
		ImGui::DragFloat3("Max1", &AABB.position.x, 0.1f);
		ImGui::DragFloat3("Min1", &AABB.size.x, 0.1f);
		SimpleDraw::AddAABB(AABB.size, AABB.position, AABB.color);
	}

	ImGui::Checkbox("Filled AABB", &FilledAABB.render);
	if (FilledAABB.render)
	{
		ImGui::ColorEdit4("Color2", &FilledAABB.color.r, 0.1f);
		ImGui::DragFloat3("Max2", &FilledAABB.position.x, 0.1f);
		ImGui::DragFloat3("Min2", &FilledAABB.size.x, 0.1f);
		SimpleDraw::AddFilledAABB(FilledAABB.size, FilledAABB.position, FilledAABB.color);
	}

	ImGui::Text("Render Tagret");
	ImGui::Image(mRenderTarget.GetRawData(), { 128, 128 }, { 0, 0 }, { 1, 1 }, {1, 1, 1, 1}, {1, 1, 1, 1});

	ImGui::End();


	SimpleDraw::AddCircle(30, 3, {}, Colors::Black);
	SimpleDraw::Render(camera);
}

void GameState::Initialize()
{
	
	camera.SetPosition(Vector3( 0, 1, -3 ));
	camera.SetLookAt(Vector3::Zero);

	mRenderTargetCamera.SetPosition(Vector3(0, 1, -3));
	mRenderTargetCamera.SetLookAt(Vector3::Zero);

	//CreateShape();
	
	if (!std::filesystem::exists(texturePath))
		throw CreateException("Texture doenst exist", __FILE__, __LINE__).what();

	mSampler.Initialize(NEng::Sampler::Filter::Linear, NEng::Sampler::Addressmode::Wrap);
	//mDiffuseTexture.Initialize(texturePath);
	

	vertexShader.Initalize<VertexPX>(shaderFile);
	pixelShader.Initalize(shaderFile);
	constantBuffer.Initialize(sizeof(Matrix4));

	mRenderTarget.Initialize(512, 512, NEng::Texture::Format::RGBA_U32);

	skySphere.Initialize();
	earth.Initialize();
}

void GameState::Terminate()
{
	vertices.clear();
	vertexShader.Terminate();
	pixelShader.Terminate();
	//meshBuffer.Terminate();
	constantBuffer.Terminate();
	mSampler.Terminate();
	//mDiffuseTexture.Terminate();
	mRenderTarget.Terminate();
	skySphere.Terminate();
	earth.Terminate();
}

void GameState::Update(float deltaTime)
{
	auto input = NEng::Input::InputSystem::Get();
	/*if (input->IsKeyPressed(NEng::Input::KeyCode::ONE))	App::ChangeState("SphereState");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::TWO)) App::ChangeState("SkyBox");*/
		
	/*else if (input->IsKeyPressed(NEng::Input::KeyCode::THREE)) App::ChangeState("CylinderMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FOUR)) App::ChangeState("PlaneMesh");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::FIVE)) App::ChangeState("RectangleMesh");*/

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