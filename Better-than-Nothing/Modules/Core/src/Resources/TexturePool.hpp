#pragma once

#include "Resources/ResourcePool.hpp"
#include "Resources/Texture.hpp"

namespace BetterThanNothing
{
	class Device;

	typedef std::pair<VkImage, VkDeviceMemory>	ImageData;

	class TexturePool: public ResourcePool<Texture>
	{
	private:
		Device*			m_Device;

	public:
						TexturePool(const std::string& basePath, Device* device);
						~TexturePool();

		Texture*		GetResource(const std::string& filePath) override;

	private:
		ImageData		CreateTextureImage(const std::string& filePath, u32* mipLevels);
		VkImageView		CreateTextureImageView(VkImage& image, u32 mipLevels);
		VkSampler		CreateTextureSampler(u32 mipLevels);
		void			GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, u32 mipLevels);
	};
};
