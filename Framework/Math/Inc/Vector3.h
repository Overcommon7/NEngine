#pragma once
#include "NMath.h"

namespace NEng
{
	class Vector3
	{
	public:
		 
		union 
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			
			array<float, 3> v;
		};

		const static Vector3 Zero;
		const static Vector3 One;
		const static Vector3 XAxis;
		const static Vector3 YAxis;
		const static Vector3 ZAxis;

		constexpr Vector3() noexcept : Vector3(0.0f) {}
		explicit constexpr Vector3(float f) noexcept : Vector3(f, f, f) {}
		constexpr Vector3(float x, float y, float z) noexcept : x{ x }, y{ y }, z{ z } {}

		constexpr Vector3& operator=(const Vector3& vec) = default;
		constexpr bool operator==(const Vector3& vec) const { return equals(x, vec.x) && equals(y, vec.y) && equals(z, vec.z); }
		constexpr bool operator!=(const Vector3& vec) const { return !(equals(x, vec.x) && equals(y, vec.y) && equals(z, vec.z)); }

		constexpr Vector3 operator-() const { return { -x, -y, -z }; }
		constexpr Vector3 operator+(Vector3 b) const { return { x + b.x, y + b.y, z + b.z }; }
		constexpr Vector3 operator-(Vector3 b) const { return { x - b.x, y - b.y, z - b.z }; }
		constexpr Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
		constexpr Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }

		constexpr Vector3& operator+=(const Vector3& vec) { this->x += vec.x, this->y += vec.y, this->z += vec.z; return *this; }
		constexpr Vector3& operator-=(const Vector3& vec) { this->x -= vec.x, this->y -= vec.y, this->z -= vec.z; return *this; }
		constexpr Vector3& operator/=(const float& f) { return *this; this->x /= f, this->y /= f, this->z /= f ; return *this;}
		constexpr Vector3& operator*=(const float& f) { this->x *= f, this->y *= f, this->z *= f; return *this;}

		inline float Magnitude() const
		{
			return sqrtf((x * x) + (y * y) + (z * z));
		}
		inline float MagnitudeSqr() const
		{
			const float mag = Magnitude();
			return mag * mag;
		}
		inline float DotProduct(const Vector3& vec) const
		{
			return (vec.x * this->x) + (vec.y * this->y) + (vec.z * this->z);
		}
		inline Vector3 Normalize() const
		{
			const float mag = Magnitude();
			return Vector3(x / mag, y / mag, z / mag);
		}
		inline Vector3 CrossProduct(const Vector3& w) const
		{
			return Vector3(
				(this->y * w.z) - (this->z * w.y),
				(this->z * w.x) - (this->x * w.z),
				(this->x * w.y) - (this->y * w.x));
		}
		inline Vector3 Lerp(const Vector3& vec, const float& t) const
		{
			return Vector3(
				lerp(x, vec.x, t),
				lerp(y, vec.y, t),
				lerp(z, vec.z, t));
		}

		inline float Distance(const Vector3& b)
		{
			return sqrt(abs((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z)));
		}

		inline float DistanceSqr(const Vector3& b)
		{
			return abs((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
		}
	};
}
