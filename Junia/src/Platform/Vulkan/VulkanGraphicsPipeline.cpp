#include "VulkanGraphicsPipeline.hpp"
#include "VulkanDevice.hpp"
#include "VulkanShader.hpp"
#include <array>
#include <vector>
#include <Junia/Core/FileSystem.hpp>

namespace Vulkan {

extern VulkanDevice* vkDevice;

VulkanGraphicsPipeline::VulkanGraphicsPipeline(VkRenderPass renderPass, std::shared_ptr<Junia::Material> material) : material(material) {
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
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{ };
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 0;
	vertexInputInfo.vertexAttributeDescriptionCount = 0;

	// stage: input assembler
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{ };
	inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

	// stage: vertex shader
	std::shared_ptr<VulkanShader> vertexShader = std::dynamic_pointer_cast<VulkanShader>(material->GetVertexShader());
	if (vertexShader == nullptr) throw std::runtime_error("invalid vertex shader");

	// TODO: stage: tessellation shader

	// TODO: stage: geometry shader

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
	std::shared_ptr<VulkanShader> fragmentShader = std::dynamic_pointer_cast<VulkanShader>(material->GetFragmentShader());
	if (fragmentShader == nullptr) throw std::runtime_error("invalid fragment shader");

	// stage: color blending
	VkPipelineColorBlendAttachmentState colorBlendAttachment{ };
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	VkPipelineColorBlendStateCreateInfo colorBlendingInfo{ };
	colorBlendingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendingInfo.logicOpEnable = VK_FALSE;
	colorBlendingInfo.attachmentCount = 1;
	colorBlendingInfo.pAttachments = &colorBlendAttachment;

	// pipeline layout
	VkPipelineLayoutCreateInfo pipelineLayoutInfo{ };
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = 0;
	pipelineLayoutInfo.pSetLayouts = nullptr;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;
	if (vkCreatePipelineLayout(vkDevice->GetLogical(), &pipelineLayoutInfo, nullptr, &layout) != VK_SUCCESS)
		throw std::runtime_error("failed to create pipeline layout");

	// graphics pipeline
	VkGraphicsPipelineCreateInfo pipelineInfo{ };
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages{ vertexShader->GetStageCreateInfo(), fragmentShader->GetStageCreateInfo() };
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
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;
	if (vkCreateGraphicsPipelines(vkDevice->GetLogical(), nullptr, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS)
		throw std::runtime_error("failed to create graphics pipeline");
}

VulkanGraphicsPipeline::~VulkanGraphicsPipeline() {
	vkDestroyPipelineLayout(vkDevice->GetLogical(), layout, nullptr);
	vkDestroyPipeline(vkDevice->GetLogical(), graphicsPipeline, nullptr);
}

void VulkanGraphicsPipeline::Bind(VkCommandBuffer buffer) {
	vkCmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
}

} // namespace Vulkan
