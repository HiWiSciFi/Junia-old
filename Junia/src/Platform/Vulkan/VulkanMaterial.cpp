#include "VulkanMaterial.hpp"
#include "VulkanDevice.hpp"
#include "VulkanRenderPass.hpp"
#include "VulkanShader.hpp"
#include <JMath/Vector3.hpp>

namespace Vulkan {

extern VulkanDevice* vkDevice;

void VulkanMaterial::CreatePipeline() {
	VulkanRenderPass compatibilityRenderPass(JMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

	// dynamic state
	std::vector<VkDynamicState> dynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
	VkPipelineDynamicStateCreateInfo dynamicStateInfo{ };
	dynamicStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicStateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicStateInfo.pDynamicStates = dynamicStates.data();
	VkPipelineViewportStateCreateInfo viewportStateInfo{ };
	viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportStateInfo.viewportCount = 1;
	viewportStateInfo.scissorCount = 1;

	// stage: vertex / index buffer
	VkVertexInputBindingDescription vertexBindingDescription{ };
	vertexBindingDescription.binding = 0;
	vertexBindingDescription.stride = sizeof(JMath::Vec3f);
	vertexBindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	VkVertexInputAttributeDescription vertexAttributeDescription{ };
	vertexAttributeDescription.binding = 0;
	vertexAttributeDescription.location = 0;
	vertexAttributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	vertexAttributeDescription.offset = 0;
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{ };
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.pVertexBindingDescriptions = &vertexBindingDescription;
	vertexInputInfo.vertexAttributeDescriptionCount = 1;
	vertexInputInfo.pVertexAttributeDescriptions = &vertexAttributeDescription;

	// stage: input assembler
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{ };
	inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

	std::vector<VkPipelineShaderStageCreateInfo> shaderStages{ };
	shaderStages.reserve(5);

	// stage: vertex shader
	shaderStages.push_back(vertexShader->GetStageCreateInfo());

	// TODO: stage: tessellation control shader
	if (tessellationControlShader != nullptr) shaderStages.push_back(tessellationControlShader->GetStageCreateInfo());

	// TODO: stage: tessellation evaluation shader
	if (tessellationEvaluationShader != nullptr) shaderStages.push_back(tessellationEvaluationShader->GetStageCreateInfo());

	// TODO: stage: geometry shader
	if (geometryShader != nullptr) shaderStages.push_back(geometryShader->GetStageCreateInfo());

	// stage: rasterization
	VkPipelineRasterizationStateCreateInfo rasterizerInfo{ };
	rasterizerInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizerInfo.depthClampEnable = VK_FALSE;
	rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizerInfo.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizerInfo.lineWidth = 1.0f;
	rasterizerInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizerInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizerInfo.depthBiasEnable = VK_FALSE;

	// multisampling
	VkPipelineMultisampleStateCreateInfo multisamplingInfo{ };
	multisamplingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisamplingInfo.sampleShadingEnable = VK_FALSE;
	multisamplingInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	// stage: fragment shader
	shaderStages.push_back(fragmentShader->GetStageCreateInfo());

	// stage: color blending
	VkPipelineColorBlendAttachmentState colorBlendAttachment{ };
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	VkPipelineColorBlendStateCreateInfo colorBlendingInfo{ };
	colorBlendingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendingInfo.logicOpEnable = VK_FALSE;
	colorBlendingInfo.attachmentCount = 1;
	colorBlendingInfo.pAttachments = &colorBlendAttachment;

	// descriptor set layout
	// TODO: move
	VkDescriptorSetLayoutBinding uboLayoutBinding{ };
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorSetLayoutCreateInfo descriptorCreateInfo{ };
	descriptorCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorCreateInfo.bindingCount = 1;
	descriptorCreateInfo.pBindings = &uboLayoutBinding;
	if (vkCreateDescriptorSetLayout(vkDevice->GetLogical(), &descriptorCreateInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
		throw std::runtime_error("failed to create descriptor set layout");

	// pipeline layout
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{ };
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 1;
	pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;
	if (vkCreatePipelineLayout(vkDevice->GetLogical(), &pipelineLayoutInfo, nullptr, &layout) != VK_SUCCESS)
		throw std::runtime_error("failed to create pipeline layout");

	// graphics pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo{ };
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = shaderStages.size();
	pipelineInfo.pStages = shaderStages.data();
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssemblyInfo;
	pipelineInfo.pViewportState = &viewportStateInfo;
	pipelineInfo.pRasterizationState = &rasterizerInfo;
	pipelineInfo.pMultisampleState = &multisamplingInfo;
	pipelineInfo.pDepthStencilState = nullptr;
	pipelineInfo.pColorBlendState = &colorBlendingInfo;
	pipelineInfo.pDynamicState = &dynamicStateInfo;
	pipelineInfo.layout = layout;
	pipelineInfo.renderPass = compatibilityRenderPass.Get();
	pipelineInfo.subpass = 0;
	if (vkCreateGraphicsPipelines(vkDevice->GetLogical(), nullptr, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS)
		throw std::runtime_error("failed to create graphics pipeline");

	vkDestroyDescriptorSetLayout(vkDevice->GetLogical(), descriptorSetLayout, nullptr);
}

void VulkanMaterial::CleanupPipeline() {
	vkDestroyPipelineLayout(vkDevice->GetLogical(), layout, nullptr);
	vkDestroyPipeline(vkDevice->GetLogical(), pipeline, nullptr);
}

#include <iostream>

VulkanMaterial::VulkanMaterial(std::shared_ptr<Junia::Shader> vertexShader, std::shared_ptr<Junia::Shader> fragmentShader) {
	if (vertexShader->GetType() != Junia::Shader::Type::VERTEX)
		throw std::runtime_error("shader has to be a vertex shader");
	this->vertexShader = std::dynamic_pointer_cast<VulkanShader>(vertexShader);
	if (this->vertexShader == nullptr) throw std::runtime_error("cannot use non vulkan shader in vulkan material");

	if (fragmentShader->GetType() != Junia::Shader::Type::FRAGMENT)
		throw std::runtime_error("shader has to be a fragment shader");
	this->fragmentShader = std::dynamic_pointer_cast<VulkanShader>(fragmentShader);
	if (this->fragmentShader == nullptr) throw std::runtime_error("cannot use non vulkan shader in vulkan material");

	CreatePipeline();
}

VulkanMaterial::~VulkanMaterial() {
	CleanupPipeline();
}

void VulkanMaterial::SetVertexShader(std::shared_ptr<Junia::Shader> shader) {
	if (shader->GetType() != Junia::Shader::Type::VERTEX)
		throw std::runtime_error("shader has to be a vertex shader");
	std::shared_ptr<VulkanShader> newShader = std::dynamic_pointer_cast<VulkanShader>(shader);
	if (newShader == nullptr) throw std::runtime_error("cannot use non vulkan shader in vulkan material");
	if (newShader == vertexShader) return;
	vertexShader = newShader;
	CleanupPipeline();
	CreatePipeline();
}

void VulkanMaterial::SetFragmentShader(std::shared_ptr<Junia::Shader> shader) {
	if (shader->GetType() != Junia::Shader::Type::FRAGMENT)
		throw std::runtime_error("shader has to be a fragment shader");
	std::shared_ptr<VulkanShader> newShader = std::dynamic_pointer_cast<VulkanShader>(shader);
	if (newShader == nullptr) throw std::runtime_error("cannot use non vulkan shader in vulkan material");
	if (newShader == fragmentShader) return;
	fragmentShader = newShader;
	CleanupPipeline();
	CreatePipeline();
}

void VulkanMaterial::SetTessellationControlShader(std::shared_ptr<Junia::Shader> shader) {
	if (shader->GetType() != Junia::Shader::Type::TESSELATION_CONTROL)
		throw std::runtime_error("shader has to be a tessellation control shader");
	std::shared_ptr<VulkanShader> newShader = std::dynamic_pointer_cast<VulkanShader>(shader);
	if (newShader == nullptr) throw std::runtime_error("cannot use non vulkan shader in vulkan material");
	if (newShader == tessellationControlShader) return;
	tessellationControlShader = newShader;
	CleanupPipeline();
	CreatePipeline();
}

void VulkanMaterial::SetTessellationEvaluationShader(std::shared_ptr<Junia::Shader> shader) {
	if (shader->GetType() != Junia::Shader::Type::TESSELATION_EVALUATION)
		throw std::runtime_error("shader has to be a tessellation evaluation shader");
	std::shared_ptr<VulkanShader> newShader = std::dynamic_pointer_cast<VulkanShader>(shader);
	if (newShader == nullptr) throw std::runtime_error("cannot use non vulkan shader in vulkan material");
	if (newShader == tessellationEvaluationShader) return;
	tessellationEvaluationShader = newShader;
	CleanupPipeline();
	CreatePipeline();
}

void VulkanMaterial::SetGeometryShader(std::shared_ptr<Junia::Shader> shader) {
	if (shader->GetType() != Junia::Shader::Type::GEOMETRY)
		throw std::runtime_error("shader has to be a geometry shader");
	std::shared_ptr<VulkanShader> newShader = std::dynamic_pointer_cast<VulkanShader>(shader);
	if (newShader == nullptr) throw std::runtime_error("cannot use non vulkan shader in vulkan material");
	if (newShader == geometryShader) return;
	geometryShader = newShader;
	CleanupPipeline();
	CreatePipeline();
}

std::shared_ptr<Junia::Shader> VulkanMaterial::GetVertexShader() const {
	return vertexShader;
}

std::shared_ptr<Junia::Shader> VulkanMaterial::GetFragmentShader() const {
	return fragmentShader;
}

std::shared_ptr<Junia::Shader> VulkanMaterial::GetTessellationControlShader() const {
	return tessellationControlShader;
}

std::shared_ptr<Junia::Shader> VulkanMaterial::GetTessellationEvaluationShader() const {
	return tessellationEvaluationShader;
}

std::shared_ptr<Junia::Shader> VulkanMaterial::GetGeometryShader() const {
	return geometryShader;
}

void VulkanMaterial::BindPipeline(VkCommandBuffer buffer) {
	vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

} // namespace Vulkan
