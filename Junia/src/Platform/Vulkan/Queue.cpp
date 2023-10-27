#include "Queue.hpp"

namespace Junia::Vulkan {

Vulkan::Queue::Queue() : valid(false), family(0), queue(VK_NULL_HANDLE) {

}

Vulkan::Queue::Queue(std::uint32_t family, VkDevice device) : valid(true), family(family) {
	UpdateQueue(device);
}

void Vulkan::Queue::UpdateQueue(VkDevice device) {
	if (!valid || device == VK_NULL_HANDLE) this->queue = VK_NULL_HANDLE;
	else vkGetDeviceQueue(device, this->family, 0, &this->queue);
}

void Vulkan::Queue::WaitIdle() {
	if (this->queue != VK_NULL_HANDLE) vkQueueWaitIdle(this->queue);
}

} // namespace Junia::Vulkan
