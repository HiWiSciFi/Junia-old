#pragma once

#include <vulkan/vulkan.hpp>
#include <Junia/Core/Version.hpp>
#include <vector>

#include "RenderDevice.hpp"

namespace Junia::Vulkan {

// -----------------------------------------------------------------------------
// -------------------------------- Declarations -------------------------------
// -----------------------------------------------------------------------------

class Instance {
public:
	Instance(const std::string& appName, Junia::Version appVersion, const std::string& engineName, Junia::Version engineVersion);
	~Instance();

	/**
	 * @brief Initialize Vulkan
	 * @param appName The name of the application
	 * @param appVersion The Version of the application
	 * @param engineName The name of the game engine
	 * @param engineVersion The version of the game engine
	*/
	static inline void Init(const std::string& appName, Junia::Version appVersion, const std::string& engineName, Junia::Version engineVersion);

	/**
	 * @brief Terminate Vulkan and free resources
	*/
	static inline void Terminate();

	/**
	 * @brief Get the underlying VkInstance
	 * @return The application wide VkInstance
	*/
	static inline VkInstance Get();

	/**
	 * @brief Get available render devices
	 * @return a reference to a vector containing a list of pointers to valid
	 *         render devices
	*/
	static inline std::vector<std::weak_ptr<Vulkan::RenderDevice>> GetDevices();

	/**
	 * @brief Pick a device for rendering
	 * @param device The device to use for rendering (see
	 *               Vulkan::Instance::GetDevices())
	*/
	static inline void PickDevice(std::weak_ptr<Vulkan::RenderDevice> device);

private:
	static std::unique_ptr<Instance> s_instance;
	static std::vector<std::shared_ptr<Vulkan::RenderDevice>> s_renderDevices;
	static std::shared_ptr<Vulkan::RenderDevice> s_device;

	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;

	void EnumerateDevices();
};

// -----------------------------------------------------------------------------
// ------------------------------- Implementation ------------------------------
// -----------------------------------------------------------------------------

inline void Vulkan::Instance::Init(const std::string& appName, Junia::Version appVersion, const std::string& engineName, Junia::Version engineVersion) {
	s_instance = std::make_unique<Vulkan::Instance>(appName, std::move(appVersion), engineName, std::move(engineVersion));
	s_instance->EnumerateDevices();
}

inline void Vulkan::Instance::Terminate() {
	s_instance.reset();
}

inline VkInstance Vulkan::Instance::Get() {
	return s_instance->instance;
}

inline std::vector<std::weak_ptr<Vulkan::RenderDevice>> Vulkan::Instance::GetDevices() {
	std::vector<std::weak_ptr<Vulkan::RenderDevice>> devices(s_renderDevices.begin(), s_renderDevices.end());
	return devices;
}

inline void Instance::PickDevice(std::weak_ptr<Vulkan::RenderDevice> device) {
	if (device.expired()) s_device = s_renderDevices[0];
	else s_device = device.lock();
	s_device->Pick();
}

}
