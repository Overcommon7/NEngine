#include "Precompiled.h"
#include "StandardEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "TextureManager.h"


void NEng::StandardEffect::Initialize(const std::filesystem::path& filepath)
{
	transformBuffer.Initialize();
	lightingBuffer.Initialize();
	materialBuffer.Initialize();
	settingsBuffer.Initialize();

	vertexShader.Initalize<Vertex>(filepath);
	pixelShader.Initalize(filepath);
	sampler.Initialize(Sampler::Filter::Linear, Sampler::Addressmode::Wrap);
}

void NEng::StandardEffect::Terminate()
{
	sampler.Terminate();
	pixelShader.Terminate();
	vertexShader.Terminate();
	settingsBuffer.Terminate();
	materialBuffer.Terminate();
	lightingBuffer.Terminate();
	transformBuffer.Terminate();
}

void NEng::StandardEffect::Begin()
{
	if (camera == nullptr)
		throw CreateException("StandardEffect: Camera not Set", __FILE__, __LINE__);

	vertexShader.Bind();
	pixelShader.Bind();

	transformBuffer.BindVS(0);

	lightingBuffer.BindVS(1);
	lightingBuffer.BindPS(1);

	materialBuffer.BindPS(2);

	settingsBuffer.BindPS(3);
	settingsBuffer.BindVS(3);

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

	TransformData transformData;
	transformData.world = matWorld.Transpose();
	transformData.wvp = (matWorld * matView * matProj).Transpose();
	transformData.viewPosition = camera->GetPosition();

	SettingsData settingsData;
	settingsData.useDiffuseMap = int(this->settingsData.useDiffuseMap && renderObject.diffuseMapID);
	settingsData.useNormalMap = int(this->settingsData.useNormalMap && renderObject.normalMapID);
	settingsData.useBumpMap = int(this->settingsData.useBumpMap && renderObject.bumpMapID);
	settingsData.useSpecMap = int(this->settingsData.useSpecMap && renderObject.specMapID);
	settingsData.useCelShading = this->settingsData.useCelShading;
	settingsData.bumpWeight = this->settingsData.bumpWeight;
	

	transformBuffer.Update(transformData);
	lightingBuffer.Update(*directionalLight);
	materialBuffer.Update(renderObject.material);
	settingsBuffer.Update(settingsData);

	auto tm = TextureManager::Get();
	tm->BindPS(renderObject.diffuseMapID, 0);
	tm->BindPS(renderObject.normalMapID, 1);
	tm->BindVS(renderObject.bumpMapID, 2);

	renderObject.meshBuffer.Render();
}

void NEng::StandardEffect::SetCamera(const Camera& camera)
{
	this->camera = &camera;
}

void NEng::StandardEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	this->directionalLight = &directionalLight;
}

void NEng::StandardEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("StandardEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useDiffuseMap = (bool)this->settingsData.useDiffuseMap;
		if (ImGui::Checkbox("UseDiffuseMap", &useDiffuseMap))
		{
			settingsData.useDiffuseMap = useDiffuseMap ? 1 : 0;
		}
		bool useNormalMap = (bool)this->settingsData.useNormalMap;
		if (ImGui::Checkbox("UseNormalMap", &useNormalMap))
		{
			settingsData.useNormalMap = useNormalMap ? 1 : 0;
		}
		bool useBumpMap = (bool)this->settingsData.useBumpMap;
		if (ImGui::Checkbox("UseBumpMap", &useBumpMap))
		{
			settingsData.useBumpMap = useBumpMap ? 1 : 0;
		}
		bool useSpecMap = (bool)this->settingsData.useSpecMap;
		if (ImGui::Checkbox("UseSpecMap", &useSpecMap))
		{
			settingsData.useSpecMap = useSpecMap ? 1 : 0;
		}
		bool useCelShading = (bool)this->settingsData.useCelShading;
		if (ImGui::Checkbox("UseCelShading", &useCelShading))
		{
			settingsData.useCelShading = useCelShading ? 1 : 0;
		}
		ImGui::DragFloat("BumpWeight", &settingsData.bumpWeight, 0.1f, 0.0f, 2.0f);
	}
}
