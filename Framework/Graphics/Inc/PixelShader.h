#pragma once

namespace NEng
{
	class PixelShader final
	{
	public:

		void Initalize(const std::filesystem::path& filepath);
		void Terminate();

		void Bind();

	private:
		ID3D11PixelShader* pixelShader = nullptr;
	};
}
