#include <Junia/Core/Scene.hpp>

namespace Junia {

Scene::Scene() { }

Scene::~Scene() { }

void Scene::Update(float delta) {
	ecs.UpdateSystems(delta);
}

void Scene::Unload(std::shared_ptr<Scene> scene) { }

} // namespace Junia
