#pragma once

#include <vector>
#include <Junia/ECS/Component.hpp>

namespace Junia
{
	class Entity
	{
	public:
	private:
		std::vector<Component*> components;
		size_t componentCount;
		std::vector<Entity*> children;
	};
}
