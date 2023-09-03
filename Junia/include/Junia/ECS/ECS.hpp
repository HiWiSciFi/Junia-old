#pragma once

#include <cstdint>    // uint8_t, uint32_t
#include <functional> // std::function<T>
#include <map>        // std::map<T, U>
#include <memory>     // std::construct_at<T>, std::destroy_at<T>
#include <set>        // std::set<T>
#include <typeindex>  // std::type_index
#include <typeinfo>   // typeid(T)
#include <vector>     // std::vector<T>

#include "../Core/IdPool.hpp"   // Junia::IdPool<T>
#include "../Util/Concepts.hpp" // Junia::TypenameDerivedFrom<T>

namespace Junia {

class ECS;
class Entity;
class Component;
template<TypenameDerivedFrom<Component> T> struct ComponentRef;
class ComponentStore;
class System;

// -----------------------------------------------------------------------------
// ---------------------------------- Classes ----------------------------------
// -----------------------------------------------------------------------------

// ----------------------------------- Entity ----------------------------------
class Entity final {
friend ECS;
public:
	using IdType = uint32_t;

	Entity();
	Entity(IdType id, ECS* ecs);
	IdType GetId() const;

	Entity(const Entity&);
	Entity& operator=(const Entity&);

	bool operator==(const Entity&) const;
	bool operator!=(const Entity&) const;
	bool operator<(const Entity&) const;
	bool operator>(const Entity&) const;
	bool operator<=(const Entity&) const;
	bool operator>=(const Entity&) const;

	template<TypenameDerivedFrom<Component> T, typename... TArgs> inline ComponentRef<T> AddComponent(TArgs... args);
	template<TypenameDerivedFrom<Component> T> inline bool HasComponent();
	template<TypenameDerivedFrom<Component> T> inline ComponentRef<T> GetComponent();
	template<TypenameDerivedFrom<Component> T> inline void RemoveComponent();

private:
	IdType id;
	ECS* ecs;
};

// --------------------------------- Component ---------------------------------
class Component {
friend ECS;
public:
	virtual ~Component() = 0;

	Entity GetEntity() const;

private:
	Entity entity;
};

// -------------------------------- ComponentRef -------------------------------
template<TypenameDerivedFrom<Component> T>
struct ComponentRef final {
public:
	inline ComponentRef(const Entity& entity, ComponentStore& store);

	inline T* operator->();
	inline T& operator*();

private:
	Entity::IdType entity;
	ComponentStore& store;
};

// ------------------------------- ComponentStore ------------------------------
class ComponentStore final {
public:
	using MoveFunc = std::function<void(void* from, void* to)>;
	using DestFunc = std::function<void(void* ptr)>;

	ComponentStore(size_t, MoveFunc, DestFunc);
	~ComponentStore();

	ComponentStore(const ComponentStore&);
	ComponentStore(ComponentStore&&) noexcept;
	ComponentStore& operator=(const ComponentStore&);
	ComponentStore& operator=(ComponentStore&&) noexcept;

	void* AllocateComponent(Entity::IdType);
	bool HasComponent(Entity::IdType);
	void* GetComponent(Entity::IdType);
	void RemoveComponent(Entity::IdType);

private:
	std::vector<uint8_t> componentArray;
	std::map<Entity::IdType, size_t> entityToComponentMap;
	std::map<size_t, Entity::IdType> componentToEntityMap;
	size_t elementSize;
	size_t elementCount;
	MoveFunc moveFunc;
	DestFunc destFunc;
};

// ----------------------------------- System ----------------------------------
class System {
friend ECS;
public:
	virtual ~System() = 0;

	virtual void Init();
	virtual void Update(float delta);
	virtual void Terminate();

	const std::set<std::type_index>& GetRequirements();

protected:
	template<TypenameDerivedFrom<Component> T> inline void RequireComponent();
	std::vector<Entity>& GetEntities();

private:
	std::set<std::type_index> requirements;
	std::vector<Entity> entities;
	void RequireComponent(const std::type_index);
};

// ------------------------------------ ECS ------------------------------------
class ECS final {
public:
	ECS();

	Entity CreateEntity();
	std::vector<Entity>& GetEntities();
	void DestroyEntity(const Entity& entity);

	template<TypenameDerivedFrom<Component> T> inline void RegisterComponent();
	template<TypenameDerivedFrom<Component> T> inline void UnregisterComponent();

	template<TypenameDerivedFrom<Component> T, typename... TArgs> inline ComponentRef<T> AddComponent(const Entity& entity, TArgs... args);
	template<TypenameDerivedFrom<Component> T> inline bool HasComponent(const Entity& entity);
	template<TypenameDerivedFrom<Component> T> inline ComponentRef<T> GetComponent(const Entity& entity);
	template<TypenameDerivedFrom<Component> T> inline void RemoveComponent(const Entity& entity);

