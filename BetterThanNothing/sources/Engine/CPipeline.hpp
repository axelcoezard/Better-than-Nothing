#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <memory>

#include "CDevice.hpp"

namespace BetterThanNothing
{
	class CSwapChain;

	class CPipeline
	{
	private:
		CDevice*						m_pDevice;
		CSwapChain*						m_pSwapChain;

		VkShaderModule					m_VertexShaderModule;
		VkShaderModule					m_FragmentShaderModule;
		VkPipelineLayout				m_PipelineLayout;
		VkPipeline						m_GraphicsPipeline;

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

	public:
		VkShaderModule&					GetVkVertexShaderModule()	{ return m_VertexShaderModule; }
		VkShaderModule&					GetVkFragmentShaderModule()	{ return m_FragmentShaderModule; }
		VkPipelineLayout&				GetVkPipelineLayout()		{ return m_PipelineLayout; }
		VkPipeline&						GetVkGraphicsPipeline()		{ return m_GraphicsPipeline; }

	};
}
