#pragma once

#include <vulkan/vulkan.hpp>

namespace Vulkan {

// -----------------------------------------------------------------------------
// -------------------------------- Declaration --------------------------------
// -----------------------------------------------------------------------------

class CommandBuffer final {
public:
	CommandBuffer(VkCommandPool pool, VkQueue queue);
	~CommandBuffer();

	void Begin();
	void End();
	void Submit(VkFence fence);
	inline void Submit();

	void CmdCopyBuffer(VkBuffer src, VkDeviceSize srcOffset, VkBuffer dst, VkDeviceSize dstOffset, VkDeviceSize size);

private:
	VkCommandPool pool;
	VkCommandBuffer buffer;
	VkQueue queue;
};

// -----------------------------------------------------------------------------
// ------------------------------- Implementation ------------------------------
// -----------------------------------------------------------------------------

inline void CommandBuffer::Submit() {
	Submit(VK_NULL_HANDLE);
}

} // namespace Vulkan
