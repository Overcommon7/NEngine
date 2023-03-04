#pragma once

namespace NEng
{
	class BlendState final
	{
	public:
		static void ClearState();

		enum class Mode
		{
			Opaque,
			AlphaBlend,
			AlphaPremulitplied,
			Additive
		};

		BlendState() = default;
		~BlendState();

		BlendState(const BlendState& b) = delete;
		BlendState& operator=(const BlendState& b) = delete;

		void Initialize(Mode mode);
		void Terminate();

		void Set();

	private:
		ID3D11BlendState* mBlendState = nullptr;
	};						   
}

