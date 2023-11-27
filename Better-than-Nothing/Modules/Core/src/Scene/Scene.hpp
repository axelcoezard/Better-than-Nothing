#pragma once

namespace BetterThanNothing
{
	class Camera;
	class Event;

	class ModelPool;
	class TexturePool;

	typedef entt::entity Entity;
	typedef entt::registry Registry;

	class Scene
	{
	private:
		u32 m_Id;
		std::string m_Name;

		ModelPool* m_ModelPool;
		TexturePool* m_TexturePool;

		Camera* m_Camera;

		Registry m_Registry;
		std::queue<Entity> m_PendingEntities;
	public:
 		Scene(u32 id, std::string_view name, ModelPool* modelPool, TexturePool* texturePool);
 		~Scene();

		/**
		 * @brief Initializes the camera.
		 *
		 * @param x The x position of the camera.
		 * @param y The y position of the camera.
		 * @param z The z position of the camera.
		 * @param yaw The yaw of the camera.
		 * @param pitch The pitch of the camera.
		 * @return Camera* A pointer to the camera.
		 */
		Camera* InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch);

		/**
		 * @brief Called when the scene is updated.
		 * @param deltatime The time since the last update.
		 */
		void OnUpdate(f32 deltatime);

		/**
		 * @brief Called when an event is received.
		 * @param pEvent The event.
		 */
		void OnEvent(Event* pEvent);

		/**
		 * @brief Gets the id of the scene.
		 * @return The id of the scene.
		 */
		u32 GetId();

		/**
		 * @brief Gets the name of the scene.
		 * @return The name of the scene.
		 */
		std::string& GetName();

		/**
		 * @brief Gets the camera.
		 * @return The camera.
		 */
		Camera* GetCamera();

		/**
		 * @brief Creates a new entity.
		 * @param modelPath The path to the model.
		 * @param texturePath The path to the texture.
		 * @return The new entity.
		 */
		Entity CreateEntity(const std::string& modelPath, const std::string& texturePath);

		/**
		 * @brief Destroys an entity.
		 * @param entity The entity to destroy.
		 */
		void DestroyEntity(Entity entity);

		/**
		 * @brief Adds a component to an entity.
		 * @tparam T The component type.
		 * @param entity The entity to add the component to.
		 */
		template<typename T>
		void AddComponent(Entity entity, T component)
		{
			m_Registry.emplace<T>(entity, component);
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
			return m_Registry.view<T>().contains(entity);
		}

		/**
		 * @brief Gets a view of entities with the specified components.
		 * @tparam ComponentTypes The component types.
		 * @return The view.
		 */
		template <typename... ComponentTypes>
		auto GetView()
		{
			return m_Registry.view<ComponentTypes...>();
		}

		/**
		 * @brief Gets the number of entities.
		 * @return The number of entities.
		 */
		u32 GetEntitiesCount();

		/**
		 * @brief Checks if there are pending entities to be added to the scene.
		 * @return True if there are pending entities, false otherwise.
		 */
		bool HasPendingEntities();

		/**
		 * @brief Gets the next pending entity and removes it from the queue.
		 * @return The next pending entity.
		 */
		Entity NextPendingEntity();
	};
};
