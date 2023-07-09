#pragma once

#include <stdexcept>
#include <memory>

#include "CDevice.hpp"

namespace BetterThanNothing
{
	class CCommandPool
	{
	private:
		std::shared_ptr<CDevice>		m_pDevice;

		VkCommandPool					m_CommandPool;
	public:
										CCommandPool(std::shared_ptr<CDevice>& pDevice);
										~CCommandPool();

										CCommandPool(const CCommandPool&) = delete;
		CCommandPool&					operator=(const CCommandPool&) = delete;
										CCommandPool(CCommandPool&&) = delete;
		CCommandPool&					operator=(CCommandPool&&) = delete;

	private:
		void							CreateCommandPool();

	public:
		VkCommandPool&					GetVkCommandPool()	{ return m_CommandPool; }
	};
};
