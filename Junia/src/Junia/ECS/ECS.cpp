#include "../Core/Core.hpp"
#include <Junia/ECS/ECS.hpp>

namespace Junia
{
	namespace ECS
	{
		std::unordered_map<std::type_index, std::shared_ptr<ComponentContainer>> componentStores{ };
		std::unordered_map<std::type_index, std::shared_ptr<System>> systems{ };
		IdPool<EntityType> entityIdPool{ };
	}
}
