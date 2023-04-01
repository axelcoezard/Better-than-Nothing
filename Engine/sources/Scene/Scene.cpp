#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"
#include "Core/UUID.hpp"

Entity Scene::CreateEntity(void) {
	Entity entity = Entity(m_Registry.create(), UUID::RandomUUID(), this);
	// TODO: Add basic components to entity
	// - UUID Component
	// - Transformation component
	m_Entities[entity.GetUUID()] = entity.GetHandle();
	return entity;
}

bool Scene::RemoveEntity(const UUID& uuid) {
	auto search = m_Entities.find(uuid);
	if (search != m_Entities.end()) {
		m_Registry.destroy(search->second);
		m_Entities.erase(search);
		return true;
	}
	return false;
}
