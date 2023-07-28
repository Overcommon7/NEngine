#pragma once

#include "Colors.h"

namespace NEng
{
	struct Material
	{
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		Color emmisive = Colors::Black;
		float specularPower = 10.f;
		const float padding[3] = { 0.0f };
	};
}
