#include "BetterThanNothing.hpp"

#include <unordered_map>

namespace BetterThanNothing
{
	SwapChain::SwapChain(Window* pWindow, Device* pDevice, CommandPool* pCommandPool)
		: m_pWindow(pWindow), m_pDevice(pDevice), m_pCommandPool(pCommandPool)
	{
		CreateSwapChain();
		CreateImageViews();

		CreateColorResources();
		CreateDepthResources();

		CreateRenderPass();
		CreateFramebuffers();
		CreateCommandBuffers();
		CreateSyncObjects();

		m_UniformBuffersSize = 0;
		m_UniformBuffersCapacity = 1000;

		m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_UniformBuffers[i].resize(m_UniformBuffersCapacity);
			m_UniformBuffersMemory[i].resize(m_UniformBuffersCapacity);
			m_UniformBuffersMapped[i].resize(m_UniformBuffersCapacity);
		}
	}

	SwapChain::~SwapChain()
	{
		auto device = m_pDevice->GetVkDevice();

		CleanupSwapChain();

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(device, m_ImageAvailableSemaphores[i], nullptr);
			vkDestroySemaphore(device, m_RenderFinishedSemaphores[i], nullptr);
			vkDestroyFence(device, m_InFlightFences[i], nullptr);
		}

		vkDestroyRenderPass(device, m_RenderPass, nullptr);

		for (auto commandBuffer : m_CommandBuffers) {
			delete commandBuffer;
		}

		DestroyUniformBuffers();
	}

	void SwapChain::CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = m_pDevice->QuerySwapChainSupport(m_pDevice->GetVkPhysicalDevice());

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.m_Formats);
		VkPresentModeKHR presentationMode = ChooseSwapPresentMode(swapChainSupport.m_PresentationModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.m_Capabilities);

		m_Format = surfaceFormat.format;
		m_Extent = extent;

		u32 imageCount = swapChainSupport.m_Capabilities.minImageCount + 1;
		if (swapChainSupport.m_Capabilities.maxImageCount > 0 && imageCount > swapChainSupport.m_Capabilities.maxImageCount) {
			imageCount = swapChainSupport.m_Capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_pDevice->GetVkSurface();
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = m_pDevice->FindQueueFamilies(m_pDevice->GetVkPhysicalDevice());
		u32 queueFamilyIndices[] = { indices.m_GraphicsFamily.value(), indices.m_PresentationFamily.value() };

		if (indices.m_GraphicsFamily != indices.m_PresentationFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		} else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.m_Capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentationMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_pDevice->GetVkDevice(), &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS) {
			throw std::runtime_error("failed to create swap chain!");
		}

		vkGetSwapchainImagesKHR(m_pDevice->GetVkDevice(), m_SwapChain, &imageCount, nullptr);
		m_Images.resize(imageCount);

		vkGetSwapchainImagesKHR(m_pDevice->GetVkDevice(), m_SwapChain, &imageCount, m_Images.data());
	}

	void SwapChain::CreateImageViews()
	{
		m_ImageViews.resize(m_Images.size());

		for (size_t i = 0; i < m_Images.size(); i++) {
			m_ImageViews[i] = CreateImageView(m_Images[i], m_Format, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		}
	}

	void SwapChain::CreateDepthResources()
	{
		VkFormat depthFormat = FindDepthFormat();

		TexturePool::CreateImage(
			m_pDevice,
			m_Extent.width, m_Extent.height, 1,
			m_pDevice->GetMsaaSamples(),
			depthFormat,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_DepthImage,
			m_DepthImageMemory);

		m_DepthImageView = CreateImageView(m_DepthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
		TexturePool::TransitionImageLayout(m_DepthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1, m_pDevice, m_pCommandPool);
	}

	void SwapChain::CreateColorResources()
	{
		VkFormat colorFormat = m_Format;

		TexturePool::CreateImage(
			m_pDevice,
			m_Extent.width, m_Extent.height, 1,
			m_pDevice->GetMsaaSamples(), colorFormat,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_ColorImage, m_ColorImageMemory);

		m_ColorImageView = CreateImageView(m_ColorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
	}

	void SwapChain::CreateRenderPass()
	{
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = m_Format;
		colorAttachment.samples = m_pDevice->GetMsaaSamples();
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		 VkAttachmentDescription colorAttachmentResolve{};
		colorAttachmentResolve.format = m_Format;
		colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentReference colorAttachmentResolveRef{};
		colorAttachmentResolveRef.attachment = 2;
		colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkAttachmentDescription depthAttachment{};
		depthAttachment.format = FindDepthFormat();
		depthAttachment.samples = m_pDevice->GetMsaaSamples();
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depthAttachmentRef{};
		depthAttachmentRef.attachment = 1;
		depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;
		subpass.pResolveAttachments = &colorAttachmentResolveRef;

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcAccessMask = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		std::array<VkAttachmentDescription, 3> attachments = {
			colorAttachment, depthAttachment, colorAttachmentResolve
		};

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = static_cast<u32>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(m_pDevice->GetVkDevice(), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS) {
			throw std::runtime_error("failed to create render pass!");
		}
	}

	VkImageView SwapChain::CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, u32 mipLevels)
	{
		VkImageViewCreateInfo viewInfo{};
		viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		viewInfo.image = image;
		viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		viewInfo.format = format;
		viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		viewInfo.subresourceRange.aspectMask = aspectFlags;
		viewInfo.subresourceRange.baseMipLevel = 0;
		viewInfo.subresourceRange.levelCount = 1;
		viewInfo.subresourceRange.baseArrayLayer = 0;
		viewInfo.subresourceRange.layerCount = 1;
		viewInfo.subresourceRange.levelCount = mipLevels;

		VkImageView imageView;
		if (vkCreateImageView(m_pDevice->GetVkDevice(), &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
			throw std::runtime_error("failed to create texture image view!");
		}

		return imageView;
	}

	void SwapChain::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
	{
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		auto device = m_pDevice->GetVkDevice();
		if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to create vertex buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = m_pDevice->FindMemoryType(memRequirements.memoryTypeBits, properties);

		if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(device, buffer, bufferMemory, 0);
	}

	void SwapChain::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
	{
		CommandBuffer::SingleTimeCommands([&](CommandBuffer* commandBuffer) {
			VkBufferCopy copyRegion{};
			copyRegion.size = size;
			commandBuffer->CmdCopyBuffer(srcBuffer, dstBuffer, 1, copyRegion);
		}, m_pDevice, m_pCommandPool);
	}

	void SwapChain::CreateNewUniformBuffer()
	{
		VkDeviceSize bufferSize = sizeof(UniformBufferObject);

		if (m_UniformBuffersSize >= m_UniformBuffersCapacity) {
			m_UniformBuffersCapacity *= 2;

			for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
				m_UniformBuffers[i].resize(m_UniformBuffersCapacity);
				m_UniformBuffersMemory[i].resize(m_UniformBuffersCapacity);
				m_UniformBuffersMapped[i].resize(m_UniformBuffersCapacity);
			}
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			CreateBuffer(bufferSize,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
				m_UniformBuffers[i][m_UniformBuffersSize],
				m_UniformBuffersMemory[i][m_UniformBuffersSize]);

			vkMapMemory(m_pDevice->GetVkDevice(),
				m_UniformBuffersMemory[i][m_UniformBuffersSize], 0,
				bufferSize, 0,
				&m_UniformBuffersMapped[i][m_UniformBuffersSize]);
		}

		m_UniformBuffersSize += 1;
	}

	void SwapChain::DestroyUniformBuffers()
	{
		auto device = m_pDevice->GetVkDevice();

		if (m_UniformBuffers.size() < MAX_FRAMES_IN_FLIGHT || m_UniformBuffersMemory.size() < MAX_FRAMES_IN_FLIGHT) {
			return;
		}

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			for (size_t j = 0; j < m_UniformBuffers[i].size(); j++) {
				if (m_UniformBuffers[i][j] != VK_NULL_HANDLE) {
					vkDestroyBuffer(device, m_UniformBuffers[i][j], nullptr);
				}
			}

			for (size_t j = 0; j < m_UniformBuffersMemory[i].size(); j++) {
				vkFreeMemory(device, m_UniformBuffersMemory[i][j], nullptr);
			}
		}
	}

	void SwapChain::CreateCommandBuffers()
	{
		m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_CommandBuffers[i] = new CommandBuffer(m_pDevice, m_pCommandPool);
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

		auto device = m_pDevice->GetVkDevice();
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(device, &fenceInfo, nullptr, &m_InFlightFences[i]) != VK_SUCCESS) {

				throw std::runtime_error("failed to create synchronization objects for a frame!");
			}
		}
	}

	void SwapChain::CreateFramebuffers()
	{
		m_Framebuffers.resize(m_ImageViews.size());

		for (size_t i = 0; i < m_ImageViews.size(); i++) {
			std::array<VkImageView, 3> attachments = {
				m_ColorImageView,
				m_DepthImageView,
				m_ImageViews[i]
			};

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_RenderPass;
			framebufferInfo.attachmentCount = static_cast<u32>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = m_Extent.width;
			framebufferInfo.height = m_Extent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_pDevice->GetVkDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}

	void SwapChain::CleanupSwapChain()
	{
		auto device = m_pDevice->GetVkDevice();

		vkDestroyImageView(device, m_DepthImageView, nullptr);
		vkDestroyImage(device, m_DepthImage, nullptr);
		vkFreeMemory(device, m_DepthImageMemory, nullptr);

		vkDestroyImageView(device, m_ColorImageView, nullptr);
		vkDestroyImage(device, m_ColorImage, nullptr);
		vkFreeMemory(device, m_ColorImageMemory, nullptr);

		for (auto framebuffer : m_Framebuffers) {
			vkDestroyFramebuffer(device, framebuffer, nullptr);
		}

		for (auto imageView : m_ImageViews) {
			vkDestroyImageView(device, imageView, nullptr);
		}

		vkDestroySwapchainKHR(device, m_SwapChain, nullptr);
	}

	void SwapChain::RecreateSwapChain()
	{
		auto window = m_pWindow->GetPointer();
		int width = 0, height = 0;

		glfwGetFramebufferSize(window, &width, &height);
		while (width == 0 || height == 0) {
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(m_pDevice->GetVkDevice());

		CleanupSwapChain();

		CreateSwapChain();
		CreateImageViews();
		CreateColorResources();
		CreateDepthResources();
		CreateFramebuffers();
	}

	VkFormat SwapChain::FindDepthFormat()
	{
		return m_pDevice->FindSupportedFormat(
			{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}

	void SwapChain::BindDescriptorPool(DescriptorPool* pDescriptorPool)
	{
		m_pDescriptorPool = pDescriptorPool;
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

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_RenderPass;
		renderPassInfo.framebuffer = m_Framebuffers[m_CurrentImageIndex];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = m_Extent;

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
		clearValues[1].depthStencil = {1.0f, 0};

		renderPassInfo.clearValueCount = static_cast<u32>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		commandBuffer->BeginRenderPass(renderPassInfo);

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

	void SwapChain::BindPipeline(Pipeline* pPipeline)
	{
		m_CommandBuffers[m_CurrentFrame]->BindPipeline(pPipeline->GetVkGraphicsPipeline());
	}

	void SwapChain::Draw(GlobalUniforms* globalUniforms, DrawPacket* pDrawPacket, u32 index)
	{
		auto commandBuffer = m_CommandBuffers[m_CurrentFrame];
		auto pPipeline = static_cast<Pipeline*>(pDrawPacket->pipeline);

		// Update the uniform buffer
		UniformBufferObject ubo = {
			.model = pDrawPacket->model,
			.view = globalUniforms->view,
			.projection = globalUniforms->projection
		};

		memcpy(m_UniformBuffersMapped[m_CurrentFrame][index], &ubo, sizeof(ubo));

		commandBuffer->BindVertexBuffer(pDrawPacket->vertexBuffer);
		commandBuffer->BindIndexBuffer(pDrawPacket->indexBuffer);

		commandBuffer->BindDescriptorSets(
			m_pDescriptorPool->GetVkDescriptorSets()[m_CurrentFrame][index],
			pPipeline->GetVkPipelineLayout());

		commandBuffer->DrawIndexed(pDrawPacket->indicesCount);
	}

	void SwapChain::EndRecordCommandBuffer()
	{
		CommandBuffer* commandBuffer = m_CommandBuffers[m_CurrentFrame];

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

		if (vkQueueSubmit(m_pDevice->GetVkGraphicsQueue(), 1, &submitInfo, m_InFlightFences[m_CurrentFrame]) != VK_SUCCESS) {
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

		VkResult result = vkQueuePresentKHR(m_pDevice->GetVkPresentationQueue(), &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || m_pWindow->IsResized()) {
			m_pWindow->SetResized(false);
			RecreateSwapChain();
		} else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}

		NextFrame();
	}

	VkResult SwapChain::AcquireNextImage()
	{
		return vkAcquireNextImageKHR(
			m_pDevice->GetVkDevice(),
			m_SwapChain,
			UINT64_MAX,
			m_ImageAvailableSemaphores[m_CurrentFrame],
			VK_NULL_HANDLE,
			&m_CurrentImageIndex);
	}

	void SwapChain::WaitForFences()
	{
		vkWaitForFences(m_pDevice->GetVkDevice(), 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);
	}

	void SwapChain::ResetFences()
	{
		vkResetFences(m_pDevice->GetVkDevice(), 1, &m_InFlightFences[m_CurrentFrame]);
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
		glfwGetFramebufferSize(m_pWindow->GetPointer(), &width, &height);

		VkExtent2D actualExtent = { static_cast<u32>(width), static_cast<u32>(height)};
		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
		return actualExtent;
	}
};