#include "Precompiled.h"
#include "PixelShader.h"
#include "GraphicsSystem.h"

namespace NEng
{
	void PixelShader::Initalize(const std::filesystem::path& filepath)
	{
		auto device = GraphicsSystem::Get()->GetDevice();

		ID3DBlob* shaderBlob = nullptr;
		ID3DBlob* errorBlob = nullptr;
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

		auto hr = D3DCompileFromFile(
			filepath.c_str(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"PS", "ps_5_0",
			shaderFlags, 0,
			&shaderBlob,
			&errorBlob);

		hr = device->CreatePixelShader(
			shaderBlob->GetBufferPointer(),
			shaderBlob->GetBufferSize(),
			nullptr,
			&pixelShader);

		SafeRelease(shaderBlob);
		SafeRelease(errorBlob);
	}
	void PixelShader::Terminate()
	{
		SafeRelease(pixelShader);
	}
	void PixelShader::Bind()
	{
		GraphicsSystem::Get()->GetContext()->PSSetShader(pixelShader, nullptr, 0);
	}
}