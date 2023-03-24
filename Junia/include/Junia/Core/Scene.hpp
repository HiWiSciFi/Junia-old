#pragma once

#include <cstdint>
#include "../Util/Concepts.hpp"

namespace Junia
{
	class Scene
	{
	public:
		using IdType = uint32_t;

	public:
		virtual ~Scene() = 0;

		static std::shared_ptr<Scene> Load(IdType sceneId);
	};

	template<TypenameDerivedFrom<Scene> T, typename... TArgs>
	Scene::IdType RegisterScene(TArgs... args)
	{
		return 0;
	}

	template<TypenameDerivedFrom<Scene> T>
	void UnregisterScene()
	{
		return;
	}
}
