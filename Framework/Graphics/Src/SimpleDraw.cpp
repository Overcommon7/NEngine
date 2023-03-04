#include "Precompiled.h"
#include "SimpleDraw.h"

#include "Camera.h"


namespace NEng
{
	void SimpleDraw::Initialize(uint32_t maxVertexCount)
	{
		std::filesystem::path shaderFile = "../../Assets/Shaders/DoTransform.fx";

		mVertexShader.Initalize<VertexPC>(shaderFile);
		mPixelShader.Initalize(shaderFile);
		mConstantBuffer.Initialize(sizeof(Matrix4));
		mMeshBuffer.Initialize(nullptr, sizeof(VertexPC), maxVertexCount);
		mBlendState.Initialize(BlendState::Mode::AlphaBlend);

		mLineVerticies = std::make_unique<VertexPC[]>(maxVertexCount);
		mLineVerticies = std::make_unique<VertexPC[]>(maxVertexCount);

		mMaxVertexCount = maxVertexCount;
	}

	void SimpleDraw::Terminate()
	{
		mVertexShader.Terminate();
		mPixelShader.Terminate();
		mMeshBuffer.Terminate();
		mConstantBuffer.Terminate();
		mBlendState.Terminate();

		mLineVerticies.reset();
		mFaceVerticies.reset();
	}

	void SimpleDraw::AddLine(const Vector3& v0, const Vector3& v1, const Color& color)
	{
		if (mLineVertexCount + 2 <= mMaxVertexCount)
		{
			mLineVerticies[mLineVertexCount++] = VertexPC{ v0, color };
			mLineVerticies[mLineVertexCount++] = VertexPC{ v1, color };
		}
	}

