#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief The Buffer struct is a wrapper for a VkBuffer and its VkDeviceMemory
	 */
	struct Buffer
	{
		/**
		 * @brief The buffer
		 */
		VkBuffer m_Buffer;

		/**
		 * @brief The buffer memory
		 */
		VkDeviceMemory m_Memory;

		/**
		 * @brief The mapped memory
		 */
		void* m_Mapped;

		/**
		 * @brief The size of the buffer
		 */
		VkDeviceSize m_Size;

		/**
		 * @brief The usage of the buffer
		 */
		VkBufferUsageFlags m_Usage;
	};
};
