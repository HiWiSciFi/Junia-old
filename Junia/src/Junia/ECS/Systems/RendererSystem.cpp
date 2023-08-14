#include <Junia/ECS/Systems/RendererSystem.hpp>

#include <Junia/ECS/Components/Transform.hpp>
#include <Junia/ECS/Components/MeshRenderer.hpp>
#include <Junia/Core/Window.hpp>

namespace Junia {

void RendererSystem::Init() {
	RequireComponent<Transform>();
	RequireComponent<MeshRenderer>();
}

void RendererSystem::Update(float delta) {
	std::shared_ptr<Surface> surface = Window::Get(1)->GetSurface();
	surface->BeginDraw();
	for (auto const& e : GetEntities()) {
		MeshRenderer& meshRenderer = e.GetComponent<MeshRenderer>();
		surface->Draw(meshRenderer);
	}
	surface->EndDraw();
}

} // namespace Junia