	void SimpleDraw::AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Color& color)
	{
		if (mLineVertexCount + 3 <= mMaxVertexCount)
		{
			mLineVerticies[mLineVertexCount++] = VertexPC{ v0, color };
			mLineVerticies[mLineVertexCount++] = VertexPC{ v1, color };
			mLineVerticies[mLineVertexCount++] = VertexPC{ v2, color };
		}
	}

	void SimpleDraw::AddAABB(const Vector3& min, const Vector3& max, const Color& color)
	{
		const Vector3 topRightF = { max.x, max.y, min.z };
		const Vector3 botRightF = { max.x, min.y, min.z };
		const Vector3 topLeftF = { min.x, max.y, min.z };
		const Vector3 botLeftF = { min.x, min.y, min.z };

		const Vector3 topRightB = { max.x, max.y, max.z };
		const Vector3 botRightB = { max.x, min.y, max.z };
		const Vector3 topLeftB = { min.x, max.y,  max.z };
		const Vector3 botLeftB = { min.x, min.y,  max.z };

		//front
		AddLine(topRightF, botRightF, color);
		AddLine(botRightF, botLeftF, color);
		AddLine(botLeftF, topLeftF, color);
		AddLine(topLeftF, topRightF, color);

		//back
		AddLine(topRightB, botRightB, color);
		AddLine(botRightB, botLeftB, color);
		AddLine(botLeftB, topLeftB, color);
		AddLine(topLeftB, topRightB, color);

		//top
		AddLine(topRightF, topRightB, color);
		AddLine(topLeftF, topLeftB, color);

		//bottom
		AddLine(botRightF, botRightB, color);
		AddLine(botLeftF, botLeftB, color);

	}

	void SimpleDraw::AddFilledAABB(const Vector3& min, const Vector3& max, const Color& color)
	{
		const Vector3 topRightF = { max.x, max.y, min.z };
		const Vector3 botRightF = { max.x, min.y, min.z };
		const Vector3 topLeftF =  { min.x, max.y, min.z };
		const Vector3 botLeftF =  { min.x, min.y, min.z };

		const Vector3 topRightB = { max.x, max.y, max.z };
		const Vector3 botRightB = { max.x, min.y, max.z };
		const Vector3 topLeftB =  { min.x, max.y, max.z };
		const Vector3 botLeftB =  { min.x, min.y, max.z };

		AddFace(topRightF, botRightF, botLeftF, color);
		AddFace(botLeftF, topLeftF, topRightF, color);

		AddFace(botLeftB, topRightB, topLeftB, color);
		AddFace(botLeftB, topLeftB, topRightB, color);

		AddFace(topRightB, topRightF, topLeftF, color);
		AddFace(botLeftF, topLeftB, topRightB, color);

		AddFace(topRightB, botLeftF, botRightF, color);
		AddFace(botLeftF, botRightB, botLeftB, color);

		AddFace(topRightB, botRightB, botRightF, color);
		AddFace(botRightF, topRightB, topRightB, color);

	}

	void SimpleDraw::AddSphere(int slices, int rings, float radius, const Vector3& pos, const Color& color)
	{
		Vector3 v0 = {};
		Vector3 v1 = {};

		float vertRotation = PI / float(rings - 1);
		float horzRotation = TWO_PI / float(slices);
		int size = 0;
		for (int r = 0; r <= rings; r++)
		{
			float ring = (float)r;
			float phi = ring * vertRotation;

			for (int s = 0; s <= slices; s++)
			{
				float slice0 = (float)s;
				float rotation0 = slice0 * horzRotation;

				float slice1 = s + 1.f;
				float rotation1 = slice1 * horzRotation;

				v0 = {
						(radius * sin(rotation0) * sin(phi)) + pos.x,
						(radius * cos(phi)) + pos.y,
						(radius * cos(rotation0) * sin(phi)) + pos.z };
				v1 = {
						(radius * sin(rotation1) * sin(phi)) + pos.x,
						(radius * cos(phi)) + pos.y,
						(radius * cos(rotation1) * sin(phi)) + pos.z };

				AddLine(v0, v1, color);

				v0 = {
						(radius * cos(phi)) + pos.x,
						(radius * cos(rotation0) * sin(phi)) + pos.y,
						(radius * sin(rotation0) * sin(phi)) + pos.z };
				v1 = {
						(radius * cos(phi)) + pos.x,
						(radius * cos(rotation1) * sin(phi)) + pos.y,
						(radius * sin(rotation1) * sin(phi)) + pos.z };

				AddLine(v0, v1, color);
			}
		}
	}

	void SimpleDraw::AddCircle(int slices, float radius, const Vector3& pos, const Color& color)
	{
		float horzRotation = TWO_PI / float(slices);
		Vector3 v0 = {};
		Vector3 v1 = {};

		for (int s = 0; s <= slices; s++)
		{
			float slice0 = (float)s;
			float rotation0 = slice0 * horzRotation;

			float slice1 = s + 1.f;
			float rotation1 = slice1 * horzRotation;

			v0 = {
					(radius *  sin(rotation0)) + pos.x,
					pos.y,
					(radius * cos(rotation0)) + pos.z 
			};
			v1 = {
					(radius * sin(rotation1)) + pos.x,
					pos.y,
					(radius * cos(rotation1)) + pos.z 
			};

			AddLine(v0, v1, color);
		}
	}

	void SimpleDraw::AddGroundPlane(float size, const Color& color)
	{
		const float hs = size * 0.5f;
		Vector3 v0 = {};
		Vector3 v1 = {};

		for (int i = 0; i <= size; ++i)
		{
			AddLine({ i - hs, 0.0f, -hs }, { i - hs, 0.0f, hs }, color);
			AddLine({ -hs, 0.0f, i - hs }, { hs, 0.0f, i - hs }, color);
		}							  
	}

	void SimpleDraw::AddTransform(const Matrix4& m)
	{
		const Vector3 side = { m._11, m._12, m._13 };
		const Vector3 up =   { m._21, m._22, m._23 };
		const Vector3 look = { m._31, m._32, m._33 };
		const Vector3 pos =  { m._41, m._42, m._43 };

		AddLine(pos, pos + side, Colors::Red);
		AddLine(pos, pos + up, Colors::Green);
		AddLine(pos, pos + look, Colors::Blue);
	}

	void SimpleDraw::Render(const Camera& camera)
	{
		auto matView = camera.GetViewMatrix();
		auto matProj = camera.GetProjectionMatrix();
		auto transform = (matView * matProj).Transpose();

		mConstantBuffer.Update(&transform);
		mConstantBuffer.BindVS(0);

		mVertexShader.Bind();
		mPixelShader.Bind();

		mBlendState.Set();

		mMeshBuffer.Update(mLineVerticies.get(), mLineVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Lines);
		mMeshBuffer.Render();

		mMeshBuffer.Update(mFaceVerticies.get(), mFaceVertexCount);
		mMeshBuffer.SetTopology(MeshBuffer::Topology::Triangles);
		mMeshBuffer.Render();

		BlendState::ClearState();

		mLineVertexCount = 0;
		mFaceVertexCount = 0;
	}
}