#pragma once

#include <cstdint>
#include <memory>
#include "IdPool.hpp"
#include "../Util/Concepts.hpp"

namespace Junia {

class Scene {
protected:
	explicit Scene();

public:
	virtual ~Scene() = 0;

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
