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

		for (auto entry : m_pModels) {
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

	void CRenderer::LoadModel(const std::string& modelID, const std::string& modelPath, const std::string& texturePath)
	{
		auto model = new CModel(m_pDevice, this);
		model->LoadFromFiles(modelPath, texturePath);

		auto entry = std::pair<std::string, CModel*>(modelID, model);
		m_pModels.insert(entry);
	}

	void CRenderer::PrepareFrame()
	{
		m_pDescriptorPool->CreateDescriptorSets();
	}

	void CRenderer::DrawFrame()
	{
		auto pPipeline = m_pPipeLines.at("main");

		m_pSwapChain->BindDescriptorPool(m_pDescriptorPool);
		m_pSwapChain->BeginRecordCommandBuffer(pPipeline);

		auto index = 0;
		for (auto & entry : m_pModels) {
			auto pModel = entry.second;

			m_pSwapChain->BindModel(pModel);
			m_pDescriptorPool->UpdateDescriptorSets(pModel);
			m_pSwapChain->DrawModel(pPipeline, pModel);
			index++;
		}

		m_pSwapChain->EndRecordCommandBuffer();
	}
}
