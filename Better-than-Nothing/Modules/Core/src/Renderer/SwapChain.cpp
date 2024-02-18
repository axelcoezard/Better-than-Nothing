#include "BetterThanNothing.hpp"

#include <unordered_map>

namespace BetterThanNothing
{
	SwapChain::SwapChain(Window* window, Device* device, DescriptorPool* descriptorPool)
		: m_Window(window), m_Device(device), m_DescriptorPool(descriptorPool)
	{
		CreateSwapChain();

		RenderPassProperties renderPassProperties;
		renderPassProperties.device = m_Device;
		renderPassProperties.swapChain = this;
		renderPassProperties.swapChainFormat = &m_Format;
		renderPassProperties.swapChainExtent = &m_Extent;
		renderPassProperties.msaaSamples = m_Device->GetMsaaSamples();

		m_RenderPass = new RenderPass(renderPassProperties);
		m_RenderPass->Create();

#if ENABLE_IMGUI
		SetupImGui();
#endif

		CreateCommandBuffers();
		CreateSyncObjects();
	}

	SwapChain::~SwapChain()
	{
		auto device = m_Device->GetVkDevice();

		CleanupSwapChain();

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(device, m_ImageAvailableSemaphores[i], nullptr);
			vkDestroySemaphore(device, m_RenderFinishedSemaphores[i], nullptr);
			vkDestroyFence(device, m_InFlightFences[i], nullptr);
		}

#if ENABLE_IMGUI

		ImGui_ImplVulkan_DestroyFontsTexture();
		ImGui_ImplVulkan_Shutdown();
		delete m_ImGuiDescriptorPool;
#endif

		delete m_RenderPass;

