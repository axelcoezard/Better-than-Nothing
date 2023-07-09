#pragma once

#include <stdexcept>
#include <memory>

#include "CDevice.hpp"
#include "CSwapChain.hpp"
#include "CPipeline.hpp"
#include "CCommandPool.hpp"

namespace BetterThanNothing
{
	class CCommandBuffer
	{
	private:
		std::shared_ptr<CDevice>		m_pDevice;
		std::shared_ptr<CSwapChain>		m_pSwapChain;
		std::shared_ptr<CPipeline>		m_pPipeline;
		std::shared_ptr<CCommandPool>	m_pCommandPool;

		VkCommandBuffer					m_CommandBuffer;
	public:
										CCommandBuffer(std::shared_ptr<CDevice>& pDevice, \
													   std::shared_ptr<CSwapChain>& pSwapChain, \
													   std::shared_ptr<CPipeline>& pPipeline, \
													   std::shared_ptr<CCommandPool>& pCommandPool);
										~CCommandBuffer();

										CCommandBuffer(const CCommandBuffer&) = delete;
		CCommandBuffer&					operator=(const CCommandBuffer&) = delete;
										CCommandBuffer(CCommandBuffer&&) = delete;
		CCommandBuffer&					operator=(CCommandBuffer&&) = delete;

	private:
		void							CreateCommandBuffer();
		void							RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

		VkCommandBuffer&				GetVkCommandBuffer()	{ return m_CommandBuffer; }
	};
};
