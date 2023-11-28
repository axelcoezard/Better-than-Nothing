#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	void ImGuiRenderPass::CreateRenderPass()
	{
		VkAttachmentDescription attachment = {};
		attachment.format = m_Properties.swapChainFormat;
		attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; // Modified: Changed from VK_ATTACHMENT_LOAD_OP_LOAD
		attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED; // Modified: Changed from VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference color_attachment = {};
		color_attachment.attachment = 0;
		color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_attachment;

		VkRenderPassCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = 1;
		info.pAttachments = &attachment;
		info.subpassCount = 1;
		info.pSubpasses = &subpass;

		if (vkCreateRenderPass(m_Properties.device->GetVkDevice(), &info, nullptr, &m_RenderPass) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create ImGui render pass");
		}
	}

	void ImGuiRenderPass::GetRenderPassBeginInfo(VkRenderPassBeginInfo* renderPassInfo, u32 index)
	{
		renderPassInfo->sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo->renderPass = m_RenderPass;
		renderPassInfo->framebuffer = m_Framebuffers[index];
		renderPassInfo->renderArea.offset = {0, 0};
		renderPassInfo->renderArea.extent = m_Properties.swapChainExtent;
	}
};
