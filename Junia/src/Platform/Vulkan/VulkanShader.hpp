#pragma once

#include <Junia/Renderer/Shader.hpp>
#include <vulkan/vulkan.h>
#include <vector>

namespace Vulkan {

class VulkanShader : public Junia::Shader {
private:
	VkShaderModule shader;

public:
	VulkanShader(const std::vector<uint8_t>& code, Junia::Shader::Type type);
	virtual ~VulkanShader() override;

	VkPipelineShaderStageCreateInfo GetStageCreateInfo() const;
};

} // namespace Vulkan
