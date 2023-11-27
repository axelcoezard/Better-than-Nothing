#pragma once

namespace BetterThanNoting
{
	using Entity = entt::entity;
	using Registry = entt::registry;

	/**
	 * @brief The Entity Component System (ECS) class.
	 * @note It is a wrapper around the EnTT library.
	 */
	class ECSManager
	{
	private:
		/**
		 * @brief The ECS registry.
		 * @note It is a typedef foe the EnTT registry.
		 */
		Registry m_Registry;

	public:
		/**
		 * @brief Creates a new entity.
		 * @return The new entity.
		 */
		Entity CreateEntity()
		{
			return m_Registry.create();
		}

		/**
		 * @brief Destroys an entity.
		 * @param entity The entity to destroy.
		 */
		void DestroyEntity(Entity entity)
		{
			m_Registry.destroy(entity);
		}

		/**
		 * @brief Adds a component to an entity.
		 * @tparam T The component type.
		 * @param entity The entity to add the component to.
		 */
		template<typename T>
		void AddComponent(Entity entity)
		{
			m_Registry.emplace<T>(entity);
		}

		/**
		 * @brief Removes a component from an entity.
		 * @tparam T The component type.
		 * @param entity The entity to remove the component from.
		 */
		template<typename T>
		void RemoveComponent(Entity entity)
		{
			m_Registry.remove<T>(entity);
		}

		/**
		 * @brief Gets a component from an entity.
		 * @tparam T The component type.
		 * @param entity The entity to get the component from.
		 * @return The component.
		 */
		template<typename T>
		T& GetComponent(Entity entity)
		{
			return m_Registry.get<T>(entity);
		}

		/**
		 * @brief Check if an entity has a component.
		 * @tparam T The component type.
		 * @param entity The entity to check.
		 * @return True if the entity has the component, false otherwise.
		 */
		template<typename T>
		bool HasComponent(Entity entity)
		{
			return m_Registry.has<T>(entity);
		}

		/**
		 * @brief Gets a view of entities with the specified components.
		 * @tparam ComponentTypes The component types.
		 * @return The view.
		 */
		template <typename... ComponentTypes>
		auto View()
		{
			return m_Registry.view<ComponentTypes...>();
		}
	};
};
