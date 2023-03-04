#include "RenderObject.h"

using namespace NEng;

void SkySphere::Initialize()
{
	auto sphere = MeshBuilder::CreateSkySpherePX(100, 100, 100);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize("../../Assets/Images/skysphere/sunrise.jpg");
	mTransform = Matrix4::Identity;
}

void SkySphere::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void SkySphere::Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio, bool usetransform)
{
	mDiffuseTexture.BindPS(0);

	camera.SetAspectRatio(acpectRatio);

	

	Matrix4 matWorld = usetransform ? mTransform : Matrix4::Identity;
	Matrix4 matFinal = (matWorld * camera.GetViewMatrix() * camera.GetProjectionMatrix()).Transpose();

	constantBuffer.Update(&matFinal);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();
   
	Texture::UnbindPS(0);
}

void SkySphere::Update(float deltaTime)
{
}



void Earth::Initialize()
{
	auto sphere = MeshBuilder::CreateSpherePX(30, 30, 1);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize("../../Assets/Textures/earth.jpg");
	mTransform = Matrix4::Identity;
}

void Earth::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Earth::Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio, bool usetransform)
{
	mDiffuseTexture.BindPS(0);

	camera.SetAspectRatio(acpectRatio);

	Matrix4 matWorld = usetransform ? mTransform : Matrix4::Identity;
	Matrix4 matFinal = (matWorld * camera.GetViewMatrix() * camera.GetProjectionMatrix()).Transpose();

	constantBuffer.Update(&matFinal);
	constantBuffer.BindVS(0);

	mMeshBuffer.Render();

	Texture::UnbindPS(0);
}

void Earth::Update(float deltaTime)
{
}
