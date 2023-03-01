#pragma once

#include "../../../JMath/Vector3.hpp"
#include "../../../JMath/Vector4.hpp"

namespace Junia
{
	struct Transform
	{
		JMath::Vec3 position;
		JMath::Vec4 rotation;
		JMath::Vec3 scale;
	};
}
