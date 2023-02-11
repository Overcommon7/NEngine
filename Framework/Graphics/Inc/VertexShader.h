#pragma once

namespace NEng
{
	class VertexShader final
	{
	public:

		void Initalize(const std::filesystem::path& filepath, uint32_t uint);
		void Terminate();

		void Bind();

	private:
		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11InputLayout* inputLayout = nullptr;
	};
}
