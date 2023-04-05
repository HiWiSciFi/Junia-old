#pragma once

#include <cstdint>
#include <string>

namespace Junia
{
	/**
	 * @brief The hardware type of a Render Device
	*/
	enum class RenderDeviceType : uint8_t
	{
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
	class RenderDevice
	{
	protected:
		// TODO(HiWiSciFi): move to getter / setter [05-Apr-23]
		RenderDeviceType type = RenderDeviceType::OTHER;
		// TODO(HiWiSciFi): move to getter / setter [05-Apr-23]
		uint32_t rating = 0;

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
		[[nodiscard]] inline RenderDeviceType GetType() const { return type; }

		/**
		 * @brief Get the rating of this device
		 * @return A value representing how "good" this device is (0 if the
		 *         device is not suitable for rendering)
		*/
		[[nodiscard]] inline uint32_t GetRating() const { return rating; }

		/**
		 * @brief Get the identifier of the device
		 * @return A string containing the name of this device
		*/
		[[nodiscard]] virtual const std::string& GetName() const = 0;
	};
} // namespace Junia
