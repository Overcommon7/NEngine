#include "Precompiled.h"
#include "VertexShader.h"
#include "GraphicsSystem.h"
#include "VertexTypes.h"

namespace NEng
{
	void VertexShader::Initalize(const std::filesystem::path& filepath, uint32_t uint)
	{
		auto device = GraphicsSystem::Get()->GetDevice();

		std::filesystem::path shaderFile = "../../Assets/Shaders/DoSomething.fx";

		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;

		auto hr = D3DCompileFromFile(
			shaderFile.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"VS", "vs_5_0",
			shaderFlags, 0,
			&shaderBlob,
			&errorBlob
		);

		hr = device->CreateVertexShader(
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			nullptr,
			&vertexShader);

		vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;

		vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
		vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

		hr = device->CreateInputLayout(
			vertexLayout.data(),
			(UINT)vertexLayout.size(),
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			&inputLayout);

		SafeRelease(shaderBlob);
		SafeRelease(errorBlob);
	}

	void VertexShader::Terminate()
	{
		SafeRelease(inputLayout);
		SafeRelease(vertexBuffer);
	}

	void VertexShader::Bind()
	{
		auto context = GraphicsSystem::Get()->GetContext();

		context->VSSetShader(vertexShader, nullptr, 0);
		context->IASetInputLayout(inputLayout);
	}
}

