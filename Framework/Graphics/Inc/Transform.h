#pragma once

#include "Common.h"

namespace NEng
{
	struct Transform
	{
		Vector3 position = Vector3::Zero;
		Quaternion rotation = Quaternion::Identity;
		Vector3 scale = Vector3::One;

		Matrix4 GetMatrix4() const
		{
			return
			{
				Matrix4::Scaling(scale) *
				Matrix4::MatrixRotationQuaternion(rotation) *
				Matrix4::Translation(position)
			};

		}
	};
}
