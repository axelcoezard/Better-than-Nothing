#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief The details of a shader.
	 * It contains the number of uniform buffers, storage buffers and samplers
	 */
	struct ShaderDetails
	{
		/**
		 * @brief The number of uniform buffers in the shader
		 */
		uint32_t uniformBufferCount;

		/**
		 * @brief The number of storage buffers in the shader
		 */
		uint32_t storageBufferCount;

		/**
		 * @brief The number of samplers in the shader
		 */
		uint32_t samplerCount;
	};

	/**
	 * @brief The model struct that contains all the data of a 3D model
	 */
	struct Shader
	{
		/**
		 * @brief The file path of the shader
		 */
		std::string filePath;

		/**
		 * @brief The stage of the shader
		 */
		glslang_stage_t stage;

		/**
		 * @brief The Vulkan shader module
		 */
		VkShaderModule module;

		/**
		 * @brief The details of the shader
		 */
		ShaderDetails details;
	};
};
