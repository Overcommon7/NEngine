#pragma once

#include "Colors.h"
#include "VertexTypes.h"
#include "ConstantBuffer.h"
#include "MeshBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "BlendState.h"

namespace NEng
{
	class Camera;

	class SimpleDraw final
	{
		
		SimpleDraw() = delete;
		SimpleDraw(const SimpleDraw& s) = delete;
		SimpleDraw& operator=(const SimpleDraw& s) = delete;

		inline static VertexShader mVertexShader = {};
		inline static PixelShader mPixelShader = {};
		inline static ConstantBuffer mConstantBuffer = {};
		inline static MeshBuffer mMeshBuffer = {};
		inline static BlendState mBlendState = {};
		
		inline static std::unique_ptr<VertexPC[]> mLineVerticies = {};
		inline static std::unique_ptr<VertexPC[]> mFaceVerticies = {};
		
		static inline uint32_t mLineVertexCount = 0;
		static inline uint32_t mFaceVertexCount = 0;
		static inline uint32_t mMaxVertexCount = 0;

	public:
		static void Initialize(uint32_t maxVertexCount);
		static void Terminate();

		static void AddLine(const Vector3& v0, const Vector3& v1, const Color& color);
		static void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color);

		static void AddAABB(const Vector3& min, const Vector3& max, const Color& color);
		static void AddFilledAABB(const Vector3& min, const Vector3& max, const Color& color);

		static void AddSphere(int slices, int rings, float radius, const Vector3& pos, const Color& color);

		static void AddGroundPlane(float size, const Color& color);

		static void AddTransform(const Matrix4& m);

		static void Render(const Camera& camera);
	};												  
}

