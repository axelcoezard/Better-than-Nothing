#pragma once

#include <map>
namespace BetterThanNothing
{
	class Window;
	class Device;
	class SwapChain;
	class DescriptorPool;
	class Texture;
	class Pipeline;
	class Entity;
	class Scene;
	class DrawStreamBuilder;

	/**
	 * @brief The Renderer class that is used to render a scene
	 */
	class Renderer
	{
	private:
		/**
		 * @brief The pointer to the window
		 */
		Window* m_Window;

		/**
		 * @brief The pointer to the device
		 */
		Device* m_Device;

		/**
		 * @brief The pointer to the swap chain
		 */
		SwapChain* m_SwapChain;

		/**
		 * @brief The pointer to the descriptor pool
		 */
		DescriptorPool* m_DescriptorPool;

		/**
		 * @brief All the pipelines
		 */
		std::map<std::string, Pipeline*> m_PipeLines;

		/**
		 * @brief All the uniform buffers
		 */
		std::vector<std::vector<VkBuffer>> m_UniformBuffers;

		/**
		 * @brief All the uniform buffers memory
		 */
		std::vector<std::vector<VkDeviceMemory>> m_UniformBuffersMemory;

		/**
		 * @brief All the uniform buffers mapped
		 */
		std::vector<std::vector<void*>> m_UniformBuffersMapped;

		/**
		 * @brief The uniform buffers count
		 */
		u32 m_UniformBuffersSize;

		/**
		 * @brief The uniform buffers maximum capacity
		 */
		u32 m_UniformBuffersCapacity;

	public:
		/**
		 * @brief Construct a new Renderer object
		 *
		 * @param window The pointer to the window
		 * @param device The pointer to the device
		 */
		Renderer(Window* window, Device* device);

		/**
		 * @brief Destroy the Renderer object
		 */
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer&&) = delete;

	private:
		/**
		 * @brief Create a new uniform buffer
		 */
		void CreateNewUniformBuffer();

		/**
		 * @brief Destroy all the uniform buffers
		 */
		void DestroyUniformBuffers();

	public:
		/**
		 * @brief Load a shader pipeline using the vertex and fragment shader files
		 *
		 * @param pipelineID The ID of the pipeline
		 * @param vertexShaderFilePath The path to the vertex shader file
		 * @param fragmentShaderFilePath The path to the fragment shader file
		 * @note The pipelineID must be unique.
		 * @note The vertexShaderFilePath and fragmentShaderFilePath must be valid.
		 * @note All the shaders must be compiled with the same version.
		 * @note The shader files path must be relative to the Shaders folder.
		 */
		void LoadPipeline(const std::string& pipelineID, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		/**
		 * @brief Render the scene
		 * @param scene The scene to render
		 */
		void Render(Scene* scene);

	public:
		/**
		 * @brief Get the pointer to the window
		 * @return Window* The pointer to the window
		 */
		Window* GetWindow() { return m_Window; }

		/**
		 * @brief Get the pointer to the device
		 * @return Device* The pointer to the device
		 */
		Device* GetDevice() { return m_Device; }

		/**
		 * @brief Get the pointer to the swap chain
		 * @return SwapChain* The pointer to the swap chain
		 */
		SwapChain* GetSwapChain() { return m_SwapChain; }

		/**
		 * @brief Get the pointer to the descriptor pool
		 * @return DescriptorPool* The pointer to the descriptor pool
		 */
		DescriptorPool* GetDescriptorPool() { return m_DescriptorPool; }

		/**
		 * @brief Get all the pipelines
		 * @return std::map<std::string, Pipeline*> All the pipelines
		 */
		std::map<std::string, Pipeline*> GetPipeLines() { return m_PipeLines; }

		/**
		 * @brief Get all the uniform buffers
		 * @return std::vector<std::vector<VkBuffer>> All the uniform buffers
		 */
		std::vector<std::vector<VkBuffer>>& GetUniformBuffers() { return m_UniformBuffers; }

		/**
		 * @brief Get all the uniform buffers memory
		 * @return std::vector<std::vector<VkDeviceMemory>> All the uniform buffers memory
		 */
		std::vector<std::vector<VkDeviceMemory>>& GetUniformBuffersMemory() { return m_UniformBuffersMemory; }

		/**
		 * @brief Get all the uniform buffers mapped
		 * @return std::vector<std::vector<void*>> All the uniform buffers mapped
		 */
		std::vector<std::vector<void*>>& GetUniformBuffersMapped() { return m_UniformBuffersMapped; }
	};
};