	template<TypenameDerivedFrom<System> T, typename... TArgs> inline void InitSystem(TArgs... args);
	template<TypenameDerivedFrom<System> T> T& GetSystem();
	void UpdateSystems(float delta);
	template<TypenameDerivedFrom<System> T> inline void TerminateSystem();

private:
	std::vector<Entity> entities;
	std::map<std::type_index, ComponentStore> componentStores;
	std::map<std::type_index, std::unique_ptr<System>> systems;
	IdPool<Entity::IdType> entityIdPool;

	void RegisterComponent(const std::type_index, size_t, ComponentStore::MoveFunc, ComponentStore::DestFunc);
	void UnregisterComponent(const std::type_index);
	void AddComponent(const std::type_index, Entity::IdType, Component*);
	bool HasComponent(const std::type_index, Entity::IdType);
	void RemoveComponent(const std::type_index, Entity::IdType);

	void InitSystem(const std::type_index);
	System& GetSystem(const std::type_index);
	void TerminateSystem(const std::type_index);
};

// -----------------------------------------------------------------------------
// ------------------------------- Implementation ------------------------------
// -----------------------------------------------------------------------------

// ----------------------------------- Entity ----------------------------------

template<TypenameDerivedFrom<Component> T, typename... TArgs>
inline ComponentRef<T> Entity::AddComponent(TArgs... args) {
	return ecs->AddComponent<T>(*this, args...);
}

template<TypenameDerivedFrom<Component> T>
inline bool Entity::HasComponent() {
	return ecs->HasComponent<T>(*this);
}

template<TypenameDerivedFrom<Component> T>
inline ComponentRef<T> Entity::GetComponent() {
	return ecs->GetComponent<T>(*this);
}

template<TypenameDerivedFrom<Component> T>
inline void Entity::RemoveComponent() {
	ecs->RemoveComponent<T>(*this);
}

// -------------------------------- ComponentRef -------------------------------

template<TypenameDerivedFrom<Component> T>
inline ComponentRef<T>::ComponentRef(const Entity& entity, ComponentStore& store)
	: entity(entity.GetId()), store(store) { }

template<TypenameDerivedFrom<Component> T>
inline T* ComponentRef<T>::operator->() {
	return static_cast<T*>(store.GetComponent(entity));
}

template<TypenameDerivedFrom<Component> T>
inline T& ComponentRef<T>::operator*() {
	return *static_cast<T*>(store.GetComponent(entity));
}

// ----------------------------------- System ----------------------------------

template<TypenameDerivedFrom<Component> T>
inline void System::RequireComponent() {
	RequireComponent(typeid(T));
}

// ------------------------------------ ECS ------------------------------------

template<TypenameDerivedFrom<Component> T>
inline void ECS::RegisterComponent() {
	RegisterComponent(typeid(T), sizeof(T),
		[ ] (void* from, void* to) {
			std::construct_at<T>(static_cast<T*>(to), std::move(*static_cast<T*>(from)));
		},
		[ ] (void* ptr) {
			std::destroy_at<T>(static_cast<T*>(ptr));
		}
	);
}

template<TypenameDerivedFrom<Component> T>
inline void ECS::UnregisterComponent() {
	UnregisterComponent(typeid(T));
}

template<TypenameDerivedFrom<Component> T, typename... TArgs>
inline ComponentRef<T> ECS::AddComponent(const Entity& e, TArgs... args) {
	T* component = std::construct_at<T>(static_cast<T*>(componentStores.at(typeid(T)).AllocateComponent(e.GetId())), args...);
	AddComponent(typeid(T), e.GetId(), static_cast<Component*>(component));
	return ComponentRef<T>(e, componentStores.at(typeid(T)));
}

template<TypenameDerivedFrom<Component> T>
inline bool ECS::HasComponent(const Entity& e) {
	return HasComponent(typeid(T), e.GetId());
}

template<TypenameDerivedFrom<Component> T>
inline ComponentRef<T> ECS::GetComponent(const Entity& e) {
	return ComponentRef<T>(e, componentStores.at(typeid(T)));
}

template<TypenameDerivedFrom<Component> T>
inline void ECS::RemoveComponent(const Entity& e) {
	RemoveComponent(typeid(T), e.GetId());
}

template<TypenameDerivedFrom<System> T, typename... TArgs>
inline void ECS::InitSystem(TArgs... args) {
	systems.insert({ typeid(T), std::make_unique<T>(args...) });
	InitSystem(typeid(T));
}

template<TypenameDerivedFrom<System> T>
T& ECS::GetSystem() {
	return static_cast<T&>(GetSystem(typeid(T)));
}

template<TypenameDerivedFrom<System> T>
inline void ECS::TerminateSystem() {
	TerminateSystem(typeid(T));
}

} // namespace Junia
