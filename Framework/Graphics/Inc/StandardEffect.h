#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "LightType.h"
#include "Material.h"

namespace NEng
{
	class Camera;
	class RenderObject;
	class Texture;

	class StandardEffect final
	{	
	public:
		void Initialize(const std::filesystem::path& filepath);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);

		void DebugUI();

	private:

		struct TransformData
		{
			Matrix4 world;
			Matrix4 wvp;
			Vector3 viewPosition;
			const float padding = 0;
		};

		struct SettingsData
		{
			int useDiffuseMap = 1;
			int useNormalMap = 1;
			const int padding[2] = { 0 };
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightingBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		MaterialBuffer materialBuffer;
		TransformBuffer transformBuffer;
		LightingBuffer lightingBuffer;
		SettingsBuffer settingsBuffer;

		VertexShader vertexShader;
		PixelShader pixelShader;
		Sampler sampler;

		SettingsData settingsData;

		const Camera* camera = nullptr;
		const DirectionalLight* directionalLight = nullptr;
	};
}
