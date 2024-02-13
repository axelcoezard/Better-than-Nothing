#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief The texture struct that contains all the data of a texture
	 */
	struct Texture
	{
		/**
		 * @brief The file path of the texture
		 */
		std::string filePath;

		/**
		 * @brief The mip levels of the texture
		 */
		u32 mipLevels;

		/**
		 * @brief The image
		 */
		VkImage image;

		/**
		 * @brief The image memory
		 */
		VkDeviceMemory imageMemory;

		/**
		 * @brief The image sampler
		 */
		VkSampler sampler;

		/**
		 * @brief The image view
		 */
		VkImageView imageView;
	};
};
