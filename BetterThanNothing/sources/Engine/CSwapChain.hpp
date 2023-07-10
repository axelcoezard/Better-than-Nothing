#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <limits>
#include <algorithm>

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

		std::vector<VkSemaphore>		m_ImageAvailableSemaphores;
		std::vector<VkSemaphore>		m_RenderFinishedSemaphores;
		std::vector<VkFence>			m_InFlightFences;

		uint32_t						m_CurrentFrame = 0;
		bool							m_FramebufferResized = false;

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
		void							CreateCommandBuffers();
		void							CreateSyncObjects();
		void							CreateFramebuffers();

		void							CleanupSwapChain();
		void							RecreateSwapChain();
		void							RecordCommandBuffer(CPipeline* pPipeline, VkCommandBuffer commandBuffer, uint32_t imageIndex);

		static void						FramebufferResizeCallback(GLFWwindow* window, int width, int height);

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
