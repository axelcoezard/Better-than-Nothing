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

	class Renderer
	{
	private:
		Window*								m_Window;
		Device*								m_Device;
		SwapChain*							m_SwapChain;
		DescriptorPool*						m_DescriptorPool;
		Scene*								m_Scene;

		std::map<std::string, Pipeline*>	m_PipeLines;

		std::vector<std::vector<VkBuffer>>			m_UniformBuffers;
		std::vector<std::vector<VkDeviceMemory>>	m_UniformBuffersMemory;
		std::vector<std::vector<void*>>				m_UniformBuffersMapped;
		u32											m_UniformBuffersSize;
		u32											m_UniformBuffersCapacity;

	public:
											Renderer(Window* pWindow, Device* pDevice);
											~Renderer();

											Renderer(const Renderer&) = delete;
		Renderer&							operator=(const Renderer&) = delete;
											Renderer(Renderer&&) = delete;
		Renderer&							operator=(Renderer&&) = delete;

	private:
		void								CreateNewUniformBuffer();
		void								DestroyUniformBuffers();

	public:
		void								LoadPipeline(const std::string& pipelineID, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void								Render(Scene* pScene);

	public:
		Window*								GetWindow()			{ return m_Window; }
		Device*								GetDevice()			{ return m_Device; }
		SwapChain*							GetSwapChain()		{ return m_SwapChain; }
		DescriptorPool*						GetDescriptorPool()	{ return m_DescriptorPool; }
		std::map<std::string, Pipeline*>	GetPipeLines()		{ return m_PipeLines; }
		Scene*								GetScene()			{ return m_Scene; }

		std::vector<std::vector<VkBuffer>>&			GetUniformBuffers()				{ return m_UniformBuffers; }
		std::vector<std::vector<VkDeviceMemory>>&	GetUniformBuffersMemory()		{ return m_UniformBuffersMemory; }
		std::vector<std::vector<void*>>& 			GetUniformBuffersMapped()		{ return m_UniformBuffersMapped; }
	};
};
