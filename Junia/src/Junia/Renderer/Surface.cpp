#include <Junia/Renderer/Surface.hpp>
#include "../../Platform/Vulkan/VulkanSurface.hpp"
#include <stdexcept>

namespace Junia {

std::shared_ptr<Surface> Surface::Create(Junia::Window* window, JMath::Vec2ui resolution, VSyncMode vsync) {
	return std::make_shared<Vulkan::VulkanSurface>(window, resolution, vsync);
}

Surface::~Surface() {
}

} // namespace Junia
