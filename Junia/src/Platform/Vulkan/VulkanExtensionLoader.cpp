#include <vulkan/vulkan.h>
#include "VulkanExtensionLoader.hpp"
#include <cstring>
#include <stdexcept>

static PFN_vkCmdBeginDebugUtilsLabelEXT func_vkCmdBeginDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkCmdBeginDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer,
	const VkDebugUtilsLabelEXT*                 pLabelInfo)
	{ return func_vkCmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo); }

static PFN_vkCmdEndDebugUtilsLabelEXT func_vkCmdEndDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkCmdEndDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer)
	{ return func_vkCmdEndDebugUtilsLabelEXT(commandBuffer); }

static PFN_vkCmdInsertDebugUtilsLabelEXT func_vkCmdInsertDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkCmdInsertDebugUtilsLabelEXT(
	VkCommandBuffer                             commandBuffer,
	const VkDebugUtilsLabelEXT*                 pLabelInfo)
	{ return func_vkCmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo); }

static PFN_vkCreateDebugUtilsMessengerEXT func_vkCreateDebugUtilsMessengerEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(
	VkInstance                                  instance,
	const VkDebugUtilsMessengerCreateInfoEXT*   pCreateInfo,
	const VkAllocationCallbacks*                pAllocator,
	VkDebugUtilsMessengerEXT*                   pMessenger)
	{ return func_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger); }

static PFN_vkDestroyDebugUtilsMessengerEXT func_vkDestroyDebugUtilsMessengerEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(
	VkInstance                                  instance,
	VkDebugUtilsMessengerEXT                    messenger,
	const VkAllocationCallbacks*                pAllocator)
	{ return func_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator); }

static PFN_vkQueueBeginDebugUtilsLabelEXT func_vkQueueBeginDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkQueueBeginDebugUtilsLabelEXT(
	VkQueue                                     queue,
	const VkDebugUtilsLabelEXT*                 pLabelInfo)
	{ return func_vkQueueBeginDebugUtilsLabelEXT(queue, pLabelInfo); }

static PFN_vkQueueEndDebugUtilsLabelEXT func_vkQueueEndDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkQueueEndDebugUtilsLabelEXT(
	VkQueue                                     queue)
	{ return func_vkQueueEndDebugUtilsLabelEXT(queue); }

static PFN_vkQueueInsertDebugUtilsLabelEXT func_vkQueueInsertDebugUtilsLabelEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkQueueInsertDebugUtilsLabelEXT(
	VkQueue                                     queue,
	const VkDebugUtilsLabelEXT*                 pLabelInfo)
	{ return func_vkQueueInsertDebugUtilsLabelEXT(queue, pLabelInfo); }

static PFN_vkSetDebugUtilsObjectNameEXT func_vkSetDebugUtilsObjectNameEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectNameEXT(
	VkDevice                                    device,
	const VkDebugUtilsObjectNameInfoEXT*        pNameInfo)
	{ return func_vkSetDebugUtilsObjectNameEXT(device, pNameInfo); }

static PFN_vkSetDebugUtilsObjectTagEXT func_vkSetDebugUtilsObjectTagEXT = nullptr;
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectTagEXT(
	VkDevice                                    device,
	const VkDebugUtilsObjectTagInfoEXT*         pTagInfo)
	{ return func_vkSetDebugUtilsObjectTagEXT(device, pTagInfo); }

static PFN_vkSubmitDebugUtilsMessageEXT func_vkSubmitDebugUtilsMessageEXT = nullptr;
VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(
	VkInstance                                  instance,
	VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData)
	{ return func_vkSubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData); }

namespace Vulkan {

extern VkInstance vkInstance;

template<typename FUNC>
static FUNC vkLoadFunc(const char* funcname) {
	FUNC func = reinterpret_cast<FUNC>(vkGetInstanceProcAddr(vkInstance, funcname));
	if (func == nullptr) throw std::runtime_error("failed to load vulkan function");
	return func;
}

void LoadExtensions(size_t extensionCount, const char** extensionNames) {
	for (size_t i = 0; i < extensionCount; i++) {
		if (strcmp(extensionNames[i], VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == 0) {
			func_vkCmdBeginDebugUtilsLabelEXT    = vkLoadFunc<PFN_vkCmdBeginDebugUtilsLabelEXT>    ("vkCmdBeginDebugUtilsLabelEXT"   );
			func_vkCmdEndDebugUtilsLabelEXT      = vkLoadFunc<PFN_vkCmdEndDebugUtilsLabelEXT>      ("vkCmdEndDebugUtilsLabelEXT"     );
			func_vkCmdInsertDebugUtilsLabelEXT   = vkLoadFunc<PFN_vkCmdInsertDebugUtilsLabelEXT>   ("vkCmdInsertDebugUtilsLabelEXT"  );
			func_vkCreateDebugUtilsMessengerEXT  = vkLoadFunc<PFN_vkCreateDebugUtilsMessengerEXT>  ("vkCreateDebugUtilsMessengerEXT" );
			func_vkDestroyDebugUtilsMessengerEXT = vkLoadFunc<PFN_vkDestroyDebugUtilsMessengerEXT> ("vkDestroyDebugUtilsMessengerEXT");
			func_vkQueueBeginDebugUtilsLabelEXT  = vkLoadFunc<PFN_vkQueueBeginDebugUtilsLabelEXT>  ("vkQueueBeginDebugUtilsLabelEXT" );
			func_vkQueueEndDebugUtilsLabelEXT    = vkLoadFunc<PFN_vkQueueEndDebugUtilsLabelEXT>    ("vkQueueEndDebugUtilsLabelEXT"   );
			func_vkQueueInsertDebugUtilsLabelEXT = vkLoadFunc<PFN_vkQueueInsertDebugUtilsLabelEXT> ("vkQueueInsertDebugUtilsLabelEXT");
			func_vkSetDebugUtilsObjectNameEXT    = vkLoadFunc<PFN_vkSetDebugUtilsObjectNameEXT>    ("vkSetDebugUtilsObjectNameEXT"   );
			func_vkSetDebugUtilsObjectTagEXT     = vkLoadFunc<PFN_vkSetDebugUtilsObjectTagEXT>     ("vkSetDebugUtilsObjectTagEXT"    );
			func_vkSubmitDebugUtilsMessageEXT    = vkLoadFunc<PFN_vkSubmitDebugUtilsMessageEXT>    ("vkSubmitDebugUtilsMessageEXT"   );
		}
	}
}

} // namespace Vulkan
