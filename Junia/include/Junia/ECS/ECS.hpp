#pragma once

#include "ComponentContainer.hpp"
#include "../Core/IdPool.hpp"
#include "../Util/Concepts.hpp"
#include <functional>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>

namespace Junia
{
	namespace ECS
	{
		class System;

		namespace Internal
		{
			extern std::unordered_map<std::type_index, std::shared_ptr<ComponentContainer>> componentStores;
			extern std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
			extern IdPool<EntityType> entityIdPool;

			/**
			 * @brief Get the ECS::Internal::ComponentStore for a specific
			 *        component
			 * @tparam T the component to get the store for
			 * @return a shared pointer to the ECS::Internal::ComponentStore or
			 *         a nullptr if the component has not been registered
			*/
			template<typename T>
			inline std::shared_ptr<ComponentStore<T>> GetComponentStore()
			{
				try
				{
					return std::static_pointer_cast<ComponentStore<T>>(componentStores[typeid(T)]);
				}
				catch (std::out_of_range)
				{
					return std::shared_ptr<ComponentStore<T>>(nullptr);
				}
			}
		}

		class Entity
		{
		private:
			EntityType id;

		public:
			/**
			 * @brief Create an entity
			 * @return a valid new entity
			*/
			static Entity Create();

			/**
			 * @brief Destroy an entity that has been created using ECS::CreateEntity()
			 * @param e the entity to destroy
			*/
			static void Destroy(Entity e);

			/**
			 * @brief Create an Entity by ID
			 * @param id the id for the entity
			*/
			Entity(EntityType id) : id(id) { }

			/**
			 * @brief Get the entity ID
			 * @return the ID of the entity
			*/
			EntityType GetId() const { return id; }

			/**
			 * @brief Add a component
			 * @tparam T the component type to add
			 * @param component the component to add
			*/
			template<typename T>
			inline void AddComponent(T component) const;

			/**
			 * @brief Add a component
			 * @tparam T the component type to add
			*/
			template<typename T>
			inline void AddComponent() const;

			/**
			 * @brief Remove a component
			 * @tparam T the component type to remove
			*/
			template<typename T>
			inline void RemoveComponent() const;

			/**
			 * @brief Get if the entity has a component
			 * @tparam T the type of component to check for
			 * @return true if it has the component, false otherwise
			*/
			template<typename T>
			inline bool HasComponent() const;

			/**
			 * @brief Get a component. This function will throw an
			 *        std::invalid_argument exception if the entity does not
			 *        have a component of this type
			 * @tparam T the type of the component to get
			 * @return a reference to the component
			*/
			template<typename T>
			T& GetComponent() const;

			operator EntityType() const { return id; }
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

// template specification for Hashing entities
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
		/**
		 * @brief A representation of a System. All Systems should be derived
		 *        publicly from this class
		*/
		class System
		{
		private:
			std::unordered_set<std::type_index> requirements{ };

		protected:
			/**
			 * @brief Register a component requirement for entities that should
			 *        be handled by this system
			 * @tparam T the component type to require
			*/
			template<typename T>
			inline void RequireComponent();

		public:
			/**
			 * @brief A set of entities that are relevant to this system
			*/
			std::unordered_set<Entity> entities;

			/**
			 * @brief Get a set of components that are required for the system
			 *        to apply to an entity
			 * @return a reference to a set containing type indices for each
			 *         component that is required by the system
			*/
			inline const std::unordered_set<std::type_index>& GetRequirements() const;

			/**
			 * @brief Initializes the system (set component requirements here)
			*/
			virtual void Init() { }

			/**
			 * @brief Called each frame (handle entities here)
			 * @param dt the delta time
			*/
			virtual void Update(float dt) { }
		};

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------- Entity ------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

		template<typename T>
		inline void Entity::AddComponent(T component) const
		{
			for (auto const& spair : Internal::systems)
			{
				std::shared_ptr<System> system = spair.second;
				if (system->GetRequirements().find(typeid(T)) != system->GetRequirements().end())
					system->entities.insert(*this);
			}
			Internal::GetComponentStore<T>()->Insert(id, component);
		}

		template<typename T>
		inline void Entity::AddComponent() const
		{
			AddComponent<T>(T{ });
		}

		template<typename T>
		inline void Entity::RemoveComponent() const
		{
			for (auto const& spair : Internal::systems) spair.second->entities.erase(*this);
			Internal::GetComponentStore<T>()->Erase(id);
		}

		template<typename T>
		inline bool Entity::HasComponent() const
		{
			std::shared_ptr<Internal::ComponentStore<T>> store = Internal::GetComponentStore<T>();
			if (store == nullptr) return false;
			return store->HasStored(id);
		}

		template<typename T>
		T& Entity::GetComponent() const
		{
			if (!HasComponent<T>())
				throw std::invalid_argument("There is no component of that type for this entity");
			return Internal::GetComponentStore<T>()->Get(id);
		}

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------- System ------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

		template<typename T>
		inline void System::RequireComponent()
		{
			requirements.insert(typeid(T));
		}

		inline const std::unordered_set<std::type_index>& System::GetRequirements() const
		{
			return requirements;
		}

// ---------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- Global functions -------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

		/**
		 * @brief Register a component type
		 * @tparam T the component type to register
		*/
		template<typename T>
		inline void RegisterComponent()
		{
			Internal::componentStores.insert({ typeid(T), std::make_shared<Internal::ComponentStore<T>>() });
		}

		/**
		 * @brief [WIP:NYI] Unregister a component type
		 * @tparam T the component type to unregister
		*/
		template<typename T>
		inline void UnregisterComponent()
		{
			// TODO: implement
		}

		/**
		 * @brief Register a system
		 * @tparam T the system type to register
		 * @return a pointer containing the system instance used
		*/
		template<TypenameDerivedFrom<System> T>
		inline std::shared_ptr<T> RegisterSystem()
		{
			std::shared_ptr<System> system = std::make_shared<T>();
			Internal::systems.insert({ typeid(T), system });
			system->Init();
			return std::static_pointer_cast<T>(system);
		}

		/**
		 * @brief Unregister a system. If the system hasn't been registered (see
		 *        ECS::RegisterSystem()) this will do nothing
		 * @tparam T the system type to unregister
		*/
		template<TypenameDerivedFrom<System> T>
		inline void UnregisterSystem()
		{
			Internal::systems.erase(typeid(T));
		}
	}
}
