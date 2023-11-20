#pragma once

namespace BetterThanNothing
{
	class Device;
	class SwapChain;
	class DescriptorPool;

	class Pipeline
	{
	private:
		std::string			m_Id;
		Device*				m_pDevice;
		SwapChain*			m_pSwapChain;
		DescriptorPool*		m_pDescriptorPool;



		VkShaderModule		m_VertexShaderModule;
		VkShaderModule		m_FragmentShaderModule;
		VkPipelineLayout	m_PipelineLayout;
		VkPipeline			m_GraphicsPipeline;

	public:
							Pipeline(const std::string& id, Device* pDevice, SwapChain* pSwapChain, DescriptorPool* pDescriptorPool, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
							~Pipeline();

							Pipeline(const Pipeline&) = delete;
		Pipeline&			operator=(const Pipeline&) = delete;
							Pipeline(Pipeline&&) = delete;
		Pipeline&			operator=(Pipeline&&) = delete;

	private:
		std::vector<char>	ReadFile(const std::string& filePath);
		void				LoadShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		VkShaderModule		CreateShaderModule(const std::vector<char>& code);

		void				CreateRenderPass();
		void				CreateDescriptorSetLayout();
		void				CreateGraphicsPipeline();

	public:
		std::string&		GetId()						{ return m_Id; }
		VkShaderModule&		GetVkVertexShaderModule()	{ return m_VertexShaderModule; }
		VkShaderModule&		GetVkFragmentShaderModule()	{ return m_FragmentShaderModule; }
		VkPipelineLayout&	GetVkPipelineLayout()		{ return m_PipelineLayout; }
		VkPipeline&			GetVkGraphicsPipeline()		{ return m_GraphicsPipeline; }

	};
}
