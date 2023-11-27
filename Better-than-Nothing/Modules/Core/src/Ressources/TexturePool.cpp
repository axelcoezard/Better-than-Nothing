#include "BetterThanNothing.hpp"

#include "stb_image.h"

namespace BetterThanNothing
{
	TexturePool::TexturePool(const std::string& basePath, Device* device): RessourcePool(basePath)
	{
		m_Device = device;
	}

	TexturePool::~TexturePool()
	{
		VkDevice device = m_Device->GetVkDevice();

		for (auto& [filePath, texture] : m_Ressources)
		{
			vkDestroySampler(device, texture->sampler, nullptr);
			vkDestroyImageView(device, texture->imageView, nullptr);
			vkDestroyImage(device, texture->image, nullptr);
			vkFreeMemory(device, texture->imageMemory, nullptr);
			delete texture;
		}
	}

	Texture* TexturePool::GetRessource(const std::string& filePath)
	{
		auto it = m_Ressources.find(filePath);
		if (it != m_Ressources.end())
			return it->second;

		Texture* texture = new Texture();

		u32 mipLevels;
		auto [image, imageMemory] = CreateTextureImage(m_BasePath + filePath, &mipLevels);
		auto sampler = CreateTextureSampler(mipLevels);
		auto imageView = CreateTextureImageView(image, mipLevels);

		texture->filePath = filePath;
		texture->mipLevels = mipLevels;
		texture->image = image;
		texture->imageMemory = imageMemory;
		texture->imageView = imageView;
		texture->sampler = sampler;

		LOG_SUCCESS("TexturePool: " + filePath);

		m_Ressources[filePath] = texture;
		return texture;
	}

	ImageData TexturePool::CreateTextureImage(const std::string& filePath, u32* mipLevels)
	{
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load(filePath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		VkDeviceSize imageSize = texWidth * texHeight * 4;

		*mipLevels = static_cast<u32>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;

		if (!pixels) {
			throw std::runtime_error("failed to load texture image!");
		}

		Buffer stagingBuffer;
		m_Device->CreateBuffer(
			&stagingBuffer,
			imageSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		void* data;
		m_Device->MapBuffer(&stagingBuffer, 0, 0, &data);
		memcpy(data, pixels, static_cast<size_t>(imageSize));
		m_Device->UnmapBuffer(&stagingBuffer);

		stbi_image_free(pixels);

		VkImage image;
		VkDeviceMemory imageMemory;

		m_Device->CreateImage(
			texWidth, texHeight,
			*mipLevels,
			VK_SAMPLE_COUNT_1_BIT,
			VK_FORMAT_R8G8B8A8_SRGB,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			image, imageMemory);
		m_Device->TransitionImageLayout(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, *mipLevels);
		m_Device->CopyBufferToImage(stagingBuffer.m_Buffer, image, static_cast<u32>(texWidth), static_cast<u32>(texHeight));
		GenerateMipmaps(image, VK_FORMAT_R8G8B8A8_SRGB, texWidth, texHeight, *mipLevels);

		m_Device->DestroyBuffer(&stagingBuffer);

		return {image, imageMemory};
	}

	VkImageView TexturePool::CreateTextureImageView(VkImage& image, u32 mipLevels) {
		return m_Device->CreateImageView(image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
	}

	VkSampler TexturePool::CreateTextureSampler(u32 mipLevels)
	{
		VkSamplerCreateInfo samplerInfo{};
		samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		samplerInfo.magFilter = VK_FILTER_LINEAR;
		samplerInfo.minFilter = VK_FILTER_LINEAR;
		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		samplerInfo.unnormalizedCoordinates = VK_FALSE;
		samplerInfo.compareEnable = VK_FALSE;
		samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

		VkDevice device = m_Device->GetVkDevice();

		// Anisotropic filtering
		VkPhysicalDeviceProperties properties{};
		vkGetPhysicalDeviceProperties(m_Device->GetVkPhysicalDevice(), &properties);
		samplerInfo.anisotropyEnable = VK_TRUE;
		samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;

		// Mipmap
		samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		samplerInfo.minLod = 0; // static_cast<f32>(mipLevels / 2);
		samplerInfo.maxLod = static_cast<f32>(mipLevels);
		samplerInfo.mipLodBias = 0.0f;

		VkSampler sampler;
		if (vkCreateSampler(device, &samplerInfo, nullptr, &sampler) != VK_SUCCESS) {
			throw std::runtime_error("failed to create texture sampler!");
		}
		return sampler;
	}

	void TexturePool::GenerateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, u32 mipLevels)
	{
		VkFormatProperties formatProperties;
		vkGetPhysicalDeviceFormatProperties(m_Device->GetVkPhysicalDevice(), imageFormat, &formatProperties);

		if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
			throw std::runtime_error("texture image format does not support linear blitting!");
		}

		CommandBuffer::SingleTimeCommands([&](CommandBuffer* commandBuffer) {
			VkImageMemoryBarrier barrier{};
			barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			barrier.image = image;
			barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			barrier.subresourceRange.baseArrayLayer = 0;
			barrier.subresourceRange.layerCount = 1;
			barrier.subresourceRange.levelCount = 1;

			int32_t mipWidth = texWidth;
			int32_t mipHeight = texHeight;

			for (u32 i = 1; i < mipLevels; i++) {
				barrier.subresourceRange.baseMipLevel = i - 1;
				barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
				barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

				commandBuffer->CmdPipelineBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, barrier);

				VkImageBlit blit{};
				blit.srcOffsets[0] = {0, 0, 0};
				blit.srcOffsets[1] = {mipWidth, mipHeight, 1};
				blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				blit.srcSubresource.mipLevel = i - 1;
				blit.srcSubresource.baseArrayLayer = 0;
				blit.srcSubresource.layerCount = 1;
				blit.dstOffsets[0] = {0, 0, 0};
				blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
				blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				blit.dstSubresource.mipLevel = i;
				blit.dstSubresource.baseArrayLayer = 0;
				blit.dstSubresource.layerCount = 1;

				commandBuffer->CmdBlitImage(image, image, blit);

				barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
				barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

				commandBuffer->CmdPipelineBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, barrier);

				if (mipWidth > 1) mipWidth /= 2;
				if (mipHeight > 1) mipHeight /= 2;
			}

			barrier.subresourceRange.baseMipLevel = mipLevels - 1;
			barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
			barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
			barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

			commandBuffer->CmdPipelineBarrier(VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, barrier);
		}, m_Device);
	}
};
