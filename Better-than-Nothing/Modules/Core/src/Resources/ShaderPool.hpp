#pragma once

#include "Resources/ResourcePool.hpp"
#include "Resources/Shader.hpp"

namespace BetterThanNothing
{
	class Device;

	class ShaderPool: public ResourcePool<Shader>
	{
	private:
		Device*			m_Device;

	public:
						ShaderPool(const std::string& basePath, Device* device);
						~ShaderPool();

		/**
		 * @brief Get a shader from the pool. If the shader is not in the pool, it will be loaded.
		 *
		 * @param filePath The file path of the shader
		 * @return Shader* The shader
		 */
		Shader*			GetResource(const std::string& filePath) override;

	private:
		/**
		 * @brief Read a file
		 *
		 * @param filePath The file path of the file
		 *
		 * @return std::vector<char> The content of the file
		 */
		std::vector<char> ReadFile(const std::string& filePath);

		/**
		 * @brief Compile a shader
		 *
		 * @param shaderCode The code of the shader
		 * @param stage The stage of the shader
		 * @return glslang_program_t* The program of the shader
		 */
		glslang_program_t* GetShaderProgram(std::vector<char> shaderCode, glslang_stage_t stage);

		/**
		 * @brief Create a shader module using the code of the shader
		 *
		 * @param code The code of the shader
		 * @return VkShaderModule The shader module
		 */
		VkShaderModule CreateShaderModule(glslang_program_t* program);

		/**
		 * @brief Get the stage of a shader from its file path
		 *
		 * @param filePath The file path of the shader
		 * @return glslang_stage_t The stage of the shader
		 */
		glslang_stage_t GetShaderStage(const std::string& filePath);

		/**
		 * @brief Get the details of a shader
		 *
		 * @param program The program of the shader
		 * @return ShaderDetails The details of the shader
		 */
		ShaderDetails GetShaderDetails(glslang_program_t* program);
	};
};
