/*
 * File: Entity.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 10:58:41 pm
 * Last Modified: Saturday, 25th March 2023 10:58:43 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Scene/Entity.h"

Entity::Entity(void) = default;
Entity::Entity(entt::entity handle, const UUID& uuid, Scene* scene)
	: m_Handle(handle), m_UUID(uuid), m_Scene(scene) {}

entt::entity Entity::GetHandle(void) const {
	return m_Handle;
}

UUID Entity::GetUUID(void) const {
	return m_UUID;
}
