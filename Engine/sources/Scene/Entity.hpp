#pragma once

#include "entt/entt.hpp"
#include "Core/UUID.hpp"

class Scene;

class Entity {
private:
	entt::entity	m_Handle { entt::null };
	UUID			m_UUID;
	Scene*			m_Scene;
public:
	Entity(void);
	Entity(entt::entity handle, const UUID& uuid, Scene* scene);

	entt::entity	GetHandle(void) const;
	UUID			GetUUID(void) const;
};
