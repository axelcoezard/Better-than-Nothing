#pragma once

namespace BetterThanNothing
{
	class Light
	{
	private:
		glm::vec3	m_Position;
		glm::vec3	m_Color;

	public:
		Light(glm::vec3 position, glm::vec3 color);
		~Light() = default;

		glm::vec3 GetPosition() const;
		glm::vec3 GetColor() const;
	};
};
