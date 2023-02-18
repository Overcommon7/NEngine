#include "Precompiled.h"
#include "VertexShader.h"
#include "GraphicsSystem.h"
#include "VertexTypes.h"

namespace
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> GetVertexLayout(uint32_t vertexFormat)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> desc;
		if (vertexFormat & NEng::VE_Postition)		desc.push_back({ "POSITION", 0,		 DXGI_FORMAT_R32G32B32_FLOAT,	  0,   D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA, 0 });
		if (vertexFormat & NEng::VE_Normal)			desc.push_back({ "NORMAL", 0,		 DXGI_FORMAT_R32G32B32_FLOAT,		  0,   D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA, 0 });
		if (vertexFormat & NEng::VE_Tangent)		desc.push_back({ "TANGENT", 0,		 DXGI_FORMAT_R32G32B32_FLOAT,		  0,   D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA, 0 });
		if (vertexFormat & NEng::VE_Color)			desc.push_back({ "COLOR", 0,		 DXGI_FORMAT_R32G32B32_FLOAT,		  0,   D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA, 0 });
		if (vertexFormat & NEng::VE_TexCoord)		desc.push_back({ "TEXCOORD", 0,      DXGI_FORMAT_R32G32B32_FLOAT,      0,   D3D11_APPEND_ALIGNED_ELEMENT,   D3D11_INPUT_PER_VERTEX_DATA, 0 });
		if (vertexFormat & NEng::VE_BlendIndex)		desc.push_back({ "BELNDINDICIES", 0, DXGI_FORMAT_R32G32B32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		if (vertexFormat & NEng::VE_BlendWeight)	desc.push_back({ "BLENWEIGHT", 0,    DXGI_FORMAT_R32G32B32_FLOAT,    0,    D3D11_APPEND_ALIGNED_ELEMENT,    D3D11_INPUT_PER_VERTEX_DATA, 0 });
		return desc;
	}
}

namespace NEng
{
	void VertexShader::Initalize(const std::filesystem::path& filepath, uint32_t uint)
	{
		auto device = GraphicsSystem::Get()->GetDevice();

		std::filesystem::path shaderFile = filepath;

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

		vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout = GetVertexLayout(uint);

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

