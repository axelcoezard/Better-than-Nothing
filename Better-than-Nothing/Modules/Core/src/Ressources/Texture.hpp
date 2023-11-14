#pragma once

namespace BetterThanNothing
{
	struct Texture
	{
		std::string			mame;
		std::string			filePath;

		u32					mipLevels;

		VkImage				image;
		VkDeviceMemory		imageMemory;
		VkSampler			sampler;
		VkImageView			imageView;
	};
};
