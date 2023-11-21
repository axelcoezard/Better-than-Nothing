#pragma once

namespace BetterThanNothing
{
	class Device;
	class SwapChain;
	class DescriptorPool;

	/**
	 * @brief A pipeline uses shaders and a render pass to describe the graphics pipeline
	 */
	class Pipeline
	{
	private:
		/**
		 * @brief The id of the pipeline
		 */
		std::string			m_Id;

		/**
		 * @brief A pointer to the device
		 */
		Device*				m_Device;

		/**
		 * @brief A pointer to the swap chain
		 */
		SwapChain*			m_SwapChain;

		/**
		 * @brief A pointer to the descriptor pool
		 */
		DescriptorPool*		m_DescriptorPool;

		/**
		 * @brief The vertex shader module
		 */
		VkShaderModule		m_VertexShaderModule;

		/**
		 * @brief The fragment shader module
		 */
		VkShaderModule		m_FragmentShaderModule;

		/**
		 * @brief The Pipeline Layout
		 */
		VkPipelineLayout	m_PipelineLayout;

		/**
		 * @brief The graphics pipeline
		 */
		VkPipeline			m_GraphicsPipeline;

	public:
		/**
		 * @brief Construct a new Pipeline object
		 *
		 * @param id The id of the pipeline
		 * @param device A pointer to the device
		 * @param swapChain A pointer to the swap chain
		 * @param descriptorPool A pointer to the descriptor pool
		 * @param vertexShaderFilePath The file path of the vertex shader
		 * @param fragmentShaderFilePath The file path of the fragment shader
		 */
		Pipeline(const std::string& id, Device* device, SwapChain* swapChain, DescriptorPool* descriptorPool, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		/**
		 * @brief Destroy the Pipeline object
		 */
		~Pipeline();

		Pipeline(const Pipeline&) = delete;
		Pipeline& operator=(const Pipeline&) = delete;
		Pipeline(Pipeline&&) = delete;
		Pipeline& operator=(Pipeline&&) = delete;

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
		 * @brief Load a shader
		 *
		 * @param vertexShaderFilePath The file path of the vertex shader
		 * @param fragmentShaderFilePath The file path of the fragment shader
		 */
		void LoadShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		/**
		 * @brief Create a shader module using the code of the shader
		 *
		 * @param code The code of the shader
		 * @return VkShaderModule The shader module
		 */
		VkShaderModule CreateShaderModule(const std::vector<char>& code);

		/**
		 * @brief Create the render pass
		 */
		void CreateRenderPass();

		/**
		 * @brief Create the descriptor set layout
		 */
		void CreateDescriptorSetLayout();

		/**
		 * @brief Create the graphics pipeline
		 */
		void CreateGraphicsPipeline();

	public:
		/**
		 * @brief Get the id of the pipeline
		 *
		 * @return std::string The id of the pipeline
		 */
		std::string& GetId() { return m_Id; }

		/**
		 * @brief Get the vertex shader module
		 */
		VkShaderModule& GetVkVertexShaderModule() { return m_VertexShaderModule; }

		/**
		 * @brief Get the fragment shader module
		 */
		VkShaderModule& GetVkFragmentShaderModule() { return m_FragmentShaderModule; }

		/**
		 * @brief Get the pipeline layout
		 */
		VkPipelineLayout& GetVkPipelineLayout() { return m_PipelineLayout; }

		/**
		 * @brief Get the graphics pipeline
		 */
		VkPipeline& GetVkGraphicsPipeline() { return m_GraphicsPipeline; }
	};
}
