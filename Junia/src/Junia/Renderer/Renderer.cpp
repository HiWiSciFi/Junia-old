#include <Junia/Renderer/Renderer.hpp>

#include "../../Platform/Vulkan/Instance.hpp"

namespace Junia {

const std::vector<std::shared_ptr<RenderDevice>> Renderer::GetDevices() {
	const auto& nativeDevices = Vulkan::Instance::GetDevices();
	return { nativeDevices.begin(), nativeDevices.end() };
}

void Renderer::PickDevice(std::shared_ptr<Junia::RenderDevice> device) {
	Vulkan::Instance::PickDevice(static_pointer_cast<Vulkan::RenderDevice>(device));
}

} // namespace Junia::Renderer
