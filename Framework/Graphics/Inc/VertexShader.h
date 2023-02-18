#pragma once

namespace NEng
{
	class VertexShader final
	{
	public:
		template<class VertexType>
		void Initalize(const std::filesystem::path& filepath)
		{
			Initalize(filepath, VertexType::Format);
		}
		void Initalize(const std::filesystem::path& filepath, uint32_t uint);
		void Terminate();

		void Bind();

	private:
		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11VertexShader* vertexShader = nullptr;
		ID3D11InputLayout* inputLayout = nullptr;
	};
}
