#pragma once
#include <../NEngine/Inc/NEngine.h>

class RenderObject
{
public:

	virtual void Initialize() {}
	virtual void Terminate() {}
	virtual void Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio = 0.f, bool usetransform = true) {}
	virtual void Update(float deltaTime) {}
	void SetPosition(const NEng::Vector3& pos) { mTransform._41 = pos.x; mTransform._42 = pos.y; mTransform._43 = pos.z; }

protected:
	NEng::MeshBuffer mMeshBuffer;
	NEng::Texture mDiffuseTexture;
	NEng::Matrix4 mTransform;
};


class SkySphere : public RenderObject
{
public:
	virtual void Initialize() override;
	virtual void Terminate() override;
	virtual void Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio = 0.f, bool usetransform = true) override;
	virtual void Update(float deltaTime) override;

};

class Earth : public RenderObject
{
public:
	virtual void Initialize() override;
	virtual void Terminate() override;
	virtual void Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio = 0.f, bool usetransform = true) override;
	virtual void Update(float deltaTime) override;
};
