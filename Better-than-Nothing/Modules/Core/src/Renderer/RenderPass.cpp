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
		LOG_INFO("Creating RenderPass image views...");
		std::vector<VkImage> m_Images = m_Properties.swapChain->GetImages();

		LOG_INFO("=> images count: " + std::to_string(m_Images.size()));

		m_ImageViews.clear();
		m_ImageViews.resize(m_Images.size());

		for (size_t i = 0; i < m_Images.size(); i++) {
			m_ImageViews[i] = m_Properties.device->CreateImageView(
				m_Images[i],
				m_Properties.swapChainFormat,
				VK_IMAGE_ASPECT_COLOR_BIT, 1);
		}
	}

	void RenderPass::CreateResources()
	{
		if (m_Properties.attachmentTypeFlags & RENDER_PASS_ATTACHMENT_TYPE_COLOR) {
			CreateColorResources();
		}

		if (m_Properties.attachmentTypeFlags & RENDER_PASS_ATTACHMENT_TYPE_DEPTH) {
			CreateDepthResources();
		}
	}

	void RenderPass::CreateColorResources()
	{
		LOG_INFO("Creating RenderPass color resources...");
		VkFormat colorFormat = m_Properties.swapChainFormat;

		m_Properties.device->CreateImage(
			m_Properties.swapChainExtent.width,
			m_Properties.swapChainExtent.height, 1,
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
		LOG_INFO("Creating RenderPass depth resources...");
		VkFormat depthFormat = m_Properties.swapChain->FindDepthFormat();

		m_Properties.device->CreateImage(
			m_Properties.swapChainExtent.width,
			m_Properties.swapChainExtent.height, 1,
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
		LOG_INFO("Creating RenderPass framebuffers...");
		m_Framebuffers.resize(m_ImageViews.size());

		for (u32 i = 0; i < m_ImageViews.size(); i++) {
			std::vector<VkImageView> attachments;

			if (m_Properties.attachmentTypeFlags & RENDER_PASS_ATTACHMENT_TYPE_COLOR) {
				LOG_INFO("=> Adding color image view to framebuffer attachments...");
				attachments.push_back(m_ColorImageView);
			}

			if (m_Properties.attachmentTypeFlags & RENDER_PASS_ATTACHMENT_TYPE_DEPTH) {
				LOG_INFO("=> Adding depth image view to framebuffer attachments...");
				attachments.push_back(m_DepthImageView);
			}

			attachments.push_back(m_ImageViews[i]);

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_RenderPass;
			framebufferInfo.attachmentCount = static_cast<u32>(attachments.size());
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = m_Properties.swapChainExtent.width;
			framebufferInfo.height = m_Properties.swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_Properties.device->GetVkDevice(), &framebufferInfo, nullptr, &m_Framebuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to create framebuffer!");
			}
		}
	}

	void RenderPass::CleanDependencies()
	{
		LOG_INFO("Cleaning RenderPass dependencies...");
		VkDevice device = m_Properties.device->GetVkDevice();

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
	}

	void RenderPass::RecreateDependencies()
	{
		LOG_INFO("Recreating RenderPass dependencies...");
		CreateImageViews();
		CreateResources();
		CreateFramebuffers();
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