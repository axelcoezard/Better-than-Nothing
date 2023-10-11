#include "CRenderer.hpp"

#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CCommandPool.hpp"
#include "Engine/CSwapChain.hpp"
#include "Engine/CDescriptorPool.hpp"
#include "Engine/CTexture.hpp"
#include "Engine/CPipeline.hpp"

namespace BetterThanNothing
{
	CRenderer::CRenderer(CWindow* pWindow, CDevice* pDevice): m_pWindow(pWindow), m_pDevice(pDevice)
	{
		m_pCommandPool = new CCommandPool(m_pDevice);
		m_pSwapChain = new CSwapChain(m_pWindow, m_pDevice, m_pCommandPool);
		m_pDescriptorPool = new CDescriptorPool(m_pDevice, m_pSwapChain);

		// one per shaders couple
		CreatePipeline(
			"main",
			"/home/acoezard/lab/better-than-nothing/Assets/Shaders/vert.spv",
			"/home/acoezard/lab/better-than-nothing/Assets/Shaders/frag.spv"
		);
	}

	CRenderer::~CRenderer()
	{
		for (auto & entry : m_pPipeLines) {
			delete entry.second;
		}

		delete m_pDescriptorPool;
		delete m_pSwapChain;
		delete m_pCommandPool;
	}

	void CRenderer::CreatePipeline(const std::string& pipelineID, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		auto pipeline = new CPipeline(m_pDevice, m_pSwapChain, m_pDescriptorPool, vertexShaderFilePath, fragmentShaderFilePath);
		auto entry = std::pair<std::string, CPipeline*>(pipelineID, pipeline);

		m_pPipeLines.insert(entry);
	}

	void CRenderer::DrawFrame()
	{
		m_pSwapChain->DrawFrame(m_pDescriptorPool, m_pPipeLines.at("main"));
	}
}
