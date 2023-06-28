#include <Junia/ECS/ECS.hpp>

namespace Junia::ECS {

namespace Internal {
std::unordered_map<std::type_index, std::shared_ptr<ComponentContainer>> componentStores{ };
std::unordered_map<std::type_index, std::shared_ptr<System>> systems{ };
IdPool<EntityType> entityIdPool{ };
} // namespace Internal

Entity Entity::Create() {
	Entity e(Internal::entityIdPool.Next());
	for (auto const& spair : Internal::systems) {
		std::shared_ptr<System> system = spair.second;
		if (system->GetRequirements().size() > 0) continue;
		system->entities.insert(e);
	}
	return e;
}

void Entity::Destroy(Entity e) {
	Internal::entityIdPool.Free(e);
	for (auto const& cspair : Internal::componentStores) cspair.second->Erase(e);
	for (auto const& spair : Internal::systems) spair.second->entities.erase(e);
}

void Entity::DestroyAll() {
	auto& freeIds = Internal::entityIdPool.GetFreeIds().GetContainer();
	do {
		EntityType id = Internal::entityIdPool.GetCurrent() - Internal::entityIdPool.GetStep();
		if (std::find(freeIds.begin(), freeIds.end(), id) != std::end(freeIds)) continue;
		Destroy(Entity(id));
	} while (Internal::entityIdPool.GetCurrent() != Internal::entityIdPool.GetStart());
}

} // namespace Junia::ECS
