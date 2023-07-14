#pragma once

namespace BetterThanNothing
{
	class CWindow;
	class CDevice;
	class CDescriptorPool;
	class CCommandPool;
	class CPipeline;

	class CSwapChain
	{
	private:
		CWindow*						m_pWindow;
		CDevice*						m_pDevice;
		CCommandPool*					m_pCommandPool;

		VkSwapchainKHR					m_SwapChain;
		VkRenderPass					m_RenderPass;
		VkFormat						m_Format;
		VkExtent2D						m_Extent;

		std::vector<VkImage>			m_Images;
		std::vector<VkImageView>		m_ImageViews;
		std::vector<VkFramebuffer>		m_Framebuffers;
		std::vector<VkCommandBuffer>	m_CommandBuffers;

		VkBuffer						m_VertexBuffer;
		VkDeviceMemory					m_VertexBufferMemory;
		VkBuffer						m_IndexBuffer;
		VkDeviceMemory					m_IndexBufferMemory;
		std::vector<VkBuffer>			m_UniformBuffers;
		std::vector<VkDeviceMemory>		m_UniformBuffersMemory;
		std::vector<void*>				m_UniformBuffersMapped;

		std::vector<VkSemaphore>		m_ImageAvailableSemaphores;
		std::vector<VkSemaphore>		m_RenderFinishedSemaphores;
		std::vector<VkFence>			m_InFlightFences;

		uint32_t						m_CurrentFrame = 0;

	public:
										CSwapChain(CWindow* pWindow, CDevice* pDevice, CCommandPool* pCommandPool);
										~CSwapChain();

										CSwapChain(const CSwapChain&) = delete;
		CSwapChain&						operator=(const CSwapChain&) = delete;
										CSwapChain(CSwapChain&&) = delete;
		CSwapChain&						operator=(CSwapChain&&) = delete;

	private:
		void							CreateSwapChain();
		void							CreateImageViews();
		void							CreateRenderPass();
		void							CreateVertexBuffer();
		void							CreateIndexBuffer();
		void							CreateUniformBuffer();
		void							CreateCommandBuffers();
		void							CreateSyncObjects();
		void							CreateFramebuffers();

	public:
		VkImageView						CreateImageView(VkImage image, VkFormat format);
		void							CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		VkCommandBuffer					BeginSingleTimeCommands();
		void							EndSingleTimeCommands(VkCommandBuffer& commandBuffer);
		void							CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

	private:
		void							CleanupSwapChain();
		void							RecreateSwapChain();
		void							UpdateUniformBuffer(uint32_t currentImage);
		void							RecordCommandBuffer(CDescriptorPool* pDescriptorPool, CPipeline* pPipeline, VkCommandBuffer commandBuffer, uint32_t imageIndex);
	public:
		void							DrawFrame(CDescriptorPool* pDescriptorPool, CPipeline* pPipeline);

	private:
		VkSurfaceFormatKHR				ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR				ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D						ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	public:
		VkSwapchainKHR&					GetVkSwapChain()			{ return m_SwapChain; }
		VkRenderPass&					GetVkRenderPass()			{ return m_RenderPass; }
		VkFormat&						GetVkFormat()				{ return m_Format; }
		VkExtent2D&						GetVkExtent()				{ return m_Extent; }
		std::vector<VkImage>&			GetImages()					{ return m_Images; }
		std::vector<VkImageView>&		GetImageViews()				{ return m_ImageViews; }
		std::vector<VkFramebuffer>&		GetFramebuffers()			{ return m_Framebuffers; }
		std::vector<VkCommandBuffer>&	GetVkCommandBuffer()		{ return m_CommandBuffers; }
		VkBuffer&						GetVertexBuffer()			{ return m_VertexBuffer; }
		VkDeviceMemory&					GetVertexBufferMemory()		{ return m_VertexBufferMemory; }
		VkBuffer&						GetIndexBuffer()			{ return m_IndexBuffer; }
		VkDeviceMemory&					GetIndexBufferMemory()		{ return m_IndexBufferMemory; }
		std::vector<VkBuffer>&			GetUniformBuffers()			{ return m_UniformBuffers; }
		std::vector<VkDeviceMemory>&	GetUniformBuffersMemory()	{ return m_UniformBuffersMemory; }
		std::vector<void*>&				GetUniformBuffersMapped()	{ return m_UniformBuffersMapped; }
	};
};
