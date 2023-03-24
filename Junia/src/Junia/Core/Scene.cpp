#include <Junia/Core/Scene.hpp>
#include <vector>
#include <cstdint>

namespace Junia
{
	Scene::~Scene()
	{ }

	std::shared_ptr<Scene> Scene::Load(IdType sceneId)
	{
		return std::make_shared<Scene>();
	}
}
