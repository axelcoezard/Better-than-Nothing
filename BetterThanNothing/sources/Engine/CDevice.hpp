#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "Engine/CWindow.hpp"

namespace BetterThanNothing {

	class CDevice {
	private:
		VkInstance						m_Instance;
		VkDebugUtilsMessengerEXT		m_DebugMessenger;

		const bool						m_EnableValidationLayers = true;
		const std::vector<const char*>	m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	public:
										CDevice();
										~CDevice();

										CDevice(const CDevice&) = delete;
		CDevice&						operator=(const CDevice&) = delete;
										CDevice(CDevice&&) = delete;
		CDevice&						operator=(CDevice&&) = delete;

	private:
		void							CreateInstance();
		void							SetupDebugMessenger();
		void							CreateSurface();
		void							PickPhysicalDevice();
		void							CreateLogicalDevice();

		bool 							CheckValidationLayerSupport();
		std::vector<const char*>		GetRequiredExtensions();

		VkResult						CreateDebugUtilsMessengerEXT(VkInstance instance, \
																	 const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, \
																	 const VkAllocationCallbacks* pAllocator, \
																	 VkDebugUtilsMessengerEXT* pDebugMessenger);
		void							DestroyDebugUtilsMessengerEXT(VkInstance instance, \
																	  VkDebugUtilsMessengerEXT debugMessenger, \
																	  const VkAllocationCallbacks* pAllocator);
		void							PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	};

}
