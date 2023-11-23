#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief The Vertex struct that is used to store vertex data
	 */
	struct Vertex
	{
		/**
		 * @brief The position of the vertex
		 */
		glm::vec3 position;

		/**
		 * @brief The normal of the vertex
		 */
		glm::vec3 normal;

		/**
		 * @brief The texture coordinates of the vertex
		 */
		glm::vec2 textureCoordinates;

		/**
		 * @brief Get the binding description of the vertex
		 *
		 * @return VkVertexInputBindingDescription The binding description of the vertex
		 */
		static VkVertexInputBindingDescription GetBindingDescription()
		{
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			return bindingDescription;
		}

		/**
		 * @brief Get the attribute descriptions of the vertex
		 *
		 * @return std::array<VkVertexInputAttributeDescription, 3> The attribute descriptions of the vertex
		 */
		static std::array<VkVertexInputAttributeDescription, 3> GetAttributeDescriptions()
		{
			std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, position);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, normal);

			attributeDescriptions[2].binding = 0;
			attributeDescriptions[2].location = 2;
			attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[2].offset = offsetof(Vertex, textureCoordinates);
			return attributeDescriptions;
		}

		/**
		 * @brief Check if the vertex is equal to another vertex
		 *
		 * @param other The other vertex
		 *
		 * @retval true if the vertex is equal to the other vertex
		 * @retval false otherwise
		 *
		 * @note The vertex is equal to another vertex if the position, normal and texture coordinates are equal
		 */
		bool operator==(const Vertex& other) const
		{
			return position == other.position && normal == other.normal && textureCoordinates == other.textureCoordinates;
		}
	};

};

namespace std {
	template<> struct hash<BetterThanNothing::Vertex> {
		size_t operator()(BetterThanNothing::Vertex const& vertex) const {
			return ((hash<glm::vec3>()(vertex.position) ^
					(hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
					(hash<glm::vec2>()(vertex.textureCoordinates) << 1);
		}
	};
};

