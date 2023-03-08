#pragma once
#include <../NEngine/Inc/NEngine.h>
class SkySphere
{
	NEng::MeshBuffer mMeshBuffer;
	NEng::Texture mDiffuseTexture;
	NEng::Matrix4 mTransform;
public:
	void Initialize();
	void Terminate();
	void Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio = 0.f, bool usetransform = true);
};



class Planet
{
public:
	enum class Type
	{
		Sun = 0,
		Mecury,
		Venus,
		Earth,
		Mars,
		Jupiter,
		Saturn,
		Uranus,
		Neptune,
		Pluto
	};

	float angle = 0;
	float rotation = 0;
	float size = 0;

	string filepath = "";
	NEng::MeshBuffer mMeshBuffer = {};
	NEng::Texture mDiffuseTexture = {};
	NEng::Matrix4 mTransform = {};
	Type type;

	int rings = 0;
	int slices = 0;

	static inline Type FOLLOW_TARGET = Type::Sun;
public:

	

	float moveSpeed = 0;
	float orbit = 0;

	Planet() {}
	Planet(const string& filepath, Type type) : filepath(filepath), type(type) {}

	void Initialize(float relativeSize, float relativeSpeed, float relativeOrbit, float relativeRotation);
	void Terminate();
	void Render(NEng::Camera& camera, NEng::ConstantBuffer& constantBuffer, const float& acpectRatio = 0.f, bool usetransform = true);
	void Update(float deltaTime);
	void SetPosition(const NEng::Vector3& pos) { mTransform._41 = pos.x; mTransform._42 = pos.y; mTransform._43 = pos.z; }
	void SetTarget() { FOLLOW_TARGET = type; }

	static inline float EARTH_ORBIT = 10.f;
	static inline float EARTH_RADIUS = 1.f;
	static inline float EARTH_SPEED = 0.4f;
	static inline float EARTH_ROTATION = 0.25f;

	static inline bool DEBUG_DRAW = true;
	static inline NEng::Vector3 RENDER_POSITION = { 0, 1, -3 };
	static inline NEng::Vector3 RENDER_LOOK = { 0, 0, 0 };
};
