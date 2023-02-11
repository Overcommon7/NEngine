#pragma once

namespace NEng
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer() = default;
		virtual ~ConstantBuffer();

		void Initialize(uint32_t bufferSize);
		void Terminate();

		void Update(const void* data);
		void BindVS(uint32_t slot);
		void BindPS(uint32_t slot);

	private:
		ID3D11Buffer* mConstantBuffer = nullptr;
	};
}
