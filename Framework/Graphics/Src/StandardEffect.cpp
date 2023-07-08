#include "Precompiled.h"
#include "StandardEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "TextureManager.h"

void NEng::StandardEffect::Initialize(const std::filesystem::path& filepath)
{
	transformBuffer.Initialize(sizeof(Matrix4));
	vertexShader.Initalize<Vertex>(filepath);
	pixelShader.Initalize(filepath);
	sampler.Initialize(Sampler::Filter::Linear, Sampler::Addressmode::Wrap);
}

void NEng::StandardEffect::Terminate()
{
	sampler.Terminate();
	pixelShader.Terminate();
	vertexShader.Terminate();
	transformBuffer.Terminate();
}

void NEng::StandardEffect::Begin()
{
	if (camera == nullptr)
		throw CreateException("StandardEffect: Camera not Set", __FILE__, __LINE__);

	vertexShader.Bind();
	pixelShader.Bind();

	transformBuffer.BindVS(0);
	sampler.BindPS(0);
	sampler.BindVS(0);
	
}

void NEng::StandardEffect::End()
{

}

void NEng::StandardEffect::Render(const RenderObject& renderObject)
{
	const auto& matWorld = renderObject.transform.GetMatrix4();
	const auto& matView = camera->GetViewMatrix();
	const auto& matProj = camera->GetProjectionMatrix();

	auto matWorldTranspose = (matWorld * matView * matProj).Transpose();
	transformBuffer.Update(&matWorldTranspose);

	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapID, 0);

	renderObject.meshBuffer.Render();
}

void NEng::StandardEffect::SetCamera(const Camera& camera)
{
	this->camera = &camera;
}

void NEng::StandardEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("StandardEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}
}
