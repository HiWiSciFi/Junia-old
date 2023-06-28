#include <Junia/ECS/Systems/RendererSystem.hpp>

#include <Junia/ECS/Components/Transform.hpp>
#include <Junia/ECS/Components/MeshRenderer.hpp>
#include <Junia/Core/Window.hpp>
#include "../../../Platform/Vulkan/VulkanRenderPackage.hpp"

namespace Junia {

void RendererSystem::Init() {
	RequireComponent<Transform>();
	RequireComponent<MeshRenderer>();
}

void RendererSystem::Update(float delta) {
	std::shared_ptr<Surface> surface = Window::Get(1)->GetSurface();
	surface->BeginDraw();
	for (auto const& e : entities) {
		Transform& transform = e.GetComponent<Transform>();
		MeshRenderer& meshRenderer = e.GetComponent<MeshRenderer>();
		if (meshRenderer.package == nullptr)
			meshRenderer.package = std::make_shared<Vulkan::VulkanRenderPackage>(meshRenderer.mesh, meshRenderer.material);
		surface->Draw(meshRenderer.package);
	}
	surface->EndDraw();
}

} // namespace Junia
