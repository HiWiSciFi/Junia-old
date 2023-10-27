#pragma once

#include <vulkan/vulkan.hpp>

namespace Junia::Vulkan {

class Queue {
public:
	Queue();
	Queue(std::uint32_t family, VkDevice queue);

	void UpdateQueue(VkDevice device);

	inline bool IsValid();
	inline std::uint32_t GetFamilyIndex();

	void WaitIdle();

private:
	bool valid;
	std::uint32_t family;
	VkQueue queue;
};

// -----------------------------------------------------------------------------
// ------------------------------- Implementation ------------------------------
// -----------------------------------------------------------------------------

inline bool Vulkan::Queue::IsValid() {
	return this->valid;
}

inline std::uint32_t Vulkan::Queue::GetFamilyIndex() {
	return this->family;
}

} // namespace Junia::Vulkan
