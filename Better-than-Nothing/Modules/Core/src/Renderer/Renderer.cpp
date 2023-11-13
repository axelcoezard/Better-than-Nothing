#include "Renderer/Renderer.hpp"
#include "Renderer/Window.hpp"
#include "Renderer/Device.hpp"
#include "Renderer/CommandPool.hpp"
#include "Renderer/SwapChain.hpp"
#include "Renderer/DescriptorPool.hpp"
#include "Renderer/Texture.hpp"
#include "Renderer/Pipeline.hpp"
#include "Renderer/Model.hpp"
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
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

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

		ImGui::CreateContext();
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui_ImplGlfw_InitForVulkan(m_pWindow->GetPointer(), true);

		ImGui_ImplVulkan_InitInfo info = {};
		info.Instance = m_pDevice->GetVkInstance();
		info.PhysicalDevice = m_pDevice->GetVkPhysicalDevice();
		info.Device = m_pDevice->GetVkDevice();
		info.DescriptorPool = m_pDescriptorPool->GetVkDescriptorPool();
		info.ImageCount = MAX_FRAMES_IN_FLIGHT;
		info.MinImageCount = 2;
		info.MSAASamples = m_pDevice->GetMsaaSamples();
		info.Queue = m_pDevice->GetVkGraphicsQueue();

		ImGui_ImplVulkan_Init(&info, m_pSwapChain->GetVkRenderPass());

		VkCommandBuffer commandBuffer = m_pSwapChain->BeginSingleTimeCommands();
		ImGui_ImplVulkan_CreateFontsTexture(commandBuffer);
		m_pSwapChain->EndSingleTimeCommands(commandBuffer);

		vkDeviceWaitIdle(m_pDevice->GetVkDevice());
		ImGui_ImplVulkan_DestroyFontUploadObjects();
	}

	bool Renderer::BeginRender()
	{
		auto pPipeline = m_pPipeLines.at("main");

		return m_pSwapChain->BeginRecordCommandBuffer(pPipeline);
	}

	void Renderer::DrawModel(Model* pModel, u32 modelIndex)
	{
		auto pPipeline = m_pPipeLines.at("main");

		m_pSwapChain->BindModel(pModel);
		m_pSwapChain->DrawModel(pPipeline, pModel, modelIndex);
	}

	void Renderer::EndRender()
	{
		m_pSwapChain->EndRecordCommandBuffer();
	}
}
