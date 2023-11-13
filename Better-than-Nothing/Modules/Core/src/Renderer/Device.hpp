#pragma once

#include "Renderer/Window.hpp"

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

	class Device
	{
	private:
		Window*							m_pWindow;

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

		VkSampleCountFlagBits			m_MsaaSamples = VK_SAMPLE_COUNT_1_BIT;

		std::string						m_VendorName;
		std::string						m_DeviceName;
		std::string						m_ApiVersion;

	public:
										Device(Window* pWindow);
										~Device();

										Device(const Device&) = delete;
		Device&							operator=(const Device&) = delete;
										Device(Device&&) = delete;
		Device&							operator=(Device&&) = delete;

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
		VkSampleCountFlagBits			GetMaxUsableSampleCount();
		std::string						GetVendorById(uint32_t vendorId) const;

	public:
		void							Idle() { vkDeviceWaitIdle(m_Device); }
		QueueFamilyIndices				FindQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails			QuerySwapChainSupport(VkPhysicalDevice device);
		uint32_t						FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		VkFormat						FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

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
		VkSampleCountFlagBits&			GetMsaaSamples()			{ return m_MsaaSamples; }

		std::string&					GetVendorName() { return m_VendorName; }
		std::string&					GetDeviceName() { return m_DeviceName; }
		std::string&					GetApiVersion() { return m_ApiVersion; }
	};
};
