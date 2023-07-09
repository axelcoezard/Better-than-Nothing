#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <memory>

#include "CDevice.hpp"
#include "CSwapChain.hpp"

namespace BetterThanNothing
{
	class CPipeline
	{
	private:
		CDevice*						m_pDevice;
		CSwapChain*						m_pSwapChain;

		VkShaderModule					m_VertexShaderModule;
		VkShaderModule					m_FragmentShaderModule;
		VkRenderPass					m_RenderPass;
		VkPipelineLayout				m_PipelineLayout;
		VkPipeline						m_GraphicsPipeline;

		std::vector<VkFramebuffer>		m_Framebuffers;
	public:
										CPipeline(CDevice* pDevice, CSwapChain* pSwapChain);
										~CPipeline();

										CPipeline(const CPipeline&) = delete;
		CPipeline&						operator=(const CPipeline&) = delete;
										CPipeline(CPipeline&&) = delete;
		CPipeline&						operator=(CPipeline&&) = delete;

	private:
		std::vector<char>				ReadFile(const std::string& filePath);
		void							LoadShader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		VkShaderModule					CreateShaderModule(const std::vector<char>& code);

		void							CreateRenderPass();
		void							CreateGraphicsPipeline();
		void							CreateFramebuffers();

	public:
		VkShaderModule&					GetVkVertexShaderModule()	{ return m_VertexShaderModule; }
		VkShaderModule&					GetVkFragmentShaderModule()	{ return m_FragmentShaderModule; }
		VkRenderPass&					GetVkRenderPass()			{ return m_RenderPass; }
		VkPipelineLayout&				GetVkPipelineLayout()		{ return m_PipelineLayout; }
		VkPipeline&						GetVkGraphicsPipeline()		{ return m_GraphicsPipeline; }

		std::vector<VkFramebuffer>&		GetFramebuffers()			{ return m_Framebuffers; }
	};
}
