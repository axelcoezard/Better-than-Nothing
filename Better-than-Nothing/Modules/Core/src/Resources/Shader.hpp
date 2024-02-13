#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief A resource of a shader (uniform buffer, storage buffer, sampler, etc.)
	 */
	struct ShaderResource
	{
		/**
		 * @brief The name of the resource
		 */
		std::string name;

		/**
		 * @brief The descriptor set of the resource
		 */
		u32 set;

		/**
		 * @brief The binding of the resource
		 */
		u32 binding;

		/**
		 * @brief The size of the resource
		 */
		u64 size;

		/**
		 * @brief The type of the resource
		 */
		VkDescriptorType type;
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
		std::vector<ShaderResource> resources;
	};
};
