#pragma once

#include <string>
#include <vector>
#include <Junia/ECS/ECS.hpp>

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
