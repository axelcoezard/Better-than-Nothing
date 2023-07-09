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
		CDevice*						m_pDevice;
		CSwapChain*						m_pSwapChain;
		CPipeline*						m_pPipeline;
		CCommandPool*					m_pCommandPool;

		VkCommandBuffer					m_CommandBuffer;
	public:
										CCommandBuffer(CDevice* pDevice, \
													   CSwapChain* pSwapChain, \
													   CPipeline* pPipeline, \
													   CCommandPool* pCommandPool);
										~CCommandBuffer();

										CCommandBuffer(const CCommandBuffer&) = delete;
		CCommandBuffer&					operator=(const CCommandBuffer&) = delete;
										CCommandBuffer(CCommandBuffer&&) = delete;
		CCommandBuffer&					operator=(CCommandBuffer&&) = delete;

	private:
		void							CreateCommandBuffer();

	public:
		void							RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		VkCommandBuffer&				GetVkCommandBuffer()	{ return m_CommandBuffer; }
	};
};
