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
		Window*								m_pWindow;
		Device*								m_pDevice;
		SwapChain*							m_pSwapChain;
		DescriptorPool*						m_pDescriptorPool;
		Scene*								m_pScene;

		std::map<std::string, Pipeline*>	m_pPipeLines;

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
		Window*								GetWindow()			{ return m_pWindow; }
		Device*								GetDevice()			{ return m_pDevice; }
		SwapChain*							GetSwapChain()		{ return m_pSwapChain; }
		DescriptorPool*						GetDescriptorPool()	{ return m_pDescriptorPool; }
		std::map<std::string, Pipeline*>	GetPipeLines()		{ return m_pPipeLines; }
		Scene*								GetScene()			{ return m_pScene; }

		std::vector<std::vector<VkBuffer>>&			GetUniformBuffers()				{ return m_UniformBuffers; }
		std::vector<std::vector<VkDeviceMemory>>&	GetUniformBuffersMemory()		{ return m_UniformBuffersMemory; }
		std::vector<std::vector<void*>>& 			GetUniformBuffersMapped()		{ return m_UniformBuffersMapped; }
	};
};
