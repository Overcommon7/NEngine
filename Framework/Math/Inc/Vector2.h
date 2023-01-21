#pragma once

namespace NEng
{

		class Vector2
		{
		public:
			union
			{
				struct { float x, y; };
				std::array<float, 2> v;// same as float[2]
			};

			constexpr Vector2() noexcept : Vector2(0.0f) {}
			explicit constexpr Vector2(float f) noexcept : Vector2(f, f) {}
			constexpr Vector2(float x, float y) noexcept : x{ x }, y{ y } {}

			const static Vector2 Zero;
			const static Vector2 One;
			const static Vector2 XAxis;
			const static Vector2 YAxis;

			Vector2(const Vector2& vec) = default;
			Vector2& operator=(const Vector2& vec) = default;
			bool operator==(const Vector2& vec) const { return vec.x == this->x && vec.y == this->y; }
			bool operator!=(const Vector2& vec) const { return vec.x != this->x || vec.y != this->y; }
			constexpr Vector2 operator-() const { return { -x, -y }; }
			constexpr Vector2 operator+(Vector2 b) const { return { x + b.x, y + b.y }; }
			constexpr Vector2 operator-(Vector2 b) const { return { x - b.x, y - b.y }; }
			constexpr Vector2 operator*(float s) const { return { x * s, y * s }; }
			constexpr Vector2 operator/(float s) const { return { x / s, y / s }; }

			constexpr Vector2& operator+=(const Vector2& v) { x += v.x; y += v.y; return *this; }
			constexpr Vector2& operator-=(const Vector2& v) { x -= v.x; y -= v.y; return *this; }
			constexpr Vector2& operator*=(float s) { x *= s; y *= s; return *this; }
			constexpr Vector2& operator/=(float s) { x /= s; y /= s; return *this; }

			float Magnitude() const
			{
				return sqrtf((x * x) + (y * y));
			}
			float MagnitudeSquared() const
			{
				const float mag = Magnitude();
				return mag * mag;
			}
			float DotProduct(const Vector2& vec) const
			{
				return (vec.x * this->x) + (vec.y * this->y);
			}
			Vector2 Normalize() const
			{
				const float mag = Magnitude();
				return Vector2(x / mag, y / mag);
			}
	};
}
