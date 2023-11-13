#pragma once

#include "Renderer/Device.hpp"

namespace BetterThanNothing
{
	class CommandPool
	{
	private:
		Device*		m_pDevice;

		VkCommandPool					m_CommandPool;
	public:
										CommandPool(Device* pDevice);
										~CommandPool();

										CommandPool(const CommandPool&) = delete;
		CommandPool&					operator=(const CommandPool&) = delete;
										CommandPool(CommandPool&&) = delete;
		CommandPool&					operator=(CommandPool&&) = delete;

	private:
		void							CreateCommandPool();

	public:
		VkCommandPool&					GetVkCommandPool()	{ return m_CommandPool; }
	};
};
