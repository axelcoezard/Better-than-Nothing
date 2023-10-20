#include "CRenderer.hpp"

#include "Engine/CWindow.hpp"
#include "Engine/CDevice.hpp"
#include "Engine/CCommandPool.hpp"
#include "Engine/CSwapChain.hpp"
#include "Engine/CDescriptorPool.hpp"
#include "Engine/CTexture.hpp"
#include "Engine/CPipeline.hpp"
#include "Engine/CModel.hpp"
#include "Scene/CScene.hpp"
#include "Scene/CCamera.hpp"

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

	void CRenderer::PrepareFrame(CScene* pScene)
	{
		auto models = pScene->GetModels();

		m_pSwapChain->CreateUniformBuffers(pScene);
		m_pSwapChain->CreateCommandBuffers(pScene);

		m_pDescriptorPool->CreateDescriptorPool(models);
		m_pDescriptorPool->CreateDescriptorSets(models);
	}

	void CRenderer::Render(CScene* pScene)
	{
		auto pPipeline = m_pPipeLines.at("main");
		auto models = pScene->GetModels();

		m_pSwapChain->BindDescriptorPool(m_pDescriptorPool);

		for (uint32_t i = 0; i < models.size(); i++) {
			m_pSwapChain->BeginRecordCommandBuffer(pPipeline, i);

			m_pSwapChain->BindModel(models[i], i);
			m_pSwapChain->UpdateUniformBuffer(pScene, models[i], i);
			m_pSwapChain->DrawModel(pPipeline, models[i], i);

			m_pSwapChain->EndRecordCommandBuffer(i);
		}
	}
}
