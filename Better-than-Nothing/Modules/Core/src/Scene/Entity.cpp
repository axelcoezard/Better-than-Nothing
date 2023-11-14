#include "Scene/Entity.hpp"

namespace BetterThanNothing
{
	Entity::Entity()
	{
		m_Position = {0.0f, 0.0f, 0.0f};
		m_Rotation = {0.0f, 0.0f, 0.0f};
		m_Scale	   = 1.0f;
	}

	Entity::~Entity()
	{
	}

	glm::mat4 Entity::GetModelMatrix()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(m_Scale));
		model = glm::translate(model, m_Position);
		model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		return model;
	}
};
