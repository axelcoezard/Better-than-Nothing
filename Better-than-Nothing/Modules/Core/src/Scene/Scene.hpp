#pragma once

namespace BetterThanNothing
{
	class Entity;
	class Camera;
	class Event;

	class ModelPool;
	class TexturePool;

	class Scene
	{
	private:
		u32						m_Id;
		std::string				m_Name;

		ModelPool*				m_ModelPool;
		TexturePool*			m_TexturePool;

		Camera*					m_Camera;

		std::vector<Entity*>	m_Entities;
		std::queue<Entity*>		m_PendingEntities;
	public:
								Scene(u32 id, std::string_view name, ModelPool* modelPool, TexturePool* texturePool);
								~Scene();

								Scene(const Scene&) = delete;
		Scene&					operator=(const Scene&) = delete;
								Scene(Scene&&) = delete;
		Scene&					operator=(Scene&&) = delete;

	public:
		Camera*					InitCamera(f64 x, f64 y, f64 z, f64 yaw, f64 pitch);
		Entity*					CreateEntity(const std::string& modelPath, const std::string& texturePath);

		void					OnUpdate(f32 deltatime);
		void					OnEvent(Event* pEvent);

	public:
		u32						GetId()		{ return m_Id; }
		std::string&			GetName()	{ return m_Name; }
		Camera*					GetCamera()	{ return m_Camera; }
		std::vector<Entity*>&	GetEntities()	{ return m_Entities; }

		bool					HasPendingEntities() { return m_PendingEntities.size() > 0; }
		Entity*					NextPendingEntity()
		{
			auto entity = m_PendingEntities.front();
			m_PendingEntities.pop();
			m_Entities.push_back(entity);
			return entity;
		}
	};
};
