#include "Engine/Renderer.hpp"
#include "Engine/Window.hpp"
#include "Engine/Device.hpp"
#include "Engine/CommandPool.hpp"
#include "Engine/SwapChain.hpp"
#include "Engine/DescriptorPool.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Pipeline.hpp"
#include "Engine/Model.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"

namespace BetterThanNothing
{
	Renderer::Renderer(Window* pWindow, Device* pDevice): m_pWindow(pWindow), m_pDevice(pDevice)
	{
		m_pCommandPool = new CommandPool(m_pDevice);
		m_pSwapChain = new SwapChain(m_pWindow, m_pDevice, m_pCommandPool);
		m_pDescriptorPool = new DescriptorPool(m_pDevice, m_pSwapChain);
	}

	Renderer::~Renderer()
	{
		for (auto & entry : m_pPipeLines) {
			delete entry.second;
		}

		delete m_pDescriptorPool;
		delete m_pSwapChain;
		delete m_pCommandPool;
	}

	void Renderer::LoadPipeline(const std::string& pipelineID, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		auto pipeline = new Pipeline(m_pDevice, m_pSwapChain, m_pDescriptorPool, vertexShaderFilePath, fragmentShaderFilePath);
		auto entry = std::pair<std::string, Pipeline*>(pipelineID, pipeline);

		m_pPipeLines.insert(entry);
	}

	void Renderer::Prepare(Scene* pScene)
	{
		auto models = pScene->GetModels();

		m_pSwapChain->CreateUniformBuffers(pScene);
		m_pSwapChain->CreateCommandBuffers();

		m_pDescriptorPool->CreateDescriptorPool(models);
		m_pDescriptorPool->CreateDescriptorSets(models);

		m_pSwapChain->BindDescriptorPool(m_pDescriptorPool);
	}

	void Renderer::Render(Scene* pScene)
	{
		auto pPipeline = m_pPipeLines.at("main");
		auto models = pScene->GetModels();

		if (m_pSwapChain->BeginRecordCommandBuffer(pPipeline, pScene)) {

			for (uint32_t i = 0; i < models.size(); i++) {
				m_pSwapChain->BindModel(models[i]);
				m_pSwapChain->DrawModel(pPipeline, models[i], i);
			}

			ImGui_ImplVulkan_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();

			ImGui::Render();
			ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_pSwapChain->GetCurrentCommandBuffer());

			m_pSwapChain->EndRecordCommandBuffer();
		}
	}
}
