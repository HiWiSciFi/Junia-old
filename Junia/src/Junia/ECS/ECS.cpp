#include <Junia/ECS/ECS.hpp>

#include <Junia/Core/IdPool.hpp>
#include "ComponentStore.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace Junia {

static IdPool<ECS::EntityIdType>& GetEntityIdPool() {
	static IdPool<ECS::EntityIdType> pool = IdPool<ECS::EntityIdType>();
	return pool;
}

static std::unordered_map<std::type_index, System*>& GetSystems() {
	static std::unordered_map<std::type_index, System*> systems{ };
	return systems;
}

namespace ECS {

// -----------------------------------------------------------------------------
// --------------------------------- Functions ---------------------------------
// -----------------------------------------------------------------------------

size_t GetComponentOffset(std::type_index type, EntityIdType entity) {
	return ComponentStore::Get(type)->GetComponentOffset(entity);
}

void* GetComponentByOffset(std::type_index type, size_t offset) {
	return ComponentStore::Get(type)->GetComponentByOffset(offset);
}

void RegisterComponent(std::type_index type, size_t size, size_t preallocCount, DestructorFunc destructor, CopyConstructorFunc copyConstructor) {
	ComponentStore::Create(type, size, preallocCount, std::move(destructor), std::move(copyConstructor));
}

void UnregisterComponent(std::type_index type) {
	ComponentStore::Destroy(type);
}

void* AddComponent(std::type_index type, EntityIdType entity) {
	return ComponentStore::Get(type)->AllocateComponent(entity);
}

void* GetComponent(std::type_index type, EntityIdType entity) {
	return ComponentStore::Get(type)->GetComponent(entity);
}

void RemoveComponent(std::type_index type, EntityIdType entity) {
	return ComponentStore::Get(type)->RemoveComponent(entity);
}

void RegisterSystem(std::type_index type, System* system) {
	GetSystems().insert({ type, system });
}

void UpdateSystems(float delta) {
	for (const auto& sp : GetSystems()) {
		sp.second->Update(delta);
	}
}

void UnregisterSystem(std::type_index type) {
	System* system = GetSystems().at(type);
	delete system;
	GetSystems().erase(type);
}

} // namespace ECS

// -----------------------------------------------------------------------------
// ---------------------------------- Classes ----------------------------------
// -----------------------------------------------------------------------------

// ----------------------------------- Entity ----------------------------------

Entity Entity::Create() {
	return Entity(GetEntityIdPool().Next());
}

Entity Entity::Get(ECS::EntityIdType id) {
	return Entity(id);
}

void Entity::Destroy(Entity entity) {
	ComponentStore::RemoveAllComponents(entity.id);
	GetEntityIdPool().Free(entity.id);
}

void Entity::DestroyAll() {
	IdPool<ECS::EntityIdType>& idPool = GetEntityIdPool();
	std::vector<ECS::EntityIdType>& freeIds = idPool.GetFreeIds().GetContainer();
	do {
		ECS::EntityIdType id = idPool.GetCurrent() - idPool.GetStep();
		if (std::find(freeIds.begin(), freeIds.end(), id) != std::end(freeIds)) continue;
		Destroy(Entity(id));
	} while(idPool.GetCurrent() != idPool.GetStart());
}

Entity::Entity() = default;

Entity::Entity(ECS::EntityIdType id) : id(id) { }

// ------------------------------------ hash -----------------------------------

} // namespace Junia

size_t std::hash<Junia::Entity>::operator()(const Junia::Entity& entity) const {
	return hash<Junia::ECS::EntityIdType>()(entity.GetId());
}

namespace Junia {

// --------------------------------- Component ---------------------------------

Component::Component() = default;

Component::Component(const Component& other) = default;

Component::Component(Component&& other) noexcept : entity(other.entity) { }

Component::~Component() = default;

Component& Component::operator=(const Component& other) {
	if (&other != this) entity = other.entity;
	return *this;
}

Component& Component::operator=(Component&& other) noexcept {
	if (&other != this) entity = other.entity;
	return *this;
}

Entity Component::GetEntity() {
	return entity;
}

void Component::SetEntity(ECS::EntityIdType id) {
	entity = Entity::Get(id);
}

// ----------------------------------- System ----------------------------------

System::System() = default;

System::~System() = default;

const std::unordered_set<Entity> System::GetEntities() const {
	return entities;
}

const std::unordered_set<std::type_index>& System::GetRequirements() const {
	return requirements;
}

void System::UnregisterAll() {
	for (const auto& sp : GetSystems()) {
		ECS::UnregisterSystem(sp.first);
	}
}

} // namespace Junia
