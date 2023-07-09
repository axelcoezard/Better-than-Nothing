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

namespace BetterThanNothing
{
	class CCommandBuffer;
	class CSwapChain
	{
	private:
		CWindow*						m_pWindow;
		CDevice*						m_pDevice;

		VkSwapchainKHR					m_SwapChain;
		VkFormat						m_Format;
		VkExtent2D						m_Extent;

		std::vector<VkImage>			m_Images;
		std::vector<VkImageView>		m_ImageViews;

		VkSemaphore						m_ImageAvailableSemaphore;
		VkSemaphore						m_RenderFinishedSemaphore;
		VkFence							m_InFlightFence;

	public:
										CSwapChain(CWindow* pWindow, CDevice* pDevice);
										~CSwapChain();

										CSwapChain(const CSwapChain&) = delete;
		CSwapChain&						operator=(const CSwapChain&) = delete;
										CSwapChain(CSwapChain&&) = delete;
		CSwapChain&						operator=(CSwapChain&&) = delete;

	private:
		void							CreateSwapChain();
		void							CreateImageViews();
		void							CreateSyncObjects();

	public:
		void							DrawFrame(CCommandBuffer* commandbuffer);

	private:
		VkSurfaceFormatKHR				ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR				ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D						ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	public:
		VkSwapchainKHR&					GetVkSwapChain()	{ return m_SwapChain; }
		VkFormat&						GetVkFormat()		{ return m_Format; }
		VkExtent2D&						GetVkExtent()		{ return m_Extent; }
		std::vector<VkImage>&			GetImages()			{ return m_Images; }
		std::vector<VkImageView>&		GetImageViews()		{ return m_ImageViews; }
	};
};
