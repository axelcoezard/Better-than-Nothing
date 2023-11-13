#pragma once

namespace BetterThanNothing
{
	class Device;
	class CommandPool;
	class SwapChain;

	class Texture
	{
	private:
		Device*				m_pDevice;
		CommandPool*		m_pCommandPool;
		SwapChain*			m_pSwapChain;

		VkBuffer			m_StagingBuffer;
		VkDeviceMemory 		m_StagingBufferMemory;

		u32			m_MipLevels;

		VkImage				m_Image;
		VkDeviceMemory		m_ImageMemory;
		VkSampler			m_Sampler;
		VkImageView			m_ImageView;

		std::string			m_FilePath;

	public:
							Texture(Device* pDevice, CommandPool* pCommandPool, SwapChain* pSwapChain);
							~Texture();

							Texture(const Texture&) = delete;
		Texture&			operator=(const Texture&) = delete;
							Texture(Texture&&) = delete;
		Texture&			operator=(Texture&&) = delete;

		void				LoadFromFile(const std::string& filePath);
		void				GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, u32 mipLevels);

	private:
		void				CreateTextureImage(const std::string& filePath);
		void				CreateTextureImageView();
		void				CreateTextureSampler();

	public:
		static void			CreateImage(Device* pDevice, u32 width, u32 height, u32 mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		static void			TransitionImageLayout(SwapChain* pSwapChain, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, u32 mipLevels);
		static void			CopyBufferToImage(SwapChain* pSwapChain, VkBuffer buffer, VkImage image, u32 width, u32 height);

	public:
		VkImage&			GetVkImage()				{ return m_Image; }
		VkDeviceMemory&		GetVkImageMemory()			{ return m_ImageMemory; }
		VkSampler&			GetVkTextureSampler()		{ return m_Sampler; }
		VkImageView&		GetVkTextureImageView()		{ return m_ImageView; }
		std::string&		GetFilePath()				{ return m_FilePath; }
	};
};
