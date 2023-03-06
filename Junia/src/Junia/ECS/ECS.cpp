#include <Junia/ECS/ECS.hpp>

namespace Junia
{
	namespace ECS
	{
		namespace Internal
		{
			std::unordered_map<std::type_index, std::shared_ptr<ComponentContainer>> componentStores{ };
			std::unordered_map<std::type_index, std::shared_ptr<System>> systems{ };
			IdPool<EntityType> entityIdPool{ };
		}

		Entity Entity::Create()
		{
			Entity e(Internal::entityIdPool.Next());
			for (auto const& spair : Internal::systems)
			{
				std::shared_ptr<System> system = spair.second;
				if (system->GetRequirements().size() > 0) continue;
				system->entities.insert(e);
			}
			return e;
		}

		void Entity::Destroy(Entity e)
		{
			Internal::entityIdPool.Free(e);
			for (auto const& cspair : Internal::componentStores) cspair.second->Erase(e);
			for (auto const& spair : Internal::systems) spair.second->entities.erase(e);
		}
	}
}
