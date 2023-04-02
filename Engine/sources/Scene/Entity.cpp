#include "Scene/Entity.hpp"

Entity::Entity(void) = default;
Entity::Entity(entt::entity handle, const UUID& uuid, Scene* scene)
	: m_Handle(handle), m_UUID(uuid), m_Scene(scene) {}

entt::entity Entity::GetHandle() const {
	return m_Handle;
}

UUID Entity::GetUUID() {
	return m_UUID;
}
