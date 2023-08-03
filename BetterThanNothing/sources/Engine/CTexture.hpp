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

		uint32_t			m_MipLevels;

		VkImage				m_Image;
		VkDeviceMemory		m_ImageMemory;
		VkSampler			m_Sampler;
		VkImageView			m_ImageView;


	public:
							CTexture(CDevice* pDevice, CCommandPool* pCommandPool, CSwapChain* pSwapChain);
							~CTexture();

							CTexture(const CTexture&) = delete;
		CTexture&			operator=(const CTexture&) = delete;
							CTexture(CTexture&&) = delete;
		CTexture&			operator=(CTexture&&) = delete;

		void				CreateImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void				GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

	private:
		void				CreateTextureImage();
		void				CreateTextureImageView();
		void				CreateTextureSampler();

	public:
		void				TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
		void				CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

	public:
		VkImage&			GetVkImage()				{ return m_Image; }
		VkDeviceMemory&		GetVkImageMemory()			{ return m_ImageMemory; }
		VkSampler&			GetVkTextureSampler()		{ return m_Sampler; }
		VkImageView&		GetVkTextureImageView()		{ return m_ImageView; }
	};
};
