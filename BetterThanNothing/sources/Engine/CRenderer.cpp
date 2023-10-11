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

	void CRenderer::DrawFrame()
	{
		auto pPipeline = m_pPipeLines.at("main");

		if (pPipeline == nullptr) {
			throw std::runtime_error("pipeline not found");
		}

		auto device = m_pDevice->GetVkDevice();
		auto currentFrame = m_pSwapChain->GetCurrentFrame();
		auto commandBuffer = m_pSwapChain->GetCurrentCommandBuffer();

		vkWaitForFences(device, 1, &m_pSwapChain->GetInFlightFences()[currentFrame], VK_TRUE, UINT64_MAX);

		VkResult result = m_pSwapChain->AcquireNextImage();

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			return (void) m_pSwapChain->RecreateSwapChain();
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		m_pSwapChain->UpdateUniformBuffer(currentFrame);

		vkResetFences(device, 1, &m_pSwapChain->GetInFlightFences()[currentFrame]);
		vkResetCommandBuffer(commandBuffer, 0);
		m_pSwapChain->StartRecordCommandBuffer(pPipeline, commandBuffer);

		for (auto & entry : m_pModels) {
			auto model = entry.second;

			model->Bind(commandBuffer);

			m_pDescriptorPool->UpdateDescriptorSets(model);

			vkCmdBindDescriptorSets(commandBuffer,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				pPipeline->GetVkPipelineLayout(), 0, 1,
				&m_pDescriptorPool->GetVkDescriptorSets()[currentFrame], 0, nullptr);

			model->Draw(commandBuffer);
		}

		m_pSwapChain->EndRecordCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		VkSemaphore waitSemaphores[] = {m_pSwapChain->GetImageAvailableSemaphores()[currentFrame]};
		VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		VkSemaphore signalSemaphores[] = {m_pSwapChain->GetRenderFinishedSemaphores()[currentFrame]};
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(m_pDevice->GetVkGraphicsQueue(), 1, &submitInfo, m_pSwapChain->GetInFlightFences()[currentFrame]) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = {m_pSwapChain->GetVkSwapChain()};
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &m_pSwapChain->GetCurrentImageIndex();
		presentInfo.pResults = nullptr;

		result = vkQueuePresentKHR(m_pDevice->GetVkPresentationQueue(), &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_pWindow->IsResized()) {
			m_pWindow->SetResized(false);
			m_pSwapChain->RecreateSwapChain();
		} else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}

		m_pSwapChain->SetCurrentFrame((currentFrame + 1) % MAX_FRAMES_IN_FLIGHT);
	}
}
