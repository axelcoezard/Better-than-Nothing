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

	/**
	 * @brief A wrapper class for VkDevice
	 */
	class Device
	{
	private:
		/**
		 * @brief A pointer to the Window
		 */
		Window* m_Window;

		/**
		 * @brief A pointer to the CommandPool
		 */
		CommandPool* m_CommandPool;

		/**
		 * @brief The VkInstance
		 */
		VkInstance m_Instance;

		/**
		 * @brief The VkDebugUtilsMessengerEXT
		 */
		VkDebugUtilsMessengerEXT m_DebugMessenger;

		/**
		 * @brief The VkSurfaceKHR
		 */
		VkSurfaceKHR m_Surface;

		/**
		 * @brief The VkPhysicalDevice
		 */
		VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;

		/**
		 * @brief The VkDevice
		 */
		VkDevice m_Device;

		/**
		 * @brief The Graphics Queue
		 */
		VkQueue m_GraphicsQueue;

		/**
		 * @brief The Prensetation Queue
		 */
		VkQueue m_PresentationQueue;

		/**
		 * @brief whether or not to enable validation layers
		 */
		const bool m_EnableValidationLayers = true;

		/**
		 * @brief The validation layers
		 */
		const std::vector<const char*> m_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

		/**
		 * @brief The device extensions
		 */
		const std::vector<const char*> m_DeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		/**
		 * @brief The maximum number of samples supported for color and depth buffer
		 */
		VkSampleCountFlagBits m_MsaaSamples = VK_SAMPLE_COUNT_8_BIT;

		/**
		 * @brief The GPU vendor name
		 */
		std::string m_VendorName;

		/**
		 * @brief The GPU device name
		 */
		std::string m_DeviceName;

		/**
		 * @brief The GPU API version
		 */
		std::string m_ApiVersion;

	public:
		/**
		 * @brief Construct a new Device object
		 * @param window The window
		 */
		Device(Window* window);

		/**
		 * @brief Destroy the Device object
		 */
		~Device();

		Device(const Device&) = delete;
		Device& operator=(const Device&) = delete;
		Device(Device&&) = delete;
		Device& operator=(Device&&) = delete;

	private:
		/**
		 * @brief Create the VkInstance
		 */
		void CreateInstance();

		/**
		 * @brief Setup the debug messenger
		 */
		void SetupDebugMessenger();

		/**
		 * @brief Create the VkSurfaceKHR
		 */
		void CreateSurface();

		/**
		 * @brief Pick the physical device
		 */
		void PickPhysicalDevice();

		/**
		 * @brief Create the logical device
		 */
		void CreateLogicalDevice();

		/**
		 * @brief CHeck if the validation layers are supported
		 */
		bool CheckValidationLayerSupport();

		/**
		 * @brief Check if the device extensions are supported
		 *
		 * @param device The physical device to check
		 *
		 * @retval true If the device extensions are supported
		 * @retval false If the device extensions are not supported
		 */
		bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

		/**
		 * @brief Get the required extensions
		 *
		 * @return std::vector<const char*> The required extensions
		 */
		std::vector<const char*> GetRequiredExtensions();

		/**
		 * @brief Whether or not the device is suitable
		 */
		bool IsDeviceSuitable(VkPhysicalDevice device);

		/**
		 * @brief Get the Max Usable Sample Count object
		 *
		 * @return VkSampleCountFlagBits The maximum number of samples supported for color and depth buffer
		 */
		VkSampleCountFlagBits GetMaxUsableSampleCount();

		/**
		 * @brief Get the Vendor name by id
		 *
		 * @param vendorId The vendor id
		 * @return std::string The vendor name
		 */
		std::string GetVendorById(u32 vendorId) const;

	public:
		/**
		 * @brief Wait for the device to be idle
		 *
		 * @note This function is blocking
		 * @note It is a wrapper for vkDeviceWaitIdle
		 */
		void WaitIdle() { vkDeviceWaitIdle(m_Device); }

		/**
		 * @brief Find the queue families
		 *
		 * @param device The physical device
		 */
		QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

		/**
		 * @brief Find the swap chain support details
		 *
		 * @param device The physical device
		 */
		SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

		/**
		 * @brief Find the memory type
		 *
		 * @param typeFilter The type filter
		 * @param properties The memory properties flags
		 */
		u32 FindMemoryType(u32 typeFilter, VkMemoryPropertyFlags properties);

		/**
		 * @brief Find the supported format
		 *
		 * @param candidates The format candidates
		 * @param tiling The image tiling
		 * @param features The format features flags
		 */
		VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

		/**
		 * @brief Create a buffer using vkCreateBuffer and vkAllocateMemory
		 *
		 * @param size The buffer size
		 * @param usage The buffer usage flags
		 * @param properties The memory properties flags
		 * @param buffer The destination buffer
		 * @param bufferMemory The destination buffer memory
		 */
		void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

		/**
		 * @brief Copy a buffer to another buffer using vkCmdCopyBuffer
		 *
		 * @param srcBuffer The source buffer
		 * @param dstBuffer The destination buffer
		 * @param size The buffer size
		 */
		void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		/**
		 * @brief Create a VkImageView using vkCreateImageView
		 *
		 * @param image The image
		 * @param format The image format
		 * @param aspectFlags The image aspect flags
		 * @param mipLevels The mip levels
		 */
		VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, u32 mipLevels);

		/**
		 * @brief Create a VkImage and VkMemory using vkCreateImage and vkAllocateMemory
		 *
		 * @param width The image width
		 * @param height The image height
		 * @param mipLevels The mip levels
		 * @param numSamples The number of samples
		 * @param format The image format
		 * @param tiling The image tiling
		 * @param usage The image usage flags
		 * @param properties The memory properties flags
		 * @param image The destination VkImage
		 * @param imageMemory The destination VkMemory
		 */
		void CreateImage(u32 width, u32 height, u32 mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

		/**
		 * @brief Transition the image layout using vkCmdPipelineBarrier
		 *
		 * @param image The image
		 * @param format The image format
		 * @param oldLayout the old image layout
		 * @param newLayout The new image layout
		 * @param mipLevels The mip levels
		 */
		void TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, u32 mipLevels);

		/**
		 * @brief Copy a buffer to an image using vkCmdCopyBufferToImage
		 *
		 * @param buffer The source buffer
		 * @param image The destination image
		 * @param width The image width
		 * @param height The image height
		 */
		void CopyBufferToImage(VkBuffer buffer, VkImage image, u32 width, u32 height);

	private:
		/**
		 * @brief Create the debug messenger using vkCreateDebugUtilsMessengerEXT
		 *
		 * @param instance The VkInstance
		 * @param createInfo The debug messenger create info
		 * @param allocator The allocator
		 * @param debugMessenger The destination debug messenger
		 */
		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, \
											const VkDebugUtilsMessengerCreateInfoEXT* createInfo, \
											const VkAllocationCallbacks* allocator, \
											VkDebugUtilsMessengerEXT* debugMessenger);

		/**
		 * @brief Destroy the debug messenger using vkDestroyDebugUtilsMessengerEXT
		 *
		 * @param instance The VkInstance
		 * @param debugMessenger The debug messenger
		 * @param allocator The allocator
		 */
		void DestroyDebugUtilsMessengerEXT(VkInstance instance, \
											VkDebugUtilsMessengerEXT debugMessenger, \
											const VkAllocationCallbacks* allocator);

		/**
		 * @brief Populate the debug messenger create info using vkPopulateDebugMessengerCreateInfoEXT
		 *
		 * @param createInfo The debug messenger create info
		 */
		void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	public:
		/**
		 * @brief Get the VkInstance
		 * @return VkInstance& The VkInstance
		 */
		VkInstance& GetVkInstance() { return m_Instance; }

		/**
		 * @brief Get the VkDebugUtilsMessengerEXT
		 * @return VkDebugUtilsMessengerEXT& The VkDebugUtilsMessengerEXT
		 */
		VkDebugUtilsMessengerEXT& GetVkDebugMessenger() { return m_DebugMessenger; }

		/**
		 * @brief Get the VkSurfaceKHR
		 * @return VkSurfaceKHR& The VkSurfaceKHR
		 */
		VkSurfaceKHR& GetVkSurface() { return m_Surface; }

		/**
		 * @brief Get the VkPhysicalDevice
		 * @return VkPhysicalDevice& The VkPhysicalDevice
		 */
		VkPhysicalDevice& GetVkPhysicalDevice() { return m_PhysicalDevice; }

		/**
		 * @brief Get the VkDevice
		 * @return VkDevice& The VkDevice
		 */
		VkDevice& GetVkDevice() { return m_Device; }

		/**
		 * @brief Get the GraphicsQueue
		 * @return VkQueue& The GraphicsQueue
		 */
		VkQueue& GetVkGraphicsQueue() { return m_GraphicsQueue; }

		/**
		 * @brief Get the VkPresentationQueue
		 * @return VkQueue& The PresentationQueue
		 */
		VkQueue& GetVkPresentationQueue() { return m_PresentationQueue; }

		/**
		 * @brief Get the Validation Layers vector
		 * @return const std::vector<const char*> The Validation Layers vector
		 */
		const std::vector<const char*> GetValidationLayers() { return m_ValidationLayers; }

		/**
		 * @brief Get the Device Extensions vector
		 * @return const std::vector<const char*> The Device Extensions vector
		 */
		const std::vector<const char*> GetDeviceExtensions() { return m_DeviceExtensions; }

		/**
		 * @brief Get the maximum number of samples supported for color and depth buffer
		 * @return VkSampleCountFlagBits& The maximum number of samples supported for color and depth buffer
		 */
		VkSampleCountFlagBits& GetMsaaSamples() { return m_MsaaSamples; }

		/**
		 * @brief Get the command pool
		 * @return CommandPool* The command pool
		 */
		CommandPool* GetCommandPool() { return m_CommandPool; }

		/**
		 * @brief Get the GPU vendor name
		 * @return std::string& The vendor name
		 */
		std::string& GetVendorName() { return m_VendorName; }

		/**
		 * @brief Get the GPU device name
		 * @return std::string& The device name
		 */
		std::string& GetDeviceName() { return m_DeviceName; }

		/**
		 * @brief Get the GPU API version
		 * @return std::string& The API version
		 */
		std::string& GetApiVersion() { return m_ApiVersion; }
	};
};
