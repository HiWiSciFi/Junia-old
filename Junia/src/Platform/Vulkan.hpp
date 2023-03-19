#pragma once

#include <Junia/Core/Version.hpp>
#include <Junia/Renderer/RenderDevice.hpp>
#include <string>
#include <vector>

namespace Vulkan
{
	/**
	 * @brief Initialize Vulkan
	 * @param appName the name of the application
	 * @param appVersion the version of the application
	 * @param engineName the name of the engine
	 * @param engineVersion the version of the engine
	 * @param debug if debug extensions and logging should be enabled
	*/
	void Init(std::string const& appName, Junia::Version const& appVersion, std::string const& engineName, Junia::Version const& engineVersion, bool debug = false);

	/**
	 * @brief Cleanup resources used by Vulkan
	*/
	void Cleanup();

	/**
	 * @brief Register a Vulkan Instance Extension Requirement
	 * @param extension the identifier of the extension
	*/
	void RequireExtension(std::string const& extension);

	/**
	 * @brief Register a Vulkan Device Extension Requirement
	 * @param extension the identifier of the extension
	*/
	void RequireDeviceExtension(std::string const& extension);

	/**
	 * @brief Get available render devices
	 * @return a reference to a vector containing a list of pointers to valid
	 *         render devices
	*/
	const std::vector<Junia::RenderDevice*>& GetDevices();

	/**
	 * @brief Pick a device to render on (only call this once!)
	 * @param device The device to select or nullptr to select the one with the
	 *        highest rating (see GetDevices() and Junia::RenderDevice::Pick())
	*/
	void PickDevice(Junia::RenderDevice* device);
}
