#include <Junia/ECS/ECS.hpp>

namespace Junia {

// -----------------------------------------------------------------------------
// ----------------------------------- Entity ----------------------------------
// -----------------------------------------------------------------------------

Entity::Entity()
	: id(0), ecs(nullptr) { }

Entity::Entity(IdType id, ECS* ecs)
	: id(id), ecs(ecs) { }

Entity::IdType Entity::GetId() const {
	return id;
}

Entity::Entity(const Entity& other)
	: id(other.id), ecs(other.ecs) { }

Entity& Entity::operator=(const Entity& other) {
	if (&other != this) {
		ecs = other.ecs;
		id = other.id;
	}
	return *this;
}

bool Entity::operator==(const Entity& other) const {
	return id == other.id && ecs == other.ecs;
}

bool Entity::operator!=(const Entity& other) const {
	return id != other.id || ecs != other.ecs;
}

bool Entity::operator<(const Entity& other) const {
	return id < other.id;
}

bool Entity::operator>(const Entity& other) const {
	return id > other.id;
}

bool Entity::operator<=(const Entity& other) const {
	return id <= other.id;
}

bool Entity::operator>=(const Entity& other) const {
	return id >= other.id;
}

// -----------------------------------------------------------------------------
// --------------------------------- Component ---------------------------------
// -----------------------------------------------------------------------------

Component::~Component() { }

Entity Component::GetEntity() const {
	return entity;
}

// -----------------------------------------------------------------------------
// ------------------------------- ComponentStore ------------------------------
// -----------------------------------------------------------------------------

ComponentStore::ComponentStore(size_t elementSize, MoveFunc moveFunc, DestFunc destFunc)
	: componentArray(elementSize), entityToComponentMap(), componentToEntityMap(),
	elementSize(elementSize), elementCount(0), moveFunc(moveFunc), destFunc(destFunc) { }

ComponentStore::~ComponentStore() {
	for (size_t i = 0; i < elementCount; i++) {
		destFunc(&componentArray[i * elementSize]);
	}
}

ComponentStore::ComponentStore(const ComponentStore& other) {
	*this = other;
}

ComponentStore::ComponentStore(ComponentStore&& other) noexcept {
	*this = std::move(other);
}

ComponentStore& ComponentStore::operator=(const ComponentStore& other) {
	if (&other != this) {
		componentArray = other.componentArray;
		entityToComponentMap = other.entityToComponentMap;
		componentToEntityMap = other.componentToEntityMap;
		elementSize = other.elementSize;
		elementCount = other.elementCount;
		moveFunc = other.moveFunc;
		destFunc = other.destFunc;
	}
	return *this;
}

ComponentStore& ComponentStore::operator=(ComponentStore&& other) noexcept {
	if (&other != this) {
		componentArray = std::move(other.componentArray);
		entityToComponentMap = std::move(other.entityToComponentMap);
		componentToEntityMap = std::move(other.componentToEntityMap);
		elementSize = other.elementSize;
		elementCount = other.elementCount;
		moveFunc = other.moveFunc;
		destFunc = other.destFunc;
	}
	return *this;
}

void* ComponentStore::AllocateComponent(Entity::IdType entity) {
	if ((elementCount + 1) * elementSize > componentArray.size()) {
		std::vector<uint8_t> newComponentArray(componentArray.size() * 2);
		for (size_t i = 0; i < elementCount; i++) {
			size_t offset = i * elementSize;
			moveFunc(&componentArray[offset], &newComponentArray[offset]);
			destFunc(&componentArray[offset]);
		}
		componentArray = std::move(newComponentArray);
	}
	entityToComponentMap.insert({ entity, elementCount * elementSize });
	componentToEntityMap.insert({ elementCount * elementSize, entity });
	void* componentPtr = &componentArray[entityToComponentMap.at(entity)];
	elementCount++;
	return componentPtr;
}

bool ComponentStore::HasComponent(Entity::IdType entity) {
	return entityToComponentMap.contains(entity);
}

void* ComponentStore::GetComponent(Entity::IdType entity) {
	return &componentArray.at(entityToComponentMap.at(entity));
}

void ComponentStore::RemoveComponent(Entity::IdType entity) {
	if (!HasComponent(entity)) throw std::runtime_error("Entity does not have component");
	size_t componentOffset = entityToComponentMap.at(entity);
	size_t lastComponentOffset = (elementCount - 1) * elementSize;
	if (componentOffset != lastComponentOffset) {
		destFunc(&componentArray[componentOffset]);
		moveFunc(&componentArray[lastComponentOffset], &componentArray[componentOffset]);
		Entity::IdType lastEntity = componentToEntityMap.at(lastComponentOffset);
		componentToEntityMap.at(componentOffset) = lastEntity;
		entityToComponentMap.at(lastEntity) = componentOffset;
	}
	entityToComponentMap.erase(entity);
	componentToEntityMap.erase(lastComponentOffset);
	elementCount--;
}

// -----------------------------------------------------------------------------
// ----------------------------------- System ----------------------------------
// -----------------------------------------------------------------------------

System::~System() { }

void System::Init() { }

void System::Update(float delta) { }

void System::Terminate() { }

const std::set<std::type_index>& System::GetRequirements() {
	return requirements;
}

std::vector<Entity>& System::GetEntities() {
	return entities;
}

void System::RequireComponent(const std::type_index type) {
	requirements.insert(type);
}

// -----------------------------------------------------------------------------
// ------------------------------------ ECS ------------------------------------
// -----------------------------------------------------------------------------

ECS::ECS()
	: entities(), componentStores(), systems(), entityIdPool() { }

Entity ECS::CreateEntity() {
	Entity entity(entityIdPool.Next(), this);
	entities.push_back(entity);
	for (auto& sp : systems) {
		if (sp.second->GetRequirements().empty()) sp.second->entities.push_back(entity);
	}
	return entity;
}

std::vector<Entity>& ECS::GetEntities() {
	return entities;
}

void ECS::DestroyEntity(const Entity& entity) {
	for (auto& csp : componentStores) {
		if (csp.second.HasComponent(entity.GetId())) csp.second.RemoveComponent(entity.GetId());
	}
	for (auto& syp : systems) {
		for (size_t i = 0; i < syp.second->entities.size(); i++) {
			if (syp.second->entities[i] == entity) {
				if (i != syp.second->entities.size() - 1) syp.second->entities[i] = syp.second->entities[syp.second->entities.size() - 1];
				syp.second->entities.pop_back();
			}
		}
	}
	entityIdPool.Free(entity.id);
}

void ECS::UpdateSystems(float delta) {
	for (auto& syp : systems) syp.second->Update(delta);
}

void ECS::RegisterComponent(const std::type_index type, size_t size, ComponentStore::MoveFunc move, ComponentStore::DestFunc dest) {
	if (componentStores.contains(type)) throw std::runtime_error("component already registered");
	componentStores.emplace(type, ComponentStore(size, move, dest));
}

void ECS::UnregisterComponent(const std::type_index type) {
	// TODO: Implement
	componentStores.erase(type);
}

void ECS::AddComponent(const std::type_index type, Entity::IdType entity, Component* component) {
	component->entity = Entity(entity, this);
	for (auto& syp : systems) {
		if (!syp.second->GetRequirements().contains(type)) continue;
		bool eligable = true;
		for (auto& c : syp.second->GetRequirements()) {
			if (!HasComponent(c, entity)) {
				eligable = false;
				break;
			}
		}
		if (eligable) syp.second->entities.emplace_back(entity, this);
	}
}

bool ECS::HasComponent(const std::type_index type, Entity::IdType entity) {
	return componentStores.at(type).HasComponent(entity);
}

void ECS::RemoveComponent(const std::type_index type, Entity::IdType entity) {
	componentStores.at(type).RemoveComponent(entity);
	for (auto& syp : systems) {
		if (!syp.second->GetRequirements().contains(type)) continue;
		for (size_t i = 0; i < syp.second->entities.size(); i++) {
			if (syp.second->entities[i].GetId() == entity) {
				if (i != syp.second->entities.size() - 1) {
					syp.second->entities[i] = syp.second->entities.back();
				}
				syp.second->entities.pop_back();
				break;
			}
		}
	}
}

void ECS::InitSystem(const std::type_index type) {
	std::unique_ptr<System>& system = systems.at(type);
	system->Init();
	for (auto& entity : entities) {
		bool eligable = true;
		for (auto& r : system->GetRequirements()) {
			if (!HasComponent(r, entity.GetId())) {
				eligable = false;
				break;
			}
		}
		if (eligable) system->entities.push_back(entity);
	}
}

System& ECS::GetSystem(const std::type_index type) {
	return *systems.at(type);
}

void ECS::TerminateSystem(const std::type_index type) {
	systems.at(type)->Terminate();
	systems.erase(type);
}

} // namespace Junia
