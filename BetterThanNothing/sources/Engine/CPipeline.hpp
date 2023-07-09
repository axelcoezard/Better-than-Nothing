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
		std::shared_ptr<CDevice>		m_pDevice;
		std::shared_ptr<CSwapChain>		m_pSwapChain;

		VkShaderModule					m_VertexShaderModule;
		VkShaderModule					m_FragmentShaderModule;
		VkRenderPass					m_RenderPass;
		VkPipelineLayout				m_PipelineLayout;
		VkPipeline						m_GraphicsPipeline;
	public:
										CPipeline(std::shared_ptr<CDevice>& pDevice, std::shared_ptr<CSwapChain>& pSwapChain);
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
	};
}
