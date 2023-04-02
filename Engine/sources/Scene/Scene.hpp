#pragma once

#include <map>

#include "entt/entt.hpp"
#include "Core/UUID.hpp"
#include "Scene/Entity.hpp"

class Entity;

class Scene {
private:
	entt::registry					m_Registry;
	std::map<UUID, entt::entity>	m_Entities;

public:
	Entity			CreateEntity();
	bool			RemoveEntity(UUID& uuid);

	template<typename... Components>
	auto			GetAllEntitiesWith() {
		return m_Registry.view<Components...>();
	}

	entt::registry&	GetRegistry();
};
