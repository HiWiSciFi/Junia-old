#pragma once

#include "RenderDevice.hpp"
#include <vector>

namespace Junia::Renderer {

/**
 * @brief Get available render devices
 * @return a reference to a vector containing a list of pointers to valid
 *         render devices
*/
const std::vector<Junia::RenderDevice*>& GetDevices();

/**
 * @brief Pick a device to render on
 * @param device The device to select or nullptr to select the one with the
 *               highest rating (see GetDevices() and
 *               Junia::RenderDevice::Pick())
*/
void PickDevice(Junia::RenderDevice* device);

} // namespace Junia::Renderer
