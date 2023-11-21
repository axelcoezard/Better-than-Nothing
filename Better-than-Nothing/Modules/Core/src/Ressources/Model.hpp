#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief The model struct that contains all the data of a 3D model
	 */
	struct Model
	{
		/**
		 * @brief The file path of the model
		 */
		std::string filePath;

		/**
		 * @brief The vertices buffer of the model
		 */
		VkBuffer vertexBuffer;

		/**
		 * @brief The vertex buffer memory
		 */
		VkDeviceMemory vertexBufferMemory;

		/**
		 * @brief The indices buffer of the model
		 */
		VkBuffer indexBuffer;

		/**
		 * @brief The index buffer memory
		 */
		VkDeviceMemory indexBufferMemory;

		/**
		 * @brief The number of indices
		 */
		u32 indexCount;
	};
};
