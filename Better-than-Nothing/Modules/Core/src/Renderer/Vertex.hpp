#pragma once

namespace BetterThanNothing
{
	struct Vertex
	{
		glm::vec3	m_Position;
		glm::vec3	m_Color;
		glm::vec2	m_TextureCoordinates;

		static VkVertexInputBindingDescription GetBindingDescription()
		{
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, m_Position);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, m_Color);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, m_TextureCoordinates);
			return attributeDescriptions;
		}

		bool operator==(const Vertex& other) const
		{
			return m_Position == other.m_Position && m_Color == other.m_Color && m_TextureCoordinates == other.m_TextureCoordinates;
		}
	};

};


namespace std {
	template<> struct hash<BetterThanNothing::Vertex> {
		size_t operator()(BetterThanNothing::Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.m_Position) ^
					(hash<glm::vec3>()(vertex.m_Color) << 1)) >> 1) ^
					(hash<glm::vec2>()(vertex.m_TextureCoordinates) << 1);
		}
	};
};

