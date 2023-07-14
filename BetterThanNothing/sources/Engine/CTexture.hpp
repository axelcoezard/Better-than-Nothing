#pragma once

namespace BetterThanNothing
{
	class CDevice;
	class CCommandPool;
	class CSwapChain;

	class CTexture
	{
	private:
		CDevice*			m_pDevice;
		CCommandPool*		m_pCommandPool;
		CSwapChain*			m_pSwapChain;

		VkBuffer			m_StagingBuffer;
		VkDeviceMemory 		m_StagingBufferMemory;

		VkImage				m_Image;
		VkDeviceMemory		m_ImageMemory;


	public:
							CTexture(CDevice* pDevice, CCommandPool* pCommandPool, CSwapChain* pSwapChain);
							~CTexture();

							CTexture(const CTexture&) = delete;
		CTexture&			operator=(const CTexture&) = delete;
							CTexture(CTexture&&) = delete;
		CTexture&			operator=(CTexture&&) = delete;

		void				CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	private:
		void				CreateTextureImage();

	public:
		void				TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
		void				CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	public:
		VkImage&			GetVkImage()		{ return m_Image; }
		VkDeviceMemory&		GetVkImageMemory()	{ return m_ImageMemory; }
	};
};
