#include "ExtensionLoader.hpp"

static PFN_vkCmdBeginDebugUtilsLabelEXT func_vkCmdBeginDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkCmdBeginDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer,
	const VkDebugUtilsLabelEXT* pLabelInfo) {
	return func_vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

static PFN_vkCmdEndDebugUtilsLabelEXT func_vkCmdEndDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkCmdEndDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer) {
	return func_vkCmdEndDebugUtilsLabelEXT(commandBuffer);
}

static PFN_vkCmdInsertDebugUtilsLabelEXT func_vkCmdInsertDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkCmdInsertDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer,
	const VkDebugUtilsLabelEXT* pLabelInfo) {
	return func_vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo);
}

static PFN_vkCreateDebugUtilsMessengerEXT func_vkCreateDebugUtilsMessengerEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
	VkInstance                                  instance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pMessenger) {
	return func_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
}

static PFN_vkDestroyDebugUtilsMessengerEXT func_vkDestroyDebugUtilsMessengerEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
	VkInstance                                  instance,
	VkDebugUtilsMessengerEXT                    messenger,
	const VkAllocationCallbacks* pAllocator) {
	return func_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
}

static PFN_vkQueueBeginDebugUtilsLabelEXT func_vkQueueBeginDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkQueueBeginDebugUtilsLabelEXT(
	VkQueue                                     queue,
	const VkDebugUtilsLabelEXT* pLabelInfo) {
	return func_vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo);
}

static PFN_vkQueueEndDebugUtilsLabelEXT func_vkQueueEndDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkQueueEndDebugUtilsLabelEXT(
	VkQueue                                     queue) {
	return func_vkQueueEndDebugUtilsLabelEXT(queue);
}

static PFN_vkQueueInsertDebugUtilsLabelEXT func_vkQueueInsertDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkQueueInsertDebugUtilsLabelEXT(
	VkQueue                                     queue,
	const VkDebugUtilsLabelEXT* pLabelInfo) {
	return func_vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo);
}

static PFN_vkSetDebugUtilsObjectNameEXT func_vkSetDebugUtilsObjectNameEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectNameEXT(
	VkDevice                                    device,
	const VkDebugUtilsObjectNameInfoEXT* pNameInfo) {
	return func_vkSetDebugUtilsObjectNameEXT(device, pNameInfo);
}

static PFN_vkSetDebugUtilsObjectTagEXT func_vkSetDebugUtilsObjectTagEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectTagEXT(
	VkDevice                                    device,
	const VkDebugUtilsObjectTagInfoEXT* pTagInfo) {
	return func_vkSetDebugUtilsObjectTagEXT(device, pTagInfo);
}

static PFN_vkSubmitDebugUtilsMessageEXT func_vkSubmitDebugUtilsMessageEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(
	VkInstance                                  instance,
	VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData) {
	return func_vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData);
}

namespace Junia::Vulkan {

template<typename FUNC>
static FUNC vkLoadFunc(VkInstance instance, const char* funcName) {
	FUNC func = reinterpret_cast<FUNC>(vkGetInstanceProcAddr(instance, funcName));
	if (func == nullptr) throw std::runtime_error("failed to load vulkan function");
	return func;
}

void LoadExtensions(VkInstance instance, std::vector<const char*>& extensions) {
	for (const auto& extension : extensions) {
		if (strcmp(extension, VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0) {
			func_vkCmdBeginDebugUtilsLabelEXT    = Vulkan::vkLoadFunc<PFN_vkCmdBeginDebugUtilsLabelEXT>    (instance, "vkCmdBeginDebugUtilsLabelEXT"   );
			func_vkCmdEndDebugUtilsLabelEXT      = Vulkan::vkLoadFunc<PFN_vkCmdEndDebugUtilsLabelEXT>      (instance, "vkCmdEndDebugUtilsLabelEXT"     );
			func_vkCmdInsertDebugUtilsLabelEXT   = Vulkan::vkLoadFunc<PFN_vkCmdInsertDebugUtilsLabelEXT>   (instance, "vkCmdInsertDebugUtilsLabelEXT"  );
			func_vkCreateDebugUtilsMessengerEXT  = Vulkan::vkLoadFunc<PFN_vkCreateDebugUtilsMessengerEXT>  (instance, "vkCreateDebugUtilsMessengerEXT" );
			func_vkDestroyDebugUtilsMessengerEXT = Vulkan::vkLoadFunc<PFN_vkDestroyDebugUtilsMessengerEXT> (instance, "vkDestroyDebugUtilsMessengerEXT");
			func_vkQueueBeginDebugUtilsLabelEXT  = Vulkan::vkLoadFunc<PFN_vkQueueBeginDebugUtilsLabelEXT>  (instance, "vkQueueBeginDebugUtilsLabelEXT" );
			func_vkQueueEndDebugUtilsLabelEXT    = Vulkan::vkLoadFunc<PFN_vkQueueEndDebugUtilsLabelEXT>    (instance, "vkQueueEndDebugUtilsLabelEXT"   );
			func_vkQueueInsertDebugUtilsLabelEXT = Vulkan::vkLoadFunc<PFN_vkQueueInsertDebugUtilsLabelEXT> (instance, "vkQueueInsertDebugUtilsLabelEXT");
			func_vkSetDebugUtilsObjectNameEXT    = Vulkan::vkLoadFunc<PFN_vkSetDebugUtilsObjectNameEXT>    (instance, "vkSetDebugUtilsObjectNameEXT"   );
			func_vkSetDebugUtilsObjectTagEXT     = Vulkan::vkLoadFunc<PFN_vkSetDebugUtilsObjectTagEXT>     (instance, "vkSetDebugUtilsObjectTagEXT"    );
			func_vkSubmitDebugUtilsMessageEXT    = Vulkan::vkLoadFunc<PFN_vkSubmitDebugUtilsMessageEXT>    (instance, "vkSubmitDebugUtilsMessageEXT"   );
		}
	}
}

} // namespace Junia::Vulkan
