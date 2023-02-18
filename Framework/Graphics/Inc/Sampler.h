#pragma once
namespace NEng
{
	class Sampler
	{
	public:
		enum class Filter { Point, Linear, Anistropic };
		enum class Addressmode { Border, Clmap, Mirri, Wrap };

		Sampler() = default;
		Sampler(const Sampler&) = delete;
		Sampler& operator=(const Sampler&) = delete;
		Sampler(Sampler&& t) noexcept;
		Sampler& operator=(Sampler&& t) noexcept;

		void Initialize(Filter filter, Addressmode addressMode);
		void Terminate();
		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;

	private:
		ID3D11SamplerState* mSamplerState = nullptr;
	};
}
