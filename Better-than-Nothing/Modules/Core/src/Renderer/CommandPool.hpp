#pragma once

#include "Renderer/Device.hpp"

namespace BetterThanNothing
{
	class CommandPool
	{
	private:
		Device*			m_Device;

		VkCommandPool	m_CommandPool;
	public:
						CommandPool(Device* device);
						~CommandPool();

						CommandPool(const CommandPool&) = delete;
		CommandPool&	operator=(const CommandPool&) = delete;
						CommandPool(CommandPool&&) = delete;
		CommandPool&	operator=(CommandPool&&) = delete;

	public:
		VkCommandPool&	GetVkCommandPool()	{ return m_CommandPool; }
	};
};
