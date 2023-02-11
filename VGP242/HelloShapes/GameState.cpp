#include "GameState.h"

void GameState::Render()
{
	GraphicsSystem::Get()->SetClearColor(Colors::Black);
	auto context = GraphicsSystem::Get()->GetContext();

	context->VSSetShader(vertexShader, nullptr, 0);
	context->IASetInputLayout(inputLayout);
	context->PSSetShader(pixelShader, nullptr, 0);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->Draw((UINT)vertices.size(), 0);
}

void GameState::Initialize()
{
	CreateShape();
	
	auto device = GraphicsSystem::Get()->GetDevice();

	D3D11_BUFFER_DESC buffer{};

	buffer.ByteWidth = static_cast<UINT>(vertices.size()) * sizeof(Vertex);
	buffer.Usage = D3D11_USAGE_DEFAULT;
	buffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer.MiscFlags = 0;
	buffer.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA init{};
	init.pSysMem = vertices.data();

	HRESULT hr = device->CreateBuffer(&buffer, &init, &vertexBuffer);

	std::filesystem::path shaderFile = "../../Assets/Shaders/DoSomething.fx";

	vertexShader.I

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	hr = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);

	vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;

	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
	vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);

	hr = D3DCompileFromFile(
		shaderFile.c_str(),
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

void GameState::Terminate()
{
	vertices.clear();
	SafeRelease(vertexBuffer);
	SafeRelease(pixelShader);
}

void GameState::Update(float deltaTime)
{
	auto input = NEng::Input::InputSystem::Get();
	if (input->IsKeyPressed(NEng::Input::KeyCode::ONE))	App::ChangeState("TrifroceState");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::TWO)) App::ChangeState("SquareState");
	else if (input->IsKeyPressed(NEng::Input::KeyCode::THREE)) App::ChangeState("HeartState");
}