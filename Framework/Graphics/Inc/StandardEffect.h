#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

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

		void DebugUI();

	private:
		ConstantBuffer transformBuffer;
		VertexShader vertexShader;
		PixelShader pixelShader;
		Sampler sampler;

		const Camera* camera = nullptr;
	};
}
