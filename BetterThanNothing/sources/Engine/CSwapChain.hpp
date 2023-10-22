#pragma once

namespace BetterThanNothing
{
	class CWindow;
	class CDevice;
	class CDescriptorPool;
	class CCommandPool;
	class CPipeline;
	class CTexture;
	class CVertex;
	class CModel;
	class CScene;

	class CSwapChain
	{
	private:
		CWindow*									m_pWindow;
		CDevice*									m_pDevice;
		CCommandPool*								m_pCommandPool;

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

		uint32_t									m_CurrentFrame = 0;
		uint32_t									m_CurrentImageIndex = 0;
		CDescriptorPool*							m_pDescriptorPool = nullptr;
	public:
													CSwapChain(CWindow* pWindow, CDevice* pDevice, CCommandPool* pCommandPool);
													~CSwapChain();

													CSwapChain(const CSwapChain&) = delete;
		CSwapChain&									operator=(const CSwapChain&) = delete;
													CSwapChain(CSwapChain&&) = delete;
		CSwapChain&									operator=(CSwapChain&&) = delete;

	private:
		void										CreateSwapChain();
		void										CreateImageViews();
		void										CreateRenderPass();

		void										CreateColorResources();
		void										CreateDepthResources();

		void										CreateSyncObjects();
		void										CreateFramebuffers();

	public:
		VkImageView									CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
		void										CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		VkCommandBuffer								BeginSingleTimeCommands();
		void										EndSingleTimeCommands(VkCommandBuffer& commandBuffer);
		void										CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		void										CleanupSwapChain();
		void										RecreateSwapChain();

		VkFormat									FindDepthFormat();
		bool										HasStencilComponent(VkFormat format);

		void										CreateUniformBuffers(CScene* pScene);
		void										CreateCommandBuffers();

		void										BindDescriptorPool(CDescriptorPool* pDescriptorPool);
		void										BeginRecordCommandBuffer(CPipeline* pPipeline, CScene* pScene);
		void										BindModel(CModel* pModel);
		void										UpdateUniformBuffer(CScene* pScene, CModel* pModel, int modelIndex);
		void										DrawModel(CPipeline* pPipeline, CModel* pModel, int modelIndex);
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

	};
};
