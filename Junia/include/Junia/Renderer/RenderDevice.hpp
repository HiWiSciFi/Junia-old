#pragma once

#include <cstdint>
#include <string>

namespace Junia {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

/**
 * @brief The hardware type of a Render Device
*/
enum class RenderDeviceType : std::uint8_t {
	OTHER          = 0,
	CPU            = 1,
	INTEGRATED_GPU = 2,
	VIRTUAL_GPU    = 3,
	DISCRETE_GPU   = 4
};

/**
 * @brief A wrapper for devices that can be used for rendering (currently
 *        only supported on Vulkan)
*/
class RenderDevice {
private:
	RenderDeviceType type = RenderDeviceType::OTHER;
	std::uint32_t rating = 0;

protected:
	/**
	 * @brief Set the Device type of this render device
	 * @param type The type to set it to
	*/
	inline void SetType(RenderDeviceType type);

	/**
	 * @brief Set the rating value for this device
	 * @param rating The rating to set it to
	*/
	inline void SetRating(std::uint32_t rating);

public:
	virtual ~RenderDevice() = 0;

	/**
	 * @brief Pick this device for rendering (only call once)
	*/
	virtual void Pick() = 0;

	/**
	 * @brief Get the hardware type of this device
	 * @return A RenderDeviceType representing the type of hardware this
	 *         device is implemented on
	*/
	[[nodiscard]] inline RenderDeviceType GetType() const;

	/**
	 * @brief Get the rating of this device
	 * @return A value representing how "good" this device is (0 if the
	 *         device is not suitable for rendering)
	*/
	[[nodiscard]] inline std::uint32_t GetRating() const;

	/**
	 * @brief Get the identifier of the device
	 * @return A string containing the name of this device
	*/
	[[nodiscard]] virtual const std::string& GetName() const = 0;
};

// -----------------------------------------------------------------------------
// ------------------------------ Implementations ------------------------------
// -----------------------------------------------------------------------------

inline void RenderDevice::SetType(RenderDeviceType type) {
	this->type = type;
}

inline void RenderDevice::SetRating(std::uint32_t rating) {
	this->rating = rating;
}

inline RenderDeviceType RenderDevice::GetType() const {
	return this->type;
}

inline std::uint32_t RenderDevice::GetRating() const {
	return this->rating;
}

} // namespace Junia
