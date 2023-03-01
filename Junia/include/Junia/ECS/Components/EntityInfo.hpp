#pragma once

#include "../ECS.hpp"

#include <string>
#include <vector>

namespace Junia
{
	struct EntityInfo
	{
		std::string name = "";
		ECS::Entity self;
		ECS::Entity parent;
		std::vector<ECS::Entity> children{ };
	};
}
