#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	RenderPass::~RenderPass()
	{
		VkDevice device = m_Properties.device->GetVkDevice();

		CleanDependencies();
		vkDestroyRenderPass(device, m_RenderPass, nullptr);
	}

	void RenderPass::Create()
	{
		CreateImageViews();
		CreateResources();
		CreateRenderPass();
		CreateFramebuffers();
	}

	void RenderPass::CreateImageViews()
	{
		std::vector<VkImage> m_Images = m_Properties.swapChain->GetImages();

		m_ImageViews.resize(m_Images.size());

		for (size_t i = 0; i < m_Images.size(); i++) {
			m_ImageViews[i] = m_Properties.device->CreateImageView(
				m_Images[i],
				*m_Properties.swapChainFormat,
				VK_IMAGE_ASPECT_COLOR_BIT, 1);
		}
	}

	void RenderPass::CreateResources()
	{
		CreateColorResources();
		CreateDepthResources();
	}

	void RenderPass::CreateColorResources()
	{
		VkFormat colorFormat = *m_Properties.swapChainFormat;

		m_Properties.device->CreateImage(
			m_Properties.swapChainExtent->width,
			m_Properties.swapChainExtent->height, 1,
			m_Properties.msaaSamples,
			colorFormat,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_ColorImage, m_ColorImageMemory);

		m_ColorImageView = m_Properties.device->CreateImageView(
			m_ColorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
	}

	void RenderPass::CreateDepthResources()
	{
		VkFormat depthFormat = m_Properties.swapChain->FindDepthFormat();

		m_Properties.device->CreateImage(
			m_Properties.swapChainExtent->width,
			m_Properties.swapChainExtent->height, 1,
			m_Properties.msaaSamples,
			depthFormat,
			VK_IMAGE_TILING_OPTIMAL,
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			m_DepthImage,
			m_DepthImageMemory);

		m_DepthImageView = m_Properties.device->CreateImageView(
			m_DepthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);

		m_Properties.device->TransitionImageLayout(
			m_DepthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
	}

	void RenderPass::CreateFramebuffers()
	{
		m_Framebuffers.resize(m_ImageViews.size());

		for (u32 i = 0; i < m_ImageViews.size(); i++)
		{
			std::vector<VkImageView> attachments;
			attachments.push_back(m_ColorImageView);
			attachments.push_back(m_DepthImageView);
			attachments.push_back(m_ImageViews[i]);

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_RenderPass;
			framebufferInfo.attachmentCount = static_cast<u32>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = m_Properties.swapChainExtent->width;
			framebufferInfo.height = m_Properties.swapChainExtent->height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_Properties.device->GetVkDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}

	void RenderPass::CleanDependencies()
	{
		VkDevice device = m_Properties.device->GetVkDevice();

		vkDestroyImageView(device, m_ColorImageView, nullptr);
		vkDestroyImage(device, m_ColorImage, nullptr);
		vkFreeMemory(device, m_ColorImageMemory, nullptr);

		vkDestroyImageView(device, m_DepthImageView, nullptr);
		vkDestroyImage(device, m_DepthImage, nullptr);
		vkFreeMemory(device, m_DepthImageMemory, nullptr);

		for (auto framebuffer : m_Framebuffers) {
			if (framebuffer != VK_NULL_HANDLE) {
				vkDestroyFramebuffer(device, framebuffer, nullptr);
			}
		}

		for (auto imageView : m_ImageViews) {
			if (imageView != VK_NULL_HANDLE) {
				vkDestroyImageView(device, imageView, nullptr);
			}
		}
	}

	void RenderPass::RecreateDependencies()
	{
		CreateImageViews();
		CreateResources();
		CreateFramebuffers();
	}

	void RenderPass::CreateRenderPass()
	{
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = *m_Properties.swapChainFormat;
		colorAttachment.samples = m_Properties.msaaSamples;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

		VkAttachmentDescription colorAttachmentResolve{};
		colorAttachmentResolve.format = *m_Properties.swapChainFormat;
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
		depthAttachment.format = m_Properties.swapChain->FindDepthFormat();
		depthAttachment.samples = m_Properties.msaaSamples;
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

		VkRenderPassCreateInfo info{};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = static_cast<u32>(attachments.size());
		info.pAttachments = attachments.data();
		info.subpassCount = 1;
		info.pSubpasses = &subpass;
		info.dependencyCount = 1;
		info.pDependencies = &dependency;

		if (vkCreateRenderPass(m_Properties.device->GetVkDevice(), &info, nullptr, &m_RenderPass) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create ImGui render pass");
		}
	}

	void RenderPass::GetRenderPassBeginInfo(VkRenderPassBeginInfo* renderPassInfo, u32 index)
	{
		renderPassInfo->sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo->renderPass = m_RenderPass;
		renderPassInfo->framebuffer = m_Framebuffers[index];
		renderPassInfo->renderArea.offset = {0, 0};
		renderPassInfo->renderArea.extent = *m_Properties.swapChainExtent;
	}

	VkImageView& RenderPass::GetDepthImageView()
	{
		return m_DepthImageView;
	}

	VkImageView& RenderPass::GetColorImageView()
	{
		return m_ColorImageView;
	}

	VkImageView& RenderPass::GetImageView(u32 index)
	{
		return m_ImageViews[index];
	}

	VkFramebuffer& RenderPass::GetFramebuffer(u32 index)
	{
		return m_Framebuffers[index];
	}

	VkRenderPass& RenderPass::GetVkRenderPass()
	{
		return m_RenderPass;
	}
};
