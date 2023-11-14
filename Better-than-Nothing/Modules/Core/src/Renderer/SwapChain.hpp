#pragma once

namespace BetterThanNothing
{
	class Window;
	class Device;
	class DescriptorPool;
	class CommandPool;
	class Pipeline;
	class Texture;
	class Vertex;
	class Model;
	class Scene;
	struct DrawPacket;
	struct GlobalUniforms;

	class SwapChain
	{
	private:
		Window*										m_pWindow;
		Device*										m_pDevice;
		CommandPool*								m_pCommandPool;

		VkSwapchainKHR								m_SwapChain;
		VkRenderPass								m_RenderPass;
		VkFormat									m_Format;
		VkExtent2D									m_Extent;

		std::vector<VkImage>						m_Images;
		std::vector<VkImageView>					m_ImageViews;
		std::vector<VkFramebuffer>					m_Framebuffers;
		std::vector<VkCommandBuffer>				m_CommandBuffers;

		VkImage										m_DepthImage;
		VkDeviceMemory								m_DepthImageMemory;
		VkImageView									m_DepthImageView;

		VkImage										m_ColorImage;
		VkDeviceMemory								m_ColorImageMemory;
		VkImageView									m_ColorImageView;

		std::vector<std::vector<VkBuffer>>			m_UniformBuffers;
		std::vector<std::vector<VkDeviceMemory>>	m_UniformBuffersMemory;
		std::vector<std::vector<void*>>				m_UniformBuffersMapped;

		std::vector<VkSemaphore>					m_ImageAvailableSemaphores;
		std::vector<VkSemaphore>					m_RenderFinishedSemaphores;
		std::vector<VkFence>						m_InFlightFences;

		u32											m_CurrentFrame = 0;
		u32											m_CurrentImageIndex = 0;
		DescriptorPool*								m_pDescriptorPool = nullptr;

	public:
													SwapChain(Window* pWindow, Device* pDevice, CommandPool* pCommandPool);
													~SwapChain();

													SwapChain(const SwapChain&) = delete;
		SwapChain&									operator=(const SwapChain&) = delete;
													SwapChain(SwapChain&&) = delete;
		SwapChain&									operator=(SwapChain&&) = delete;

	private:
		void										CreateSwapChain();
		void										CreateImageViews();
		void										CreateRenderPass();

		void										CreateColorResources();
		void										CreateDepthResources();

		void										CreateSyncObjects();
		void										CreateFramebuffers();

	public:
		VkImageView									CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, u32 mipLevels);
		void										CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		VkCommandBuffer								BeginSingleTimeCommands();
		void										EndSingleTimeCommands(VkCommandBuffer& commandBuffer);
		void										CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		void										CleanupSwapChain();
		void										RecreateSwapChain();

		VkFormat									FindDepthFormat();
		bool										HasStencilComponent(VkFormat format);

		void										CreateUniformBuffers(Scene* pScene);
		void										DestroyUniformBuffers();

		void										CreateCommandBuffers();

		void										BindDescriptorPool(DescriptorPool* pDescriptorPool);
		bool										BeginRecordCommandBuffer();

		void										BindPipeline(Pipeline* pPipeline);
		void										Draw(GlobalUniforms* globalUniforms, DrawPacket* pDrawPacket, u32 index);

		void										EndRecordCommandBuffer();

	private:
		void										ResetCommandBuffer();
		VkResult									AcquireNextImage();
		void										WaitForFences();
		void										ResetFences();
		void										NextFrame();

	private:
		VkSurfaceFormatKHR							ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR							ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D									ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	public:
		VkSwapchainKHR&								GetVkSwapChain()				{ return m_SwapChain; }
		VkRenderPass&								GetVkRenderPass()				{ return m_RenderPass; }
		VkFormat&									GetVkFormat()					{ return m_Format; }
		VkExtent2D&									GetVkExtent()					{ return m_Extent; }
		std::vector<VkImage>&						GetImages()						{ return m_Images; }
		std::vector<VkImageView>&					GetImageViews()					{ return m_ImageViews; }
		std::vector<VkFramebuffer>&					GetFramebuffers()				{ return m_Framebuffers; }
		std::vector<VkCommandBuffer>&				GetVkCommandBuffer()			{ return m_CommandBuffers; }
		std::vector<std::vector<VkBuffer>>&			GetUniformBuffers()				{ return m_UniformBuffers; }
		std::vector<std::vector<VkDeviceMemory>>&	GetUniformBuffersMemory()		{ return m_UniformBuffersMemory; }
		std::vector<std::vector<void*>>& 			GetUniformBuffersMapped()		{ return m_UniformBuffersMapped; }
		VkCommandBuffer&							GetCurrentCommandBuffer()		{ return m_CommandBuffers[m_CurrentFrame]; }
	};
};
