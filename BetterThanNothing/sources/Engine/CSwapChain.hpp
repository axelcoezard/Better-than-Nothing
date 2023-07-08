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
	class CSwapChain
	{
	private:
		std::shared_ptr<CWindow>		m_pWindow;
		std::shared_ptr<CDevice>		m_pDevice;

		VkSwapchainKHR					m_SwapChain;
		VkFormat						m_Format;
		VkExtent2D						m_Extent;

		std::vector<VkImage>			m_Images;
		std::vector<VkImageView>		m_ImageViews;

	public:
										CSwapChain(std::shared_ptr<CWindow>& pWindow, std::shared_ptr<CDevice>& pDevice);
										~CSwapChain();

										CSwapChain(const CSwapChain&) = delete;
		CSwapChain&						operator=(const CSwapChain&) = delete;
										CSwapChain(CSwapChain&&) = delete;
		CSwapChain&						operator=(CSwapChain&&) = delete;

	private:
		void							CreateSwapChain();
		void							CreateImageViews();

		VkSurfaceFormatKHR				ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR				ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D						ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	};
};
