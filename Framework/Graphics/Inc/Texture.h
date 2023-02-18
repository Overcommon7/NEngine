#pragma once
namespace NEng
{
	class Texture
	{
	public:
		enum class Format
		{
			RGBA_U8,
			RGBA_U32
		};
		static void UnbindPS(uint32_t slot);
		Texture() = default;
		virtual ~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		Texture(Texture&& t) noexcept;
		Texture& operator=(Texture&& t) noexcept;

		virtual void Initialize(const std::filesystem::path& filename);
		virtual void Initialize(uint32_t width, uint32_t height, Format format);
		virtual void Terminate();

		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;

		inline void* GetRawData() const { return mShaderResourceView; }

	protected:
		inline DXGI_FORMAT GetDXGIFormat(const Format& format);
		ID3D11ShaderResourceView* mShaderResourceView = nullptr;
	};
}
