/*
 * File: Scene,h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 5:07:56 pm
 * Last Modified: Saturday, 25th March 2023 5:07:58 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <map>

#include "entt/entt.hpp"

#include "Core/UUID.h"

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

#include "Scene/Entity.h"
