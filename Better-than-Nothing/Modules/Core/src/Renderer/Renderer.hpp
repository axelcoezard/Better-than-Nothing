#pragma once

#include <map>
namespace BetterThanNothing
{
	class Window;
	class Device;
	class SwapChain;
	class DescriptorPool;
	class ResourceManager;
	class Texture;
	class Pipeline;
	class Scene;
	class DrawStreamBuilder;
	class Buffer;
	class DrawStreamBufferPool;
	class RendererDebugInfo;

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
		 * @brief The pointer to the resource manager
		 */
		ResourceManager* m_ResourceManager;

		/**
		 * @brief The pointer to the swap chain
		 */
		SwapChain* m_SwapChain;

		/**
		 * @brief The pointer to the descriptor pool
		 */
		DescriptorPool* m_DescriptorPool;

		/**
		 * @brief The pointer to the uniform pool
		 */
		DrawStreamBufferPool* m_DrawStreamBuffers;

		/**
		 * @brief All the pipelines
		 */
		std::map<std::string, Pipeline*> m_PipeLines;

	public:
		/**
		 * @brief Construct a new Renderer object
		 *
		 * @param window The pointer to the window
		 * @param device The pointer to the device
		 * @param shaderPool The pointer to the shader pool
		 */
		Renderer(Window* window, Device* device, ResourceManager* resourceManager);

		/**
		 * @brief Destroy the Renderer object
		 */
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer&&) = delete;

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

		void BeforeRender();

		/**
		 * @brief Render the scene
		 * @param scene The scene to render
		 * @param debugInfo The debug info to display
		 */
		void Render(Scene* scene, RendererDebugInfo* debugInfo);

		void AfterRender();

	private:
		/**
		 * @brief Render the debug info using ImGui
		 * @param debugInfo The debug info to display
		 */
		void RenderDebugInfo(RendererDebugInfo* debugInfo);

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
	};
};
