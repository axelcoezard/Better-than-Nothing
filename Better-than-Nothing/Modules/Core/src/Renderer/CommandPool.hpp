#pragma once

#include "Renderer/Device.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief A wrapper class for VkCommandPool
	 */
	class CommandPool
	{
	private:
		/**
		 * @brief The device that owns this command pool
		 */
		Device* m_Device;

		/**
		 * @brief The VkCommandPool
		 */
		VkCommandPool m_CommandPool;

	public:
		/**
		 * @brief Construct a new Command Pool object
		 * @param device The device that owns this command pool
		 */
		CommandPool(Device* device);

		/**
		 * @brief Destroy the Command Pool object
		 */
		~CommandPool();

		CommandPool(const CommandPool&) = delete;
		CommandPool& operator=(const CommandPool&) = delete;
		CommandPool(CommandPool&&) = delete;
		CommandPool& operator=(CommandPool&&) = delete;

		/**
		 * @brief Get the VkCommandPool object
		 * @return VkCommandPool& The VkCommandPool object
		 */
		VkCommandPool& GetVkCommandPool() { return m_CommandPool; }
	};
};
