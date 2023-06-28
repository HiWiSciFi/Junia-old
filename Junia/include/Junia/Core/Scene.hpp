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
};

namespace Scenes {

template<TypenameDerivedFrom<Scene> T>
std::shared_ptr<Scene> Load();

void Unload(Scene* scene);

// Implementation

template<TypenameDerivedFrom<Scene> T>
std::shared_ptr<Scene> Load() {
	return std::make_shared<T>();
}

} // namespace Scenes
} // namespace Junia
