#pragma once

#include <cstdint>
#include <memory>

#include "../Util/Concepts.hpp"
#include "../ECS/ECS.hpp"
#include "IdPool.hpp"

namespace Junia {

class Scene {
protected:
	ECS ecs;
	explicit Scene();

public:
	virtual ~Scene() = 0;

	void Update(float delta);

	template<TypenameDerivedFrom<Scene> T>
	static std::shared_ptr<Scene> Load();

	static void Unload(std::shared_ptr<Scene> scene);
};

// -----------------------------------------------------------------------------
// ------------------------------- Implementation ------------------------------
// -----------------------------------------------------------------------------

template<TypenameDerivedFrom<Scene> T>
std::shared_ptr<Scene> Scene::Load() {
	return std::make_shared<T>();
}

} // namespace Junia
