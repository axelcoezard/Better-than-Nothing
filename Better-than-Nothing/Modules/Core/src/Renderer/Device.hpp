#pragma once

namespace BetterThanNothing
{
	struct QueueFamilyIndices
	{
		std::optional<u32>				graphicsFamily;
		std::optional<u32>				presentationFamily;

		bool IsComplete() {
			return graphicsFamily.has_value() && presentationFamily.has_value();
		}
	};

	struct SwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR		capabilities;
		std::vector<VkSurfaceFormatKHR>	formats;
		std::vector<VkPresentModeKHR>	presentationModes;
	};

	class Window;
	class CommandPool;

	class Device
	{
	private:
		Window*							m_Window;
		CommandPool*					m_CommandPool;

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

		VkSampleCountFlagBits			m_MsaaSamples = VK_SAMPLE_COUNT_8_BIT;

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
		std::string						GetVendorById(u32 vendorId) const;

	public:
		void							Idle() { vkDeviceWaitIdle(m_Device); }
		QueueFamilyIndices				FindQueueFamilies(VkPhysicalDevice device);
		SwapChainSupportDetails			QuerySwapChainSupport(VkPhysicalDevice device);
		u32								FindMemoryType(u32 typeFilter, VkMemoryPropertyFlags properties);
		VkFormat						FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

		void							CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void							CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
		VkImageView						CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, u32 mipLevels);

		void							CreateImage(u32 width, u32 height, u32 mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void							TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, u32 mipLevels);
		void							CopyBufferToImage(VkBuffer buffer, VkImage image, u32 width, u32 height);

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

		CommandPool*					GetCommandPool()			{ return m_CommandPool; }

		std::string&					GetVendorName() { return m_VendorName; }
		std::string&					GetDeviceName() { return m_DeviceName; }
		std::string&					GetApiVersion() { return m_ApiVersion; }
	};
};
