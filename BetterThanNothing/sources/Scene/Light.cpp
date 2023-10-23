#include "Scene/Light.hpp"

namespace BetterThanNothing
{
	Light::Light(glm::vec3 position, glm::vec3 color)
		: m_Position(position), m_Color(color) { }

	glm::vec3 Light::GetPosition() const
	{
		return m_Position;
	}

	glm::vec3 Light::GetColor() const
	{
		return m_Color;
	}
};
