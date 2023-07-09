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

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR		m_Capabilities;
		std::vector<VkSurfaceFormatKHR>	m_Formats;
		std::vector<VkPresentModeKHR>	m_PresentationModes;
	};

	class CDevice
	{
	private:
		CWindow*						m_pWindow;

		VkInstance						m_Instance;
		VkDebugUtilsMessengerEXT		m_DebugMessenger;
		VkSurfaceKHR					m_Surface;
		VkPhysicalDevice				m_PhysicalDevice = VK_NULL_HANDLE;
		VkDevice						m_Device;
		VkQueue							m_GraphicsQueue;
		VkQueue							m_PresentationQueue;

		const bool						m_EnableValidationLayers = true;
		const std::vector<const char*>	m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char*>	m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	public:
										CDevice(CWindow* pWindow);
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
		bool							CheckDeviceExtensionSupport(VkPhysicalDevice device);

		std::vector<const char*>		GetRequiredExtensions();
		bool							IsDeviceSuitable(VkPhysicalDevice device);

	public:
		QueueFamilyIndices				FindQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails			QuerySwapChainSupport(VkPhysicalDevice device);

	private:
		VkResult						CreateDebugUtilsMessengerEXT(VkInstance instance, \
																	 const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, \
																	 const VkAllocationCallbacks* pAllocator, \
																	 VkDebugUtilsMessengerEXT* pDebugMessenger);
		void							DestroyDebugUtilsMessengerEXT(VkInstance instance, \
																	  VkDebugUtilsMessengerEXT debugMessenger, \
																	  const VkAllocationCallbacks* pAllocator);
		void							PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	public:
		VkInstance&						GetVkInstance()				{ return m_Instance; }
		VkDebugUtilsMessengerEXT&		GetVkDebugMessenger()		{ return m_DebugMessenger; }
		VkSurfaceKHR&					GetVkSurface()				{ return m_Surface; }
		VkPhysicalDevice&				GetVkPhysicalDevice()		{ return m_PhysicalDevice; }
		VkDevice&						GetVkDevice()				{ return m_Device; }
		VkQueue&						GetVkGraphicsQueue()		{ return m_GraphicsQueue; }
		VkQueue&						GetVkPresentationQueue()	{ return m_PresentationQueue; }
		const std::vector<const char*>	GetValidationLayers()		{ return m_ValidationLayers; }
		const std::vector<const char*>	GetDeviceExtensions()		{ return m_DeviceExtensions; }
	};
};
