#pragma once

#include <Junia/Util/Concepts.hpp>

#include <cstdint>
#include <functional>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <unordered_set>

namespace Junia {

// -----------------------------------------------------------------------------
// ---------------------------- forward declarations ---------------------------
// -----------------------------------------------------------------------------

class Entity;
class Component;
class System;

namespace ECS {

// -----------------------------------------------------------------------------
// ----------------------------- Using declarations ----------------------------
// -----------------------------------------------------------------------------

using EntityIdType = uint32_t;
using ComponentIdType = size_t;
using DestructorFunc = std::function<void(void*)>;
using CopyConstructorFunc = std::function<void(void*, void*)>;

// -----------------------------------------------------------------------------
// --------------------------------- Functions ---------------------------------
// -----------------------------------------------------------------------------

size_t GetComponentOffset(std::type_index type, EntityIdType entity);
void* GetComponentByOffset(std::type_index type, size_t offset);

void RegisterComponent(std::type_index type, size_t size, size_t preallocCount, DestructorFunc destructor, CopyConstructorFunc copyConstructor);
void UnregisterComponent(std::type_index type);

void* AddComponent(std::type_index type, EntityIdType entity);
void* GetComponent(std::type_index type, EntityIdType entity);
void RemoveComponent(std::type_index type, EntityIdType entity);

void RegisterSystem(std::type_index type, System* system);
void UpdateSystems(float delta);
void UnregisterSystem(std::type_index type);

void UpdateSystemsEntity(EntityIdType entity);

} // namespace ECS

// -----------------------------------------------------------------------------
// ---------------------------------- Classes ----------------------------------
// -----------------------------------------------------------------------------

// ----------------------------------- Entity ----------------------------------

class Entity {
private:
	ECS::EntityIdType id = 0;
	explicit Entity(ECS::EntityIdType entityId);

public:
	Entity();

	[[nodiscard]] inline ECS::EntityIdType GetId() const { return id; }

	static Entity Create();
	static Entity Get(ECS::EntityIdType id);
	static void Destroy(Entity entity);
	static void DestroyAll();

	template<TypenameDerivedFrom<Component> T, typename... TArgs>
	T& AddComponent(TArgs... args);

	template<TypenameDerivedFrom<Component> T>
	T& GetComponent() const;

	template<TypenameDerivedFrom<Component> T>
	void RemoveComponent();

	operator ECS::EntityIdType() const { return id; }
	bool operator==(const Entity& other) const { return id == other.id; }
	bool operator>(const Entity& other) const { return id > other.id; }
	bool operator<(const Entity& other) const { return id < other.id; }
	void operator++()    { id++; }
	void operator++(int) { id++; }
	void operator--()    { id--; }
	void operator--(int) { id--; }
};

// ------------------------------------ hash -----------------------------------

} // namespace Junia

template<>
struct std::hash<Junia::Entity> {
public:
	size_t operator()(const Junia::Entity& entity) const;
};

namespace Junia {

// --------------------------------- Component ---------------------------------

class Component {
friend Entity;
private:
	Entity entity{ };

	void SetEntity(ECS::EntityIdType id);

public:
	Component();
	Component(const Component& other);
	Component(Component&& other) noexcept;
	virtual ~Component() = 0;

	Component& operator=(const Component& other);
	Component& operator=(Component&& other) noexcept;

	Entity GetEntity();

	template<TypenameDerivedFrom<Component> T>
	static inline void Register(size_t preallocCount = 1);

	template<TypenameDerivedFrom<Component> T>
	static inline void Unregister();
};

// ------------------------------ ComponentRef<T> ------------------------------

template<TypenameDerivedFrom<Component> T>
struct ComponentRef {
private:
	size_t offset;

public:
	ComponentRef();
	explicit ComponentRef(Entity entity);
	explicit ComponentRef(T& component);

	T* operator->();
	T& operator*();
};

// ----------------------------------- System ----------------------------------

class System {
friend Entity;
private:
	std::unordered_set<std::type_index> requirements{ };
	std::unordered_set<Entity> entities{ };

protected:
	template<TypenameDerivedFrom<Component> T>
	inline void RequireComponent();

	const std::unordered_set<Entity> GetEntities() const;

public:
	System();
	virtual ~System() = 0;

	const std::unordered_set<std::type_index>& GetRequirements() const;

	virtual void Init() = 0;
	virtual void Update(float delta) = 0;

	template<TypenameDerivedFrom<System> T, typename... TArgs>
	static inline void Register(TArgs ...args);

	template<TypenameDerivedFrom<System> T>
	static inline void Unregister();

	static void UnregisterAll();
};

// -----------------------------------------------------------------------------
// ------------------------------- Implementation ------------------------------
// -----------------------------------------------------------------------------


// ----------------------------------- Entity ----------------------------------

template<TypenameDerivedFrom<Component> T, typename... TArgs>
inline T& Entity::AddComponent(TArgs ...args) {
	T* componentAddress = static_cast<T*>(ECS::AddComponent(typeid(T), id));
	std::construct_at<T>(componentAddress, args...);
	componentAddress->SetEntity(id);
	ECS::UpdateSystemsEntity(id);
	return *componentAddress;
}

template<TypenameDerivedFrom<Component> T>
inline T& Entity::GetComponent() const {
	return *static_cast<T*>(ECS::GetComponent(typeid(T), id));
}

template<TypenameDerivedFrom<Component> T>
inline void Entity::RemoveComponent() {
	ECS::RemoveComponent(typeid(T), id);
	ECS::UpdateSystemsEntity(id);
}

// --------------------------------- Component ---------------------------------

template<TypenameDerivedFrom<Component> T>
inline void Component::Register(size_t preallocCount) {
	ECS::RegisterComponent(typeid(T), sizeof(T), preallocCount,
		[] (void* ptr) -> void {
			std::destroy_at<T>(static_cast<T*>(ptr));
		},
		[] (void* dest, void* src) -> void {
			std::construct_at<T>(
				static_cast<T*>(dest),
				*static_cast<T*>(src));
		});
}

template<TypenameDerivedFrom<Component> T>
inline void Component::Unregister() {
	ECS::UnregisterComponent(typeid(T));
}

// ------------------------------ ComponentRef<T> ------------------------------

template<TypenameDerivedFrom<Component> T>
inline ComponentRef<T>::ComponentRef()
	: offset(0) { }

template<TypenameDerivedFrom<Component> T>
inline ComponentRef<T>::ComponentRef(Entity entity)
	: offset(ECS::GetComponentOffset(typeid(T), entity.GetId())) { }

template<TypenameDerivedFrom<Component> T>
inline ComponentRef<T>::ComponentRef(T& component)
	: offset(ECS::GetComponentOffset(typeid(T), component.GetEntity().GetId())) { }

template<TypenameDerivedFrom<Component> T>
inline T* ComponentRef<T>::operator->() {
	return static_cast<T*>(ECS::GetComponentByOffset(typeid(T), offset));
}

template<TypenameDerivedFrom<Component> T>
inline T& ComponentRef<T>::operator*() {
	return *static_cast<T*>(ECS::GetComponentByOffset(typeid(T), offset));
}

// ----------------------------------- System ----------------------------------

template<TypenameDerivedFrom<Component> T>
void System::RequireComponent() {
	requirements.insert(typeid(T));
}

template<TypenameDerivedFrom<System> T, typename... TArgs>
inline void System::Register(TArgs ...args) {
	ECS::RegisterSystem(typeid(T), new T(args...));
}

template<TypenameDerivedFrom<System> T>
inline void System::Unregister() {
	ECS::UnregisterSystem(typeid(T));
}

} // namespace Junia
