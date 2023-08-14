#include "ComponentStore.hpp"

#include <stdexcept>

namespace Junia {

static void DeleteByteArrayCallback(const uint8_t* ptr) {
	delete[] ptr;
}

// -----------------------------------------------------------------------------
// ------------------------------ static functions -----------------------------
// -----------------------------------------------------------------------------

ComponentStore::ComponentStoreMapType& ComponentStore::GetComponentStores() {
	static ComponentStoreMapType componentStores{ };
	return componentStores;
}

void ComponentStore::Create(std::type_index type, size_t size, size_t preallocCount, ECS::DestructorFunc destructor, ECS::CopyConstructorFunc copyConstructor) {
	GetComponentStores()[type] = std::make_shared<ComponentStore>(size, preallocCount, std::move(destructor), std::move(copyConstructor));
}

void ComponentStore::Destroy(std::type_index type) {
	GetComponentStores().erase(type);
}

std::shared_ptr<ComponentStore> ComponentStore::Get(std::type_index type) {
	return GetComponentStores().at(type);
}

void ComponentStore::RemoveAllComponents(ECS::EntityIdType entity) {
	for (auto& componentStorePair : GetComponentStores())
		componentStorePair.second->RemoveComponent(entity);
}

// -----------------------------------------------------------------------------
// ------------------------------ Member functions -----------------------------
// -----------------------------------------------------------------------------

void ComponentStore::ReallocUpsize() {
	capacity *= 2;
	if (capacity == 0) capacity = 2;

	const std::shared_ptr<uint8_t> new_data(new uint8_t[capacity * elementSize], DeleteByteArrayCallback);

	for (ECS::ComponentIdType i = 0; i < count; i++) {
		if (freeComponentIds.contains(i)) continue;
		void* old_comp = data.get() + (i * elementSize);
		copyConstructor(new_data.get() + (i * elementSize), old_comp);
		destructor(old_comp);
	}
	data = new_data;
}

ComponentStore::ComponentStore(size_t size, size_t preallocCount, ECS::DestructorFunc destructor, ECS::CopyConstructorFunc copyConstructor)
	: elementSize(size), destructor(std::move(destructor)), copyConstructor(std::move(copyConstructor)),
	capacity(preallocCount == 0 ? 1 : preallocCount), data(new uint8_t[capacity * elementSize], DeleteByteArrayCallback) { }


ComponentStore::ComponentStore(const ComponentStore& other)
	: entityToComponentMap(other.entityToComponentMap), freeComponentIds(other.freeComponentIds),
	elementSize(other.elementSize), destructor(other.destructor), copyConstructor(other.copyConstructor), count(other.count),
	capacity(other.capacity), data(new uint8_t[capacity * elementSize], DeleteByteArrayCallback) {
	for (ECS::ComponentIdType i = 0; i < count; i++) {
		if (freeComponentIds.contains(i)) continue;
		copyConstructor(data.get() + (i * elementSize), other.data.get() + (i * elementSize));
	}
}

ComponentStore::ComponentStore(ComponentStore&& other) noexcept
	: entityToComponentMap(std::move(other.entityToComponentMap)), freeComponentIds(std::move(other.freeComponentIds)),
	elementSize(other.elementSize), destructor(std::move(other.destructor)), copyConstructor(std::move(other.copyConstructor)),
	count(other.count), capacity(other.capacity), data(std::move(other.data)) {
	other.capacity = 0;
	other.count = 0;
	other.data = nullptr;
}

ComponentStore::~ComponentStore() {
	for (ECS::ComponentIdType i = 0; i < count; i++) {
		if (freeComponentIds.contains(i)) continue;
		destructor(data.get() + (i * elementSize));
	}
}

ComponentStore& ComponentStore::operator=(const ComponentStore& other) {
	if (&other == this) return *this;
	if (capacity > 0 && data != nullptr) {
		for (ECS::ComponentIdType i = 0; i < count; i++) {
			if (freeComponentIds.contains(i)) continue;
			destructor(data.get() + (i * elementSize));
		}
		entityToComponentMap.clear();
		capacity = 0;
		count = 0;
	}
	entityToComponentMap = other.entityToComponentMap;
	freeComponentIds = other.freeComponentIds;
	elementSize = other.elementSize;
	destructor = other.destructor;
	copyConstructor = other.copyConstructor;
	count = other.count;
	capacity = other.capacity;
	data = std::shared_ptr<uint8_t>(new uint8_t[capacity * elementSize], DeleteByteArrayCallback);
	for (ECS::ComponentIdType i = 0; i < count; i++) {
		if (freeComponentIds.contains(i)) continue;
		copyConstructor(data.get() + (i * elementSize), other.data.get() + (i * elementSize));
	}
	return *this;
}

ComponentStore& ComponentStore::operator=(ComponentStore&& other) noexcept {
	if (capacity > 0 && data != nullptr) {
		for (ECS::ComponentIdType i = 0; i < count; i++) {
			if (freeComponentIds.contains(i)) continue;
			destructor(data.get() + (i * elementSize));
		}
		entityToComponentMap.clear();
		capacity = 0;
		count = 0;
	}
	entityToComponentMap = std::move(other.entityToComponentMap);
	freeComponentIds = std::move(other.freeComponentIds);
	elementSize = other.elementSize;
	destructor = std::move(other.destructor);
	copyConstructor = std::move(other.copyConstructor);
	count = other.count;
	capacity = other.capacity;
	data = std::move(other.data);
	other.capacity = 0;
	other.count = 0;
	other.data = nullptr;
	return *this;
}

void* ComponentStore::AllocateComponent(ECS::EntityIdType entity) {
	if (entityToComponentMap.contains(entity))
		throw std::runtime_error("entity already has component");

	ECS::ComponentIdType newComponentId = count;
	if (!freeComponentIds.empty()) {
		auto iterator = freeComponentIds.begin();
		newComponentId = *iterator;
		freeComponentIds.erase(iterator);
	} else {
		if (capacity < count + 1) ReallocUpsize();
		count++;
	}
	entityToComponentMap[entity] = newComponentId;
	return data.get() + (newComponentId * elementSize);
}

void* ComponentStore::GetComponent(ECS::EntityIdType entity) {
	const ECS::ComponentIdType componentId = entityToComponentMap.at(entity);
	return data.get() + (componentId * elementSize);
}

void ComponentStore::RemoveComponent(ECS::EntityIdType entity) {
	if (!entityToComponentMap.contains(entity)) return;
	const ECS::ComponentIdType componentId = entityToComponentMap.at(entity);
	destructor(data.get() + (componentId * elementSize));
	entityToComponentMap.erase(entity);
	freeComponentIds.insert(componentId);
	if (componentId == count - 1) count--;
}

size_t ComponentStore::GetComponentOffset(ECS::EntityIdType entity) {
	return entityToComponentMap.at(entity) * elementSize;
}

void* ComponentStore::GetComponentByOffset(size_t offset) {
	return data.get() + offset;
}

} // namespace Junia
