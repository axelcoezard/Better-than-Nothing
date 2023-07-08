#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <optional>

#include "Engine/CWindow.hpp"

namespace BetterThanNothing
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t>			m_GraphicsFamily;
		std::optional<uint32_t>			m_PresentationFamily;

		bool IsComplete() {
			return m_GraphicsFamily.has_value() && m_PresentationFamily.has_value();
		}
	};

	class CDevice {
	private:
		GLFWwindow*						m_pWindow;

		VkInstance						m_Instance;
		VkDebugUtilsMessengerEXT		m_DebugMessenger;
		VkSurfaceKHR					m_Surface;
		VkPhysicalDevice				m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice						m_Device;
		VkQueue							m_GraphicsQueue;
		VkQueue							m_PresentationQueue;

		const bool						m_EnableValidationLayers = true;
		const std::vector<const char*>	m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

	public:
										CDevice(GLFWwindow* pWindow);
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
		bool							IsDeviceSuitable(VkPhysicalDevice device);

		QueueFamilyIndices				FindQueueFamilies(VkPhysicalDevice device);

	private:
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
