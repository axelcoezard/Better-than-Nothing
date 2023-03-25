/*
 * File: Entity.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 5:05:13 pm
 * Last Modified: Saturday, 25th March 2023 5:05:14 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "entt/entt.hpp"

#include "Core/UUID.h"

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

#include "Scene/Scene.h"
