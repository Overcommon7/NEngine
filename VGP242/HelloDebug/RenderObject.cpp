#include "RenderObject.h"

using namespace NEng;

void SkySphere::Initialize()
{
	auto sphere = MeshBuilder::CreateSkySpherePX(1000, 1000, 1000);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize("../../Assets/Images/skysphere/space.jpg");
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



void Planet::Initialize(float relativeSize, float relativeSpeed, float relativeOrbit, float relativeRotation)
{
	slices = 30 * relativeSize;
	rings = 30 * relativeSize;

	auto sphere = MeshBuilder::CreateSpherePX(slices, rings, EARTH_RADIUS * relativeSize);
	mMeshBuffer.Initialize(sphere);

	mDiffuseTexture.Initialize(filepath);
	mTransform = Matrix4::Identity;

	orbit = relativeOrbit;
	moveSpeed = relativeSpeed;
	rotation = (1 / relativeRotation);
}

void Planet::Terminate()
{
	mDiffuseTexture.Terminate();
	mMeshBuffer.Terminate();
}

void Planet::Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio, bool usetransform)
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

void Planet::Update(float deltaTime)
{
	SetPosition({ 0, 0, 0 });
	angle += moveSpeed * deltaTime * EARTH_SPEED;
	Vector3 coord = { cos(angle) * orbit * EARTH_ORBIT, 0, sin(angle) * orbit * EARTH_ORBIT };
	mTransform *= Matrix4::Translation(coord) * Matrix4::RotationY(PI * (EARTH_ROTATION * rotation) *deltaTime);

	if (FOLLOW_TARGET == type)
	{
		RENDER_POSITION = coord;
		RENDER_LOOK = coord;
		RENDER_POSITION.z -= EARTH_RADIUS * size * 1.25f;
		RENDER_LOOK.z += EARTH_RADIUS * size * 1.25f;
	}
		

	if (DEBUG_DRAW)
		SimpleDraw::AddCircle(slices, orbit * EARTH_ORBIT, { 0, 0, 0 }, Colors::HotPink);
}
																			  