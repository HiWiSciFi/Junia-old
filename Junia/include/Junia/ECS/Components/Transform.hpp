#pragma once

#include "../../../JMath/Vector3.hpp"
#include "../../../JMath/Vector4.hpp"

namespace Junia
{
	/**
	 * @brief A component holding position, rotation and scale information about
	 *        an object
	*/
	struct Transform
	{
		/**
		 * @brief The position component
		*/
		JMath::Vec3 position;

		// TODO(HiWiSciFi): Replace with Quaternion [05-Apr-23]
		/**
		 * @brief The rotation component
		*/
		JMath::Vec4 rotation;

		/**
		 * @brief The scale component
		*/
		JMath::Vec3 scale;
	};
} // namespace Junia