		for (auto commandBuffer : m_CommandBuffers) {
			delete commandBuffer;
		}
	}

	void SwapChain::CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = m_Device->QuerySwapChainSupport(m_Device->GetVkPhysicalDevice());

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentationMode = ChooseSwapPresentMode(swapChainSupport.presentationModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);

		m_Format = surfaceFormat.format;
		m_Extent = extent;

		u32 imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_Device->GetVkSurface();
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = m_Device->FindQueueFamilies(m_Device->GetVkPhysicalDevice());
		u32 queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentationFamily.value() };

		if (indices.graphicsFamily != indices.presentationFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		} else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentationMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_Device->GetVkDevice(), &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(m_Device->GetVkDevice(), m_SwapChain, &imageCount, nullptr);
		m_Images.resize(imageCount);

		vkGetSwapchainImagesKHR(m_Device->GetVkDevice(), m_SwapChain, &imageCount, m_Images.data());
	}

	void SwapChain::CreateCommandBuffers()
	{
		m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_CommandBuffers[i] = new CommandBuffer(m_Device);
		}
	}

	void SwapChain::CreateSyncObjects()
	{
		m_ImageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_RenderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
		m_InFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		auto device = m_Device->GetVkDevice();
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(device, &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS) {

				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}

	void SwapChain::SetupImGui()
	{
#if ENABLE_IMGUI
		m_ImGuiDescriptorPool = new ImGuiDescriptorPool(m_Device);

		// Setup Dear ImGui context
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForVulkan(m_Window->GetPointer(), true);
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = m_Device->GetVkInstance();
		init_info.PhysicalDevice = m_Device->GetVkPhysicalDevice();
		init_info.Device = m_Device->GetVkDevice();
		init_info.DescriptorPool = m_ImGuiDescriptorPool->GetVkDescriptorPool();
		init_info.MinImageCount = 2;
		init_info.ImageCount = MAX_FRAMES_IN_FLIGHT;
		init_info.MSAASamples = m_Device->GetMsaaSamples();
		init_info.Queue = m_Device->GetVkGraphicsQueue();

		// Init Vulkan
		ImGui_ImplVulkan_Init(&init_info, m_RenderPass->GetVkRenderPass());

		// Upload Fonts
		ImGui_ImplVulkan_CreateFontsTexture();
#endif
	}

	void SwapChain::CleanupSwapChain()
	{
		auto device = m_Device->GetVkDevice();

		// TODO: Cleanup all RenderPasses resources
		m_RenderPass->CleanDependencies();

		vkDestroySwapchainKHR(device, m_SwapChain, nullptr);
	}

	void SwapChain::RecreateSwapChain()
	{
		auto window = m_Window->GetPointer();
		int width = 0, height = 0;

		glfwGetFramebufferSize(window, &width, &height);
		while (width == 0 || height == 0) {
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
		}

		m_Device->WaitIdle();

		CleanupSwapChain();
		CreateSwapChain();

		// TODO: Recreate all RenderPasses resources
		m_RenderPass->RecreateDependencies();
	}

	VkFormat SwapChain::FindDepthFormat()
	{
		return m_Device->FindSupportedFormat(
			{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}

	bool SwapChain::BeginRecordCommandBuffer()
	{
		CommandBuffer* commandBuffer = m_CommandBuffers[m_CurrentFrame];

		WaitForFences();
		VkResult result = AcquireNextImage();

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			RecreateSwapChain();
			return false;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		commandBuffer->Begin();

		// Begin default render pass;
		VkRenderPassBeginInfo renderPassInfo {};
		m_RenderPass->GetRenderPassBeginInfo(&renderPassInfo, m_CurrentImageIndex);
		commandBuffer->BeginRenderPass(renderPassInfo);

		// Prepare viewport and scissor
		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<f32>(m_Extent.width);
		viewport.height = static_cast<f32>(m_Extent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		commandBuffer->SetViewport(viewport);

		VkRect2D scissor{};
		scissor.offset = {0, 0};
		scissor.extent = m_Extent;
		commandBuffer->SetScissor(scissor);

		return true;
	}

	void SwapChain::BindPipeline(Pipeline* pipeline)
	{
		m_CommandBuffers[m_CurrentFrame]->BindPipeline(pipeline->GetVkGraphicsPipeline());
	}



	void SwapChain::Draw(DrawStream* drawStream)
	{
		CommandBuffer* commandBuffer = m_CommandBuffers[m_CurrentFrame];

		std::cout << " => VertexBuffers size: " << drawStream->vertexBuffers.size() << std::endl;
		commandBuffer->BindVertexBuffers(0, 1, drawStream->vertexBuffers.data(), drawStream->vertexOffsets.data());
		//commandBuffer->BindVertexBuffer(drawPacket->vertexBuffer.m_Buffer);

		u32 offset = 0;
		for (u32 i = 0; i < drawStream->size; i++)
		{
			std::cout << " => IndexBuffer size: " << drawStream->indexBuffers[i].m_Size << std::endl;
			commandBuffer->BindIndexBuffer(drawStream->indexBuffers[i].m_Buffer, 0);

			std::cout << " => DrawIndexed: " << drawStream->indicesCount << " offset: " << offset << std::endl;
			commandBuffer->DrawIndexed(drawStream->indicesCount, 1, offset, 0, 0); // TODO: fix vertex offset

			offset += drawStream->indicesCount;
		}

		//commandBuffer->BindDescriptorSets(
		//	m_DescriptorPool->GetVkDescriptorSets()[m_CurrentFrame][index],
		//	pipeline->GetVkPipelineLayout());

	}

	void SwapChain::EndRecordCommandBuffer()
	{
		CommandBuffer* commandBuffer = m_CommandBuffers[m_CurrentFrame];

#if ENABLE_IMGUI
		ImDrawData* draw_data = ImGui::GetDrawData();
		ImGui_ImplVulkan_RenderDrawData(draw_data, commandBuffer->GetVkCommandBuffer());
#endif

		commandBuffer->EndRenderPass();
		commandBuffer->End();

		ResetFences();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer->GetVkCommandBuffer();

		VkSemaphore waitSemaphores[] = {m_ImageAvailableSemaphores[m_CurrentFrame]};
		VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		VkSemaphore signalSemaphores[] = {m_RenderFinishedSemaphores[m_CurrentFrame]};
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(m_Device->GetVkGraphicsQueue(), 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS) {
			throw std::runtime_error("failed to submit draw command buffer!");
		}

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = {m_SwapChain};
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &m_CurrentImageIndex;
		presentInfo.pResults = nullptr;

		VkResult result = vkQueuePresentKHR(m_Device->GetVkPresentationQueue(), &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_Window->IsResized()) {
			m_Window->SetResized(false);
			RecreateSwapChain();
		} else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}

		NextFrame();
	}

	VkResult SwapChain::AcquireNextImage()
	{
		return vkAcquireNextImageKHR(
			m_Device->GetVkDevice(),
			m_SwapChain,
			UINT64_MAX,
			m_ImageAvailableSemaphores[m_CurrentFrame],
			VK_NULL_HANDLE,
			&m_CurrentImageIndex);
	}

	void SwapChain::WaitForFences()
	{
		vkWaitForFences(m_Device->GetVkDevice(), 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);
	}

	void SwapChain::ResetFences()
	{
		vkResetFences(m_Device->GetVkDevice(), 1, &m_InFlightFences[m_CurrentFrame]);
	}

	void SwapChain::NextFrame()
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	VkSurfaceFormatKHR SwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}
		return availableFormats[0];
	}

	VkPresentModeKHR SwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D SwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<u32>::max()) {
			return capabilities.currentExtent;
		}

		int width, height;
		glfwGetFramebufferSize(m_Window->GetPointer(), &width, &height);

		VkExtent2D actualExtent = { static_cast<u32>(width), static_cast<u32>(height)};
		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
		return actualExtent;
	}
};
