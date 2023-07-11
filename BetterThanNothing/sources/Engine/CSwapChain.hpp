#pragma once

#include "CWindow.hpp"
#include "CDevice.hpp"
#include "CCommandPool.hpp"

namespace BetterThanNothing
{
	constexpr const int MAX_FRAMES_IN_FLIGHT = 2;

	class CPipeline;

	class CSwapChain
	{
	private:
		CWindow*						m_pWindow;
		CDevice*						m_pDevice;
		CCommandPool*					m_pCommandPool;

		VkSwapchainKHR					m_SwapChain;
		VkRenderPass					m_RenderPass;
		VkFormat						m_Format;
		VkExtent2D						m_Extent;

		std::vector<VkImage>			m_Images;
		std::vector<VkImageView>		m_ImageViews;
		std::vector<VkFramebuffer>		m_Framebuffers;
		std::vector<VkCommandBuffer>	m_CommandBuffers;

		VkBuffer						m_VertexBuffer;
		VkDeviceMemory					m_VertexBufferMemory;
		VkBuffer						m_IndexBuffer;
		VkDeviceMemory					m_IndexBufferMemory;

		std::vector<VkSemaphore>		m_ImageAvailableSemaphores;
		std::vector<VkSemaphore>		m_RenderFinishedSemaphores;
		std::vector<VkFence>			m_InFlightFences;

		uint32_t						m_CurrentFrame = 0;

	public:
										CSwapChain(CWindow* pWindow, CDevice* pDevice, CCommandPool* pCommandPool);
										~CSwapChain();

										CSwapChain(const CSwapChain&) = delete;
		CSwapChain&						operator=(const CSwapChain&) = delete;
										CSwapChain(CSwapChain&&) = delete;
		CSwapChain&						operator=(CSwapChain&&) = delete;

	private:
		void							CreateSwapChain();
		void							CreateImageViews();
		void							CreateRenderPass();
		void							CreateVertexBuffer();
		void							CreateIndexBuffer();
		void							CreateCommandBuffers();
		void							CreateSyncObjects();
		void							CreateFramebuffers();

		void							CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void							CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		void							CleanupSwapChain();
		void							RecreateSwapChain();
		void							RecordCommandBuffer(CPipeline* pPipeline, VkCommandBuffer commandBuffer, uint32_t imageIndex);
	public:
		void							DrawFrame(CPipeline* pPipeline);

	private:
		VkSurfaceFormatKHR				ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR				ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D						ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	public:
		VkSwapchainKHR&					GetVkSwapChain()		{ return m_SwapChain; }
		VkRenderPass&					GetVkRenderPass()		{ return m_RenderPass; }
		VkFormat&						GetVkFormat()			{ return m_Format; }
		VkExtent2D&						GetVkExtent()			{ return m_Extent; }
		std::vector<VkImage>&			GetImages()				{ return m_Images; }
		std::vector<VkImageView>&		GetImageViews()			{ return m_ImageViews; }
		std::vector<VkFramebuffer>&		GetFramebuffers()		{ return m_Framebuffers; }
		std::vector<VkCommandBuffer>&	GetVkCommandBuffer()	{ return m_CommandBuffers; }
	};
};
