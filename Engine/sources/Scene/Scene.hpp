#pragma once

#include <map>

#include "entt/entt.hpp"
#include "Core/UUID.hpp"

class Entity;

class Scene {
private:
	entt::registry					m_Registry;
	std::map<UUID, entt::entity>	m_Entities;

public:
	Entity	CreateEntity(void);
	bool	RemoveEntity(const UUID& uuid);

	template<typename... Components>
	auto	GetAllEntitiesWith()
	{
		return m_Registry.view<Components...>();
	}
};
