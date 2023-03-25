/*
 * File: Scene,h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 25th March 2023 5:07:56 pm
 * Last Modified: Saturday, 25th March 2023 5:07:58 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "entt.hpp"

class Entity;

class Scene {
private:
	entt::registry m_Registry;
public:
	Scene(void) = default;
	~Scene(void) = default;

	Entity CreateEntity(const std::string& name);
	bool RemoveEntity(const std::string& name);

	template<typename... Components>
	auto GetAllEntitiesWith()
	{
		return m_Registry.view<Components...>();
	}
};
