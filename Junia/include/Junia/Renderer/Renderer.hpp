#pragma once

#include <vector>
#include <memory>

#include "RenderDevice.hpp"

namespace Junia {

class Renderer final {
public:
	/**
	 * @brief Get available render devices
	 * @return a reference to a vector containing a list of pointers to valid
	 *         render devices
	*/
	static const std::vector<std::shared_ptr<Junia::RenderDevice>> GetDevices();

	/**
	 * @brief Pick a device to render on
	 * @param device The device to select or nullptr to select the one with the
	 *               highest rating (see GetDevices())
	*/
	static void PickDevice(std::shared_ptr<Junia::RenderDevice> device);
};

} // namespace Junia::Renderer
