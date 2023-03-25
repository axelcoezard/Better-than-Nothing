/*
 * File: Entity.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 5:05:13 pm
 * Last Modified: Saturday, 25th March 2023 5:05:14 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "entt.hpp"

#include "Core/UUID.h"


class Entity {
private:
	entt::entity	m_EntityHandle{ entt::null };
	UUID			m_UUID;
public:
	Entity(void);
};
