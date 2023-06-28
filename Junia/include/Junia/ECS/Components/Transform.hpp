#pragma once

#include "../../../JMath/Vector3.hpp"

namespace Junia {

/**
 * @brief A component holding position, rotation and scale information about
 *        an object
*/
struct Transform {
	/**
	 * @brief The position component
	*/
	JMath::Vec3 position;

	// TODO(HiWiSciFi): Replace with Quaternion [05-Apr-23]
	/**
	 * @brief The rotation component
	*/
	JMath::Vec3 rotation;

	/**
	 * @brief The scale component
	*/
	JMath::Vec3 scale;

	Transform() = default;

	Transform(const JMath::Vec3& position, const JMath::Vec3& rotation, const JMath::Vec3& scale)
		: position(position), rotation(rotation), scale(scale) { }
};

} // namespace Junia
