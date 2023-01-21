#pragma once

namespace NEng
{
	class Matrix4
	{
	public:
		union
		{
			float
				_11, _12, _13, _14,
				_21, _22, _23, _24,
				_31, _32, _33, _34,
				_41, _42, _43, _44;

			array<float, 16> v;
		};


		Matrix4() = default;
		Matrix4(const Matrix4& m) = default;
		Matrix4(const vector<float>& f);
		Matrix4(const vector<vector<float>>& f);
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

		const static Matrix4 Zero;
		const static Matrix4 Identity;

		static Matrix4 RotationX(float rad);
		static Matrix4 RotationY(float rad);
		static Matrix4 RotationZ(float rad);
		static Matrix4 RotationAxis(const Vector3& axis, const float& rad);
		static Matrix4 Scaling(float s);
		static Matrix4 Scaling(Vector3 s);
		static Matrix4 Scaling(float sx, float sy, float sz);
		static Matrix4 Translation(Vector3 d);
		static Matrix4 Translation(float dx, float dy, float dz);

		Vector3 TransformCoord(Vector3 v) const; // assume w = 1
		Vector3 TransformNormal(Vector3 v) const; // assume w = 0
		float Determinant() const;
		Matrix4 Adjoint() const;
		Matrix4 Transpose() const;
		Matrix4 Inverse() const;
	};
}
