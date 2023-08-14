#pragma once

#include <Junia/ECS/ECS.hpp>

#include <cstdint>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

namespace Junia {

class ComponentStore {
private:
	using ComponentStoreMapType = std::unordered_map<std::type_index, std::shared_ptr<ComponentStore>>;

	static ComponentStoreMapType& GetComponentStores();

	std::unordered_map<ECS::EntityIdType, ECS::ComponentIdType> entityToComponentMap{ };
	std::unordered_set<ECS::ComponentIdType> freeComponentIds{ };
	size_t elementSize = 0;
	ECS::DestructorFunc destructor;
	ECS::CopyConstructorFunc copyConstructor;
	size_t count = 0;
	size_t capacity = 0;
	std::shared_ptr<uint8_t> data = nullptr;

	void ReallocUpsize();

public:
	static void Create(std::type_index type, size_t size, size_t preallocCount, ECS::DestructorFunc destructor, ECS::CopyConstructorFunc copyConstructor);
	static void Destroy(std::type_index type);
	static std::shared_ptr<ComponentStore> Get(std::type_index type);
	static void RemoveAllComponents(ECS::EntityIdType entity);

	ComponentStore(size_t size, size_t preallocCount, ECS::DestructorFunc destructor, ECS::CopyConstructorFunc copyConstructor);
	ComponentStore(const ComponentStore& other);
	ComponentStore(ComponentStore&& other) noexcept;
	~ComponentStore();

	ComponentStore& operator=(const ComponentStore& other);
	ComponentStore& operator=(ComponentStore&& other) noexcept;

	void* AllocateComponent(ECS::EntityIdType entity);
	void* GetComponent(ECS::EntityIdType entity);
	void RemoveComponent(ECS::EntityIdType entity);

	size_t GetComponentOffset(ECS::EntityIdType entity);
	void* GetComponentByOffset(size_t offset);
};

} // namespace Junia
