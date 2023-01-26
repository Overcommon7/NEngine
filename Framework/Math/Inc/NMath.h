#pragma once
#include "Common.h"

namespace NEng
{
	template <typename T> 
	inline constexpr T lerp(const T& a, const T& b, const T& t)
	{
		return a + t * (b - a);
	}

	template <typename T>
	inline constexpr T abs(const T& a)
	{
		return a < 0 ? -a : a;
	}

	inline constexpr float equals(const float& a, const float& b)
	{
		return abs(a - b) <= 0.0001f;
	}

	template <typename T>
	inline constexpr float min(const float& a, const float& b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	inline constexpr float max(const float& a, const float& b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	inline constexpr float clamp(const float& num, const float& min, const float& max)
	{
		if (num > max) return max;
		if (num < min) return min;
		return num;
	}

	template<typename T>
	inline constexpr T sqr(const T& value)
	{
		return value * value;
	}
}
