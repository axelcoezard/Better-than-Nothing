#include "CWindow.hpp"
#include "CDevice.hpp"
#include "CSwapChain.hpp"
#include "CTexture.hpp"
#include "CPipeline.hpp"
#include "CVertex.hpp"
#include "CUniformBufferObject.hpp"
#include "CCommandPool.hpp"
#include "CDescriptorPool.hpp"
#include "CModel.hpp"
#include "Scene/CScene.hpp"
#include "Scene/CCamera.hpp"

#include <unordered_map>

namespace BetterThanNothing
{
	CSwapChain::CSwapChain(CWindow* pWindow, CDevice* pDevice, CCommandPool* pCommandPool)
		: m_pWindow(pWindow), m_pDevice(pDevice), m_pCommandPool(pCommandPool)
	{
		CreateSwapChain();
		CreateImageViews();

		CreateColorResources();
		CreateDepthResources();

		CreateRenderPass();
		CreateFramebuffers();
		CreateSyncObjects();
	}

	CSwapChain::~CSwapChain()
	{
		auto device = m_pDevice->GetVkDevice();

		CleanupSwapChain();

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(device, m_ImageAvailableSemaphores[i], nullptr);
			vkDestroySemaphore(device, m_RenderFinishedSemaphores[i], nullptr);
			vkDestroyFence(device, m_InFlightFences[i], nullptr);
		}

		vkDestroyRenderPass(device, m_RenderPass, nullptr);

		vkFreeCommandBuffers(
			m_pDevice->GetVkDevice(),
			m_pCommandPool->GetVkCommandPool(),
			m_CommandBuffers.size(),
			m_CommandBuffers.data());

