#pragma once

namespace BetterThanNothing
{
	class Window;
	class Device;
	class DescriptorPool;
	class CommandBuffer;
	class Pipeline;
	class Texture;
	class Vertex;
	class Entity;
	class Scene;
	struct DrawPacket;

	/**
	 * @brief The swap chain class
	 */
	class SwapChain
	{
	private:
		/**
		 * @brief A pointer to the window
		 */
		Window* m_Window;

		/**
		 * @brief A pointer to the device
		 */
		Device* m_Device;

		/**
		 * @brief A pointer to the descriptor pool
		 */
		DescriptorPool* m_DescriptorPool;

		/**
		 * @brief The swap chain
		 */
		VkSwapchainKHR m_SwapChain;

		/**
		 * @brief The render pass
		 */
		VkRenderPass m_RenderPass;

		/**
		 * @brief The image format
		 */
		VkFormat m_Format;

		/**
		 * @brief The image extent
		 */
		VkExtent2D m_Extent;

		/**
		 * @brief The swap chain images
		 */
		std::vector<VkImage> m_Images;

		/**
		 * @brief The swap chain image views
		 */
		std::vector<VkImageView> m_ImageViews;

		/**
		 * @brief The swap chain framebuffers
		 */
		std::vector<VkFramebuffer> m_Framebuffers;

		/**
		 * @brief The command buffers
		 */
		std::vector<CommandBuffer*> m_CommandBuffers;

		/**
		 * @brief The depth image
		 */
		VkImage m_DepthImage;

		/**
		 * @brief The depth image memory
		 */
		VkDeviceMemory m_DepthImageMemory;

		/**
		 * @brief The depth image view
		 */
		VkImageView m_DepthImageView;

		/**
		 * @brief The color image
		 */
		VkImage m_ColorImage;

		/**
		 * @brief The color image memory
		 */
		VkDeviceMemory m_ColorImageMemory;

		/**
		 * @brief The color image view
		 */
		VkImageView m_ColorImageView;

		/**
		 * @brief The swap chain semaphores that is available for rendering
		 */
		std::vector<VkSemaphore> m_ImageAvailableSemaphores;

		/**
		 * @brief The swap chain semaphores that has finished rendering
		 */
		std::vector<VkSemaphore> m_RenderFinishedSemaphores;

		/**
		 * @brief The swap chain fences
		 */
		std::vector<VkFence> m_InFlightFences;

		/**
		 * @brief The current frame in flight
		 */
		u32 m_CurrentFrame = 0;

		/**
		 * @brief The swap chain images in flight
		 */
		u32 m_CurrentImageIndex = 0;

	public:
		/**
		 * @brief Construct a new Swap Chain object
		 *
		 * @param window
		 * @param device
		 * @param descriptorPool
		 */
 		SwapChain(Window* window, Device* device, DescriptorPool* descriptorPool);

		/**
		 * @brief Destroy the Swap Chain object
		 */
 		~SwapChain();

		SwapChain(const SwapChain&) = delete;
		SwapChain& operator=(const SwapChain&) = delete;
		SwapChain(SwapChain&&) = delete;
		SwapChain& operator=(SwapChain&&) = delete;

	private:
		/**
		 * @brief Create the swap chain
		 */
		void CreateSwapChain();

		/**
		 * @brief Create the image views
		 */
		void CreateImageViews();

		/**
		 * @brief Create the render pass
		 */
		void CreateRenderPass();

		/**
		 * @brief Create the framebuffers
		 */
		void CreateColorResources();

		/**
		 * @brief Create the depth resources
		 */
		void CreateDepthResources();

		/**
		 * @brief Create the semaphores and fences
		 */
		void CreateSyncObjects();

		/**
		 * @brief Create the framebuffers
		 */
		void CreateFramebuffers();

	public:
		/**
		 * @brief Clean the swap chain
		 */
		void CleanupSwapChain();

