#include "VulkanShader.hpp"

#include "VulkanDevice.hpp"

namespace Vulkan {

extern VulkanDevice* vkDevice;

VulkanShader::VulkanShader(const std::vector<uint8_t>& code, Junia::Shader::Type type) : Junia::Shader(type) {
	if (code.size() % 4 != 0) throw std::runtime_error("invalid SPIR-V code");
	VkShaderModuleCreateInfo createInfo{ };
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
	if (vkCreateShaderModule(vkDevice->GetLogical(), &createInfo, nullptr, &shader) != VK_SUCCESS)
		throw std::runtime_error("failed to create shader module");
}

VulkanShader::~VulkanShader() {
	vkDestroyShaderModule(vkDevice->GetLogical(), shader, nullptr);
}

VkPipelineShaderStageCreateInfo VulkanShader::GetStageCreateInfo() const {
	VkPipelineShaderStageCreateInfo shaderStageCreateInfo{ };
	shaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageCreateInfo.module = shader;
	shaderStageCreateInfo.pName = "main";
	switch (GetType()) {
	case Type::VERTEX:                 shaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;                  break;
	case Type::FRAGMENT:               shaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;                break;
	case Type::TESSELATION_CONTROL:    shaderStageCreateInfo.stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;    break;
	case Type::TESSELATION_EVALUATION: shaderStageCreateInfo.stage = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT; break;
	case Type::GEOMETRY:               shaderStageCreateInfo.stage = VK_SHADER_STAGE_GEOMETRY_BIT;                break;
	//case Type::COMPUTE:                shaderStageCreateInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;                 break;
	}
	return shaderStageCreateInfo;
}

} // namespace Vulkan
