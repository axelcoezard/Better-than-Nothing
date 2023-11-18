#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	CommandBuffer::CommandBuffer(Device* device, CommandPool* commandPool): m_Device(device), m_CommandPool(commandPool)
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = m_CommandPool->GetVkCommandPool();
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(m_Device->GetVkDevice(), &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}

	CommandBuffer::~CommandBuffer()
	{
		vkFreeCommandBuffers(m_Device->GetVkDevice(), m_CommandPool->GetVkCommandPool(), 1, &m_CommandBuffer);
	}

	void CommandBuffer::Begin()
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		if (vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}
	}

	void CommandBuffer::End()
	{
		if (vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}

	void CommandBuffer::BeginRenderPass(VkRenderPassBeginInfo& renderPassBeginInfo)
	{
		vkCmdBeginRenderPass(m_CommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void CommandBuffer::SetViewport(VkViewport& viewport)
	{
		vkCmdSetViewport(m_CommandBuffer, 0, 1, &viewport);
	}

	void CommandBuffer::SetScissor(VkRect2D& scissor)
	{
		vkCmdSetScissor(m_CommandBuffer, 0, 1, &scissor);
	}

	void CommandBuffer::EndRenderPass()
	{
		vkCmdEndRenderPass(m_CommandBuffer);
	}

	void CommandBuffer::BindPipeline(VkPipeline& pipeline)
	{
		vkCmdBindPipeline(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
	}

	void CommandBuffer::BindVertexBuffer(VkBuffer& vertexBuffer)
	{
		VkBuffer vertexBuffers[] = {vertexBuffer};
		VkDeviceSize offsets[] = {0};
		vkCmdBindVertexBuffers(m_CommandBuffer, 0, 1, vertexBuffers, offsets);
	}

	void CommandBuffer::BindIndexBuffer(VkBuffer& indexBuffer)
	{
		vkCmdBindIndexBuffer(m_CommandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
	}

	void CommandBuffer::BindDescriptorSets(VkDescriptorSet& descriptorSet, VkPipelineLayout& pipelineLayout)
	{
		vkCmdBindDescriptorSets(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
	}

	void CommandBuffer::DrawIndexed(u32 indexCount)
	{
		vkCmdDrawIndexed(m_CommandBuffer, indexCount, 1, 0, 0, 0);
	}

	void CommandBuffer::CmdPipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkImageMemoryBarrier& imageMemoryBarriers)
	{
		vkCmdPipelineBarrier(m_CommandBuffer, srcStageMask, dstStageMask, 0, 0, nullptr, 0, nullptr, 1, &imageMemoryBarriers);
	}

	void CommandBuffer::CmdBlitImage(VkImage& srcImage, VkImage& dstImage, VkImageBlit& blit)
	{
		vkCmdBlitImage(m_CommandBuffer, srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &blit, VK_FILTER_LINEAR);
	}

	void CommandBuffer::CmdCopyBufferToImage(VkBuffer& buffer, VkImage& dstImage, VkImageLayout dstImageLayout, u32 regionCount, VkBufferImageCopy& regions)
	{
		vkCmdCopyBufferToImage(m_CommandBuffer, buffer, dstImage, dstImageLayout, regionCount, &regions);
	}

	void CommandBuffer::CmdCopyBuffer(VkBuffer& srcBuffer, VkBuffer& dstBuffer, u32 regionCount, VkBufferCopy& regions)
	{
		vkCmdCopyBuffer(m_CommandBuffer, srcBuffer, dstBuffer, regionCount, &regions);
	}

	void CommandBuffer::SingleTimeCommands(const std::function<void(CommandBuffer*)>& callback, Device* device, CommandPool* commandPool)
	{
		CommandBuffer* commandBuffer = new CommandBuffer(device, commandPool);
		commandBuffer->Begin();

		callback(commandBuffer);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer->GetVkCommandBuffer();

		commandBuffer->End();

		VkQueue graphicsQueue = device->GetVkGraphicsQueue();
		vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(graphicsQueue);

		delete commandBuffer;
	}
};
