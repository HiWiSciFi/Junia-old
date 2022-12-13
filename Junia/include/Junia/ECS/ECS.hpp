#pragma once

#include <Junia/ECS/ComponentContainer.hpp>
#include <Junia/Core/IdPool.hpp>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>

namespace Junia
{
	namespace ECS
	{
		using EntityType = size_t;
		class System;

		extern std::unordered_map<std::type_index, std::shared_ptr<ComponentContainer>> componentStores;
		extern std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
		extern IdPool<EntityType> entityIdPool;

		template<typename T>
		inline std::shared_ptr<ComponentStore<T>> GetComponentStore()
		{
			return std::static_pointer_cast<ComponentStore<T>>(componentStores[typeid(T)]);
		}

		class Entity
		{
		private:
			EntityType id;

		public:
			Entity(EntityType id) : id(id) { }

			EntityType GetId() const { return id; }
			operator EntityType() const { return id; }

			template<typename T>
			inline void AddComponent(T component) const
			{
				for (auto const& spair : systems)
				{
					std::shared_ptr<System> system = spair.second;
					if (system->GetRequirements().find(typeid(T)) != system->GetRequirements().end())
						system->entities.insert(*this);
				}
				GetComponentStore<T>()->Insert(id, component);
			}

			template<typename T>
			inline void AddComponent() const
			{
				AddComponent<T>(T{ });
			}

			template<typename T>
			inline void RemoveComponent() const
			{
				for (auto const& spair : systems) spair.second->entities.erase(*this);
				GetComponentStore<T>()->Erase(id);
			}

			template<typename T>
			inline bool HasComponent() const
			{
				GetComponentStore<T>()->HasStored(id);
			}

			template<typename T>
			T& GetComponent() const
			{
				return GetComponentStore<T>()->Get(id);
			}

			bool operator==(const Entity& other) const { return id == other.id; }
			bool operator>(const Entity& other) const { return id > other.id; }
			bool operator<(const Entity& other) const { return id < other.id; }
			void operator++() { ++id; }
			void operator++(int) { ++id; }
			void operator--() { --id; }
			void operator--(int) { --id; }
		};
	}
}

template<>
struct std::hash<Junia::ECS::Entity>
{
public:
	auto operator()(const Junia::ECS::Entity& entity) const -> size_t
	{
		return hash<Junia::ECS::EntityType>()(entity.GetId());
	}
};

namespace Junia
{
	namespace ECS
	{
		class System
		{
		protected:
			std::unordered_set<std::type_index> requirements{ };

			template<typename T>
			inline void RequireComponent()
			{
				requirements.insert(typeid(T));
			}

		public:
			std::unordered_set<Entity> entities;

			inline const std::unordered_set<std::type_index>& GetRequirements() const
			{
				return requirements;
			}

			virtual void Init() { }
			virtual void Update(float dt) { }
		};

		template<typename T>
		inline void RegisterComponent()
		{
			componentStores.insert({ typeid(T), std::make_shared<ComponentStore<T>>() });
		}

		template<typename T>
		inline std::shared_ptr<System> RegisterSystem()
		{
			std::shared_ptr<System> system = std::make_shared<T>();
			systems.insert({ typeid(T), system });
			system->Init();
			return system;
		}

		inline Entity CreateEntity()
		{
			Entity e(entityIdPool.Next());
			for (auto const& spair : systems)
			{
				std::shared_ptr<System> system = spair.second;
				if (system->GetRequirements().size() > 0) continue;
				system->entities.insert(e);
			}
			return e;
		}

		inline void DestroyEntity(Entity e)
		{
			entityIdPool.Free(e);
			for (auto const& cspair : componentStores) cspair.second->Erase(e);
			for (auto const& spair : systems) spair.second->entities.erase(e);
		}
	}
}
