#include <Junia/Renderer/RenderPackage.hpp>
#include "VulkanGraphicsPipeline.hpp"
#include <Junia/Renderer/Mesh.hpp>

namespace Vulkan {

class VulkanRenderPackage : public Junia::RenderPackage {
private:
	VulkanGraphicsPipeline pipeline{ };

public:
	VulkanRenderPackage() = default;
	VulkanRenderPackage(std::shared_ptr<Junia::Mesh> mesh, std::shared_ptr<Junia::Material> material);
	~VulkanRenderPackage() override;

	VulkanGraphicsPipeline& GetPipeline() { return pipeline; }
};

} // namespace Vulkan
