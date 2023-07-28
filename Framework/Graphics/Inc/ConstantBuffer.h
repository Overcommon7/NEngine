#pragma once

namespace NEng
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer() = default;
		virtual ~ConstantBuffer();

		virtual void Initialize(uint32_t bufferSize);
		void Terminate();

		virtual void Update(const void* data);
		void BindVS(uint32_t slot);
		void BindPS(uint32_t slot);

	private:
		ID3D11Buffer* mConstantBuffer = nullptr;
	};

	template<class DataType>
	class TypedConstantBuffer final : public ConstantBuffer
	{
	public:
		void Initialize()
		{
			if (sizeof(DataType) % 16 != 0)
				throw CreateException("Data type must be 16 byte aligned", __FILE__, __LINE__);

			ConstantBuffer::Initialize(sizeof(DataType));
		}

		void Update(const DataType& data)
		{
			ConstantBuffer::Update(&data);
		}
	};
}
