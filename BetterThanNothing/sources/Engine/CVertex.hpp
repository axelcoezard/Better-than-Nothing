#pragma once

namespace BetterThanNothing
{
	struct Vertex
	{
		glm::vec2	m_Position;
		glm::vec3	m_Color;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};

			return bindingDescription;
		}
	};
};
