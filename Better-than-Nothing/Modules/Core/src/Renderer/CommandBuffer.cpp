#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	CommandBuffer::CommandBuffer(Device* device)
	{
		m_Device = device;
		m_CommandPool = device->GetCommandPool();

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
		std::vector<VkClearValue> clearValues(2);
		clearValues[0].color = {0.0f, 0.0f, 0.0f, 1.0f};
		clearValues[1].depthStencil = {1.0f, 0};

		renderPassBeginInfo.clearValueCount = static_cast<u32>(clearValues.size());
		renderPassBeginInfo.pClearValues = clearValues.data();

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
		BindVertexBuffers(0, 1, vertexBuffers, offsets);
	}

	void CommandBuffer::BindVertexBuffers(u32 firstBinding, u32 bindingCount, VkBuffer* vertexBuffers, VkDeviceSize* offsets)
	{
		vkCmdBindVertexBuffers(m_CommandBuffer, firstBinding, bindingCount, vertexBuffers, offsets);
	}

	void CommandBuffer::BindIndexBuffer(VkBuffer& indexBuffer)
	{
		BindIndexBuffer(indexBuffer, 0);
	}

	void CommandBuffer::BindIndexBuffer(VkBuffer& indexBuffer, VkDeviceSize offset)
	{
		vkCmdBindIndexBuffer(m_CommandBuffer, indexBuffer, offset, VK_INDEX_TYPE_UINT32);
	}

	void CommandBuffer::BindDescriptorSets(VkDescriptorSet& descriptorSet, VkPipelineLayout& pipelineLayout)
	{
		vkCmdBindDescriptorSets(m_CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
	}

	void CommandBuffer::DrawIndexed(u32 indexCount)
	{
		DrawIndexed(indexCount, 1, 0, 0, 0);
	}

	void CommandBuffer::DrawIndexed(u32 indexCount, u32 instanceCount, u32 firstIndex, u32 vertexOffset, u32 firstInstance)
	{
		vkCmdDrawIndexed(m_CommandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
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

	void CommandBuffer::SingleTimeCommands(const std::function<void(CommandBuffer*)>& callback, Device* device)
	{
		CommandBuffer* commandBuffer = new CommandBuffer(device);
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
