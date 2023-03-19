#pragma once

#include <cstdint>

namespace Junia
{
	class Scene
	{
	public:
		using IdType = uint32_t;

	public:
		virtual ~Scene() = 0;
	};

	template<typename T, typename... TArgs>
	Scene::IdType RegisterScene(TArgs... args)
	{
		return 0;
	}
}
