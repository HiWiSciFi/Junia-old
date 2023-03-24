#include <Junia/Renderer/Renderer.hpp>

#include "../../Platform/Vulkan.hpp"

namespace Junia
{
	namespace Renderer
	{
		const std::vector<Junia::RenderDevice*>& GetDevices()
		{
			return Vulkan::GetDevices();
		}

		void PickDevice(Junia::RenderDevice* device)
		{
			Vulkan::PickDevice(device);
		}
	}
}
