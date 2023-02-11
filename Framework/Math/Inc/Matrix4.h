#pragma once
#include "Quaternions.h"

namespace NEng
{
	class Matrix4
	{
	public:
		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			std::array<float, 16> v;
		};

		constexpr Matrix4() noexcept
			: Matrix4(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			)
		{

		}

		constexpr Matrix4(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44
		) noexcept
			: _11(_11), _12(_12), _13(_13), _14(_14)
			, _21(_21), _22(_22), _23(_23), _24(_24)
			, _31(_31), _32(_32), _33(_33), _34(_34)
			, _41(_41), _42(_42), _43(_43), _44(_44)
		{}

		Matrix4(const std::initializer_list<float> f);
		Matrix4& operator= (const Matrix4& m) = default;


		Matrix4 operator+(const Matrix4& m) const;
		Matrix4 operator-(const Matrix4& m) const;
		Matrix4 operator*(const Matrix4& m) const;
		Matrix4 operator*(const float& f) const;
		Matrix4& operator+=(const Matrix4& m);
		Matrix4& operator-=(const Matrix4& m);
		Matrix4& operator*=(const Matrix4& right);
		Matrix4& operator*=(const float& f);
		bool operator==(const Matrix4& m);

		static Matrix4 Identity;
		static Matrix4 Zero;

		static Matrix4 RotationX(float rad);
		static Matrix4 RotationY(float rad);
		static Matrix4 RotationZ(float rad);
		static Matrix4 Scaling(float s);
		static Matrix4 Scaling(Vector3 s);
		static Matrix4 Scaling(float sx, float sy, float sz);
		static Matrix4 Translation(Vector3 d);
		static Matrix4 Translation(float dx, float dy, float dz);
		static Matrix4 RotationAxis(const Vector3& axis, const float& rad);
		static Matrix4 MatrixRotationQuaternion(const Quaternion& q)
		{
			return Matrix4
			(
				1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
				(2.0f * q.x * q.y) + (2.0f * q.z * q.w),
				(2.0f * q.x * q.z) - (2.0f * q.y * q.w),
				0.0f,

				(2.0f * q.x * q.y) - (2.0f * q.z * q.w),
				1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
				(2.0f * q.y * q.z) + (2.0f * q.x * q.w),
				0.0f,

				(2.0f * q.x * q.z) + (2.0f * q.y * q.w),
				(2.0f * q.y * q.z) - (2.0f * q.x * q.w),
				1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
				0.0f,

				0.0f,
				0.0f,
				0.0f,
				1.0f
			);
		}

		Vector3 TransformCoord(Vector3 v) const; // assume w = 1
		Vector3 TransformNormal(Vector3 v) const; // assume w = 0
		float Determinant() const;
		Matrix4 Adjoint() const;
		Matrix4 Transpose() const;
		Matrix4 Inverse() const;
		

		vector<float*> GetVector();
	};
}