		for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			for (uint32_t j = 0; j < m_UniformBuffers[i].size(); j++) {
				if (m_UniformBuffers[i][j] != VK_NULL_HANDLE) {
					vkDestroyBuffer(device, m_UniformBuffers[i][j], nullptr);
				}
				vkFreeMemory(device, m_UniformBuffersMemory[i][j], nullptr);
			}
		}
	}

	void CSwapChain::CreateSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = m_pDevice->QuerySwapChainSupport(m_pDevice->GetVkPhysicalDevice());

		VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.m_Formats);
		VkPresentModeKHR presentationMode = ChooseSwapPresentMode(swapChainSupport.m_PresentationModes);
		VkExtent2D extent = ChooseSwapExtent(swapChainSupport.m_Capabilities);

		m_Format = surfaceFormat.format;
		m_Extent = extent;

		uint32_t imageCount = swapChainSupport.m_Capabilities.minImageCount + 1;
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
		uint32_t queueFamilyIndices[] = { indices.m_GraphicsFamily.value(), indices.m_PresentationFamily.value() };

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

	void CSwapChain::CreateImageViews()
	{
		m_ImageViews.resize(m_Images.size());

		for (size_t i = 0; i < m_Images.size(); i++) {
			m_ImageViews[i] = CreateImageView(m_Images[i], m_Format, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		}
	}

	void CSwapChain::CreateDepthResources()
	{
		VkFormat depthFormat = FindDepthFormat();

		CTexture::CreateImage(
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
		CTexture::TransitionImageLayout(this, m_DepthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
	}

	void CSwapChain::CreateColorResources()
	{
		VkFormat colorFormat = m_Format;

		CTexture::CreateImage(
			m_pDevice,
			m_Extent.width, m_Extent.height, 1,
			m_pDevice->GetMsaaSamples(), colorFormat,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_ColorImage, m_ColorImageMemory);

		m_ColorImageView = CreateImageView(m_ColorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
	}

	void CSwapChain::CreateRenderPass()
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
		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(m_pDevice->GetVkDevice(), &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS) {
			throw std::runtime_error("failed to create render pass!");
		}
	}

	VkImageView CSwapChain::CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels)
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

	void CSwapChain::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
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

	VkCommandBuffer CSwapChain::BeginSingleTimeCommands()
	{
		auto device = m_pDevice->GetVkDevice();
		auto commandPool = m_pCommandPool->GetVkCommandPool();

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);
		return commandBuffer;
	}

	void CSwapChain::EndSingleTimeCommands(VkCommandBuffer& commandBuffer)
	{
		auto device = m_pDevice->GetVkDevice();
		auto graphicsQueue = m_pDevice->GetVkGraphicsQueue();
		auto commandPool = m_pCommandPool->GetVkCommandPool();

		vkEndCommandBuffer(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(graphicsQueue);

		vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
	}

	void CSwapChain::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
	{
		VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
		{
			VkBufferCopy copyRegion{};
			copyRegion.size = size;
			vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
		}
		EndSingleTimeCommands(commandBuffer);
	}

	void CSwapChain::CreateUniformBuffers(CScene* pScene)
	{
		VkDeviceSize bufferSize = sizeof(CUniformBufferObject);

		m_UniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
		m_UniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

		auto modelCount = pScene->GetModels().size();
		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			m_UniformBuffers[i].resize(modelCount);
			m_UniformBuffersMemory[i].resize(modelCount);
			m_UniformBuffersMapped[i].resize(modelCount);

			for (size_t j = 0; j < modelCount; j++) {
				CreateBuffer(bufferSize,
					VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
					VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
					m_UniformBuffers[i][j],
					m_UniformBuffersMemory[i][j]);

				vkMapMemory(m_pDevice->GetVkDevice(),
					m_UniformBuffersMemory[i][j], 0,
					bufferSize, 0,
					&m_UniformBuffersMapped[i][j]);
			}
		}
	}

	void CSwapChain::CreateCommandBuffers()
	{
		m_CommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_pCommandPool->GetVkCommandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = m_CommandBuffers.size();

		if (vkAllocateCommandBuffers(m_pDevice->GetVkDevice(), &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}

	void CSwapChain::CreateSyncObjects()
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

	void CSwapChain::CreateFramebuffers()
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
			framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = m_Extent.width;
			framebufferInfo.height = m_Extent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_pDevice->GetVkDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}

	void CSwapChain::CleanupSwapChain()
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

	void CSwapChain::RecreateSwapChain()
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

	VkFormat CSwapChain::FindDepthFormat()
	{
		return m_pDevice->FindSupportedFormat(
			{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
	}

	bool CSwapChain::HasStencilComponent(VkFormat format)
	{
		return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
	}

	void CSwapChain::BindDescriptorPool(CDescriptorPool* pDescriptorPool)
	{
		m_pDescriptorPool = pDescriptorPool;
	}

	bool CSwapChain::BeginRecordCommandBuffer(CPipeline* pPipeline, CScene* pScene)
	{
		auto commandBuffer = m_CommandBuffers[m_CurrentFrame];

		WaitForFences();
		VkResult result = AcquireNextImage();

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			RecreateSwapChain();
			return false;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		// Old Uniform Buffer Object (UBO) update place
		for (size_t i = 0; i < pScene->GetModels().size(); i++) {
			UpdateUniformBuffer(pScene, pScene->GetModels()[i], i);
		}

		ResetFences();
		vkResetCommandBuffer(commandBuffer, 0);

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_RenderPass;
		renderPassInfo.framebuffer = m_Framebuffers[m_CurrentImageIndex];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = m_Extent;

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
		clearValues[1].depthStencil = {1.0f, 0};

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pPipeline->GetVkGraphicsPipeline());

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(m_Extent.width);
		viewport.height = static_cast<float>(m_Extent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = {0, 0};
		scissor.extent = m_Extent;
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
		return true;
	}

	void CSwapChain::UpdateUniformBuffer(CScene* pScene, CModel* pModel, int modelIndex)
	{
		CUniformBufferObject ubo{};

		// move all those calculus to shader
		ubo.m_Model = glm::mat4(1.0f);
		ubo.m_Model = glm::scale(ubo.m_Model, glm::vec3(pModel->GetScale()));
		ubo.m_Model = glm::translate(ubo.m_Model, pModel->GetPosition());
		ubo.m_Model = glm::rotate(ubo.m_Model, glm::radians(pModel->GetRotation().x), glm::vec3(1.0f, 0.0f, 0.0f));
		ubo.m_Model = glm::rotate(ubo.m_Model, glm::radians(pModel->GetRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
		ubo.m_Model = glm::rotate(ubo.m_Model, glm::radians(pModel->GetRotation().z), glm::vec3(0.0f, 0.0f, 1.0f));

		ubo.m_View = pScene->GetCamera()->GetViewMatrix();
		ubo.m_Projection = pScene->GetCamera()->GetProjectionMatrix();

		memcpy(m_UniformBuffersMapped[m_CurrentFrame][modelIndex], &ubo, sizeof(ubo));
	}

	void CSwapChain::BindModel(CModel* pModel)
	{
		auto commandBuffer = m_CommandBuffers[m_CurrentFrame];

		VkBuffer vertexBuffers[] = {pModel->GetVertexBuffer()};
		VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
		vkCmdBindIndexBuffer(commandBuffer, pModel->GetIndexBuffer(), 0, VK_INDEX_TYPE_UINT32);
	}

	void CSwapChain::DrawModel(CPipeline* pPipeline, CModel* pModel, int modelIndex)
	{
		auto commandBuffer = m_CommandBuffers[m_CurrentFrame];

		vkCmdBindDescriptorSets(commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pPipeline->GetVkPipelineLayout(), 0, 1,
			&m_pDescriptorPool->GetVkDescriptorSets()[m_CurrentFrame][modelIndex], 0, nullptr);

		vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(pModel->GetIndicesCount()), 1, 0, 0, 0);
	}

	void CSwapChain::EndRecordCommandBuffer()
	{
		auto commandBuffer = m_CommandBuffers[m_CurrentFrame];

		vkCmdEndRenderPass(commandBuffer);

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

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

	VkResult CSwapChain::AcquireNextImage()
	{
		return vkAcquireNextImageKHR(
			m_pDevice->GetVkDevice(),
			m_SwapChain,
			UINT64_MAX,
			m_ImageAvailableSemaphores[m_CurrentFrame],
			VK_NULL_HANDLE,
			&m_CurrentImageIndex);
	}

	void CSwapChain::WaitForFences()
	{
		vkWaitForFences(m_pDevice->GetVkDevice(), 1, &m_InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);
	}

	void CSwapChain::ResetFences()
	{
		vkResetFences(m_pDevice->GetVkDevice(), 1, &m_InFlightFences[m_CurrentFrame]);
	}

	void CSwapChain::NextFrame()
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	VkSurfaceFormatKHR CSwapChain::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}
		return availableFormats[0];
	}

	VkPresentModeKHR CSwapChain::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
				return availablePresentMode;
			}
		}
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D CSwapChain::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
			return capabilities.currentExtent;
		}

		int width, height;
		glfwGetFramebufferSize(m_pWindow->GetPointer(), &width, &height);

		VkExtent2D actualExtent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
		return actualExtent;
	}
};
