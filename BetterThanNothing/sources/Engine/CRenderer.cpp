#include "CRenderer.hpp"

#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CCommandPool.hpp"
#include "Engine/CSwapChain.hpp"
#include "Engine/CDescriptorPool.hpp"
#include "Engine/CTexture.hpp"
#include "Engine/CPipeline.hpp"
#include "Engine/CModel.hpp"

namespace BetterThanNothing
{
	CRenderer::CRenderer(CWindow* pWindow, CDevice* pDevice): m_pWindow(pWindow), m_pDevice(pDevice)
	{
		m_pCommandPool = new CCommandPool(m_pDevice);
		m_pSwapChain = new CSwapChain(m_pWindow, m_pDevice, m_pCommandPool);
		m_pDescriptorPool = new CDescriptorPool(m_pDevice, m_pSwapChain);
	}

	CRenderer::~CRenderer()
	{
		for (auto & entry : m_pPipeLines) {
			delete entry.second;
		}

		for (uint32_t i = 0; i < m_pModels.size(); i++) {
			delete m_pModels[i];
		}

		delete m_pDescriptorPool;
		delete m_pSwapChain;
		delete m_pCommandPool;
	}

	void CRenderer::LoadPipeline(const std::string& pipelineID, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		auto pipeline = new CPipeline(m_pDevice, m_pSwapChain, m_pDescriptorPool, vertexShaderFilePath, fragmentShaderFilePath);
		auto entry = std::pair<std::string, CPipeline*>(pipelineID, pipeline);

		m_pPipeLines.insert(entry);
	}

	void CRenderer::LoadModel(const std::string& modelPath, const std::string& texturePath)
	{
		auto model = new CModel(m_pDevice, this);
		model->LoadFromFiles(modelPath, texturePath);

		m_pModels.push_back(model);
	}

	void CRenderer::PrepareFrame()
	{
		m_pDescriptorPool->CreateDescriptorPool(m_pModels);
		m_pDescriptorPool->CreateDescriptorSets(m_pModels);
	}

	void CRenderer::MoveCamera(float x, float y, float z)
	{
		m_pSwapChain->MoveCamera(x, y, z);
	}

	void CRenderer::DrawFrame()
	{
		auto pPipeline = m_pPipeLines.at("main");

		m_pSwapChain->BindDescriptorPool(m_pDescriptorPool);
		m_pSwapChain->BeginRecordCommandBuffer(pPipeline);

		for (uint32_t i = 0; i < m_pModels.size(); i++) {
			m_pSwapChain->BindModel(m_pModels[i]);
			m_pSwapChain->DrawModel(pPipeline, m_pModels[i], i);
		}

		m_pSwapChain->EndRecordCommandBuffer();
	}
}