		/**
		 * @brief Recreate the swap chain
		 */
		void RecreateSwapChain();

		/**
		 * @brief Find the depth format
		 * @return VkFormat the depth format
		 */
		VkFormat FindDepthFormat();

		/**
		 * @brief Check if the format has a stencil component
		 * @param format the format
		 * @return true if the format has a stencil component
		 * @return false if the format does not have a stencil component
		 */
		bool HasStencilComponent(VkFormat format);

		/**
		 * @brief Create the command buffers
		 */
		void CreateCommandBuffers();

		/**
		 * @brief Begin to record the commands in the command buffer
		 */
		bool BeginRecordCommandBuffer();

		/**
		 * @brief Bind the pipeline to use for drawing
		 */
		void BindPipeline(Pipeline* pPipeline);

		/**
		 * @brief Draw using a draw packet
		 */
		void Draw(DrawPacket* drawPacket, u32 index);

		/**
		 * @brief End to record the commands in the command buffer
		 */
		void EndRecordCommandBuffer();

	private:
		/**
		 * @brief Reset the command buffer
		 */
		void ResetCommandBuffer();

		/**
		 * @brief A wrapper function for vkAcquireNextImageKHR
		 */
		VkResult AcquireNextImage();

		/**
		 * @brief A wrapper function for vkWaitForFences
		 */
		void WaitForFences();

		/**
		 * @brief A wrapper function for vkResetFences
		 */
		void ResetFences();

		/**
		 * @brief Increment the current frame index by 1
		 */
		void NextFrame();

	private:
		/**
		 * @brief Choose the swap surface format
		 * @param availableFormats the available formats
		 * @return VkSurfaceFormatKHR the chosen format
		 */
		VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

		/**
		 * @brief Choose the swap present mode
		 * @param availablePresentModes the available present modes
		 * @return VkPresentModeKHR the chosen present mode
		 */
		VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

		/**
		 * @brief Choose the swap extent
		 * @param capabilities the surface capabilities
		 * @return VkExtent2D the chosen extent
		 */
		VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	public:
		/**
		 * @brief Get the VkSwapchainKHR
		 * @return VkSwapchainKHR& the VkSwapchainKHR
		 */
		VkSwapchainKHR& GetVkSwapChain() { return m_SwapChain; }

		/**
		 * @brief Get the VkRenderPass
		 * @return VkRenderPass& the VkRenderPass
		 */
		VkRenderPass& GetVkRenderPass() { return m_RenderPass; }

		/**
		 * @brief Get the VkFormat
		 * @return VkFormat& the VkFormat
		 */
		VkFormat& GetVkFormat() { return m_Format; }

		/**
		 * @brief Get the VkExtent2D
		 * @return VkExtent2D& the VkExtent2D
		 */
		VkExtent2D& GetVkExtent() { return m_Extent; }

		/**
		 * @brief Get all the VkImage
		 * @return std::vector<VkImage>& All the VkImage
		 */
		std::vector<VkImage>& GetImages() { return m_Images; }

		/**
		 * @brief Get all the VkImageView
		 * @return std::vector<VkImageView>& All the VkImageView
		 */
		std::vector<VkImageView>& GetImageViews() { return m_ImageViews; }

		/**
		 * @brief Get all the VkFramebuffer
		 * @return std::vector<VkFramebuffer>& All the VkFramebuffer
		 */
		std::vector<VkFramebuffer>& GetFramebuffers() { return m_Framebuffers; }

		/**
		 * @brief Get the Current Frame index
		 * @return u32& The index of the current frame
		 */
		u32 GetCurrentFrame() { return m_CurrentFrame; }

		/**
		 * @brief Get the pointer to the current Command Buffer using the current frame index
		 * @return CommandBuffer* A pointer to the current command buffer
		 */
		CommandBuffer* GetCurrentCommandBuffer() { return m_CommandBuffers[m_CurrentFrame]; }
	};
};
