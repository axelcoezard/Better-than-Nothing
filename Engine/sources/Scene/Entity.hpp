#pragma once

#include "entt/entt.hpp"
#include "Core/UUID.hpp"
#include "Scene/Scene.hpp"

class Scene;

class Entity {
private:
	entt::entity	m_Handle { entt::null };
	UUID			m_UUID;
	Scene*			m_Scene = nullptr;
public:
	Entity(void);
	Entity(entt::entity handle, const UUID& uuid, Scene* scene);

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args) {
		return m_Scene->GetRegistry().emplace<T>(m_Handle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent() {
		return m_Scene->GetRegistry().get<T>(m_Handle);
	}

	entt::entity	GetHandle(void) const;
	UUID			GetUUID(void) const;
};
