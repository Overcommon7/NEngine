#pragma once

#include "Colors.h"

namespace NEng
{
	struct DirectionalLight
	{
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		Vector3 direction = Vector3::ZAxis;
		const float padding = 0;
	};
}