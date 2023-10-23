#pragma once

#include <map>
namespace BetterThanNothing
{
	class Window;
	class Device;
	class CommandPool;
	class SwapChain;
	class DescriptorPool;
	class Texture;
	class Pipeline;
	class Model;
	class Scene;

	class Renderer
	{
	private:
		Window*								m_pWindow;
		Device*								m_pDevice;
		CommandPool*						m_pCommandPool;
		SwapChain*							m_pSwapChain;
		DescriptorPool*					m_pDescriptorPool;

		std::map<std::string, Pipeline*>	m_pPipeLines;

	public:
											Renderer(Window* pWindow, Device* pDevice);
											~Renderer();

											Renderer(const Renderer&) = delete;
		Renderer&							operator=(const Renderer&) = delete;
											Renderer(Renderer&&) = delete;
		Renderer&							operator=(Renderer&&) = delete;

	public:
		void								LoadPipeline(const std::string& pipelineID, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void								Prepare(Scene* pScene);
		void								Render(Scene* pScene);

	public:
		Window*							GetWindow()			{ return m_pWindow; }
		Device*							GetDevice()			{ return m_pDevice; }
		CommandPool*						GetCommandPool()	{ return m_pCommandPool; }
		SwapChain*							GetSwapChain()		{ return m_pSwapChain; }
		DescriptorPool*					GetDescriptorPool()	{ return m_pDescriptorPool; }
		std::map<std::string, Pipeline*>	GetPipeLines()		{ return m_pPipeLines; }
	};
};
