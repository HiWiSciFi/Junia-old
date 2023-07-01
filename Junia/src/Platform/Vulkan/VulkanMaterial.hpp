#pragma once

#include <Junia/Renderer/Material.hpp>
#include <vulkan/vulkan.hpp>
#include "VulkanShader.hpp"

namespace Vulkan {

class VulkanMaterial : public Junia::Material {
private:
	VkPipeline pipeline = VK_NULL_HANDLE;
	VkPipelineLayout layout = VK_NULL_HANDLE;

	std::shared_ptr<VulkanShader> vertexShader = nullptr;
	std::shared_ptr<VulkanShader> fragmentShader = nullptr;
	std::shared_ptr<VulkanShader> tessellationControlShader = nullptr;
	std::shared_ptr<VulkanShader> tessellationEvaluationShader = nullptr;
	std::shared_ptr<VulkanShader> geometryShader = nullptr;

	void CreatePipeline();
	void CleanupPipeline();

public:
	VulkanMaterial(std::shared_ptr<Junia::Shader> vertexShader, std::shared_ptr<Junia::Shader> fragmentShader);
	~VulkanMaterial() override;

	inline VkPipeline GetPipeline() const { return pipeline; }

	void SetVertexShader(std::shared_ptr<Junia::Shader> shader) override;
	void SetFragmentShader(std::shared_ptr<Junia::Shader> shader) override;
	void SetTessellationControlShader(std::shared_ptr<Junia::Shader> shader) override;
	void SetTessellationEvaluationShader(std::shared_ptr<Junia::Shader> shader) override;
	void SetGeometryShader(std::shared_ptr<Junia::Shader> shader) override;

	std::shared_ptr<Junia::Shader> GetVertexShader() const override;
	std::shared_ptr<Junia::Shader> GetFragmentShader() const override;
	std::shared_ptr<Junia::Shader> GetTessellationControlShader() const override;
	std::shared_ptr<Junia::Shader> GetTessellationEvaluationShader() const override;
	std::shared_ptr<Junia::Shader> GetGeometryShader() const override;

	void BindPipeline(VkCommandBuffer buffer);
};

} // namespace Vulkan
