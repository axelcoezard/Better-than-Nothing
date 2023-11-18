#pragma once

namespace BetterThanNothing
{
	class Device;
	class CommandPool;

	class CommandBuffer
	{
	private:
		Device*				m_Device;
		CommandPool*	 	m_CommandPool;

		VkCommandBuffer		m_CommandBuffer { VK_NULL_HANDLE };
	public:
							CommandBuffer(Device* device, CommandPool* commandPool);
							~CommandBuffer();

							CommandBuffer(const CommandBuffer&) = delete;
		CommandBuffer&		operator=(const CommandBuffer&) = delete;
							CommandBuffer(CommandBuffer&&) = delete;
		CommandBuffer&		operator=(CommandBuffer&&) = delete;

	public:
		void				Begin();
		void				End();

		void				BeginRenderPass(VkRenderPassBeginInfo& renderPassBeginInfo);
		void				SetViewport(VkViewport& viewport);
		void				SetScissor(VkRect2D& scissor);
		void				EndRenderPass();

		void				BindPipeline(VkPipeline& pipeline);
		void				BindVertexBuffer(VkBuffer& vertexBuffer);
		void				BindIndexBuffer(VkBuffer& indexBuffer);
		void				BindDescriptorSets(VkDescriptorSet& descriptorSet, VkPipelineLayout& pipelineLayout);
		void				DrawIndexed(u32 indexCount);

		void				CmdPipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkImageMemoryBarrier& imageMemoryBarriers);
		void				CmdBlitImage(VkImage& srcImage, VkImage& dstImage, VkImageBlit& blit);
		void				CmdCopyBufferToImage(VkBuffer& buffer, VkImage& dstImage, VkImageLayout dstImageLayout, u32 regionCount, VkBufferImageCopy& regions);
		void				CmdCopyBuffer(VkBuffer& srcBuffer, VkBuffer& dstBuffer, u32 regionCount, VkBufferCopy& regions);

		static void			SingleTimeCommands(const std::function<void(CommandBuffer*)>& callback, Device* device, CommandPool* commandPool);

	public:
		VkCommandBuffer&	GetVkCommandBuffer()	{ return m_CommandBuffer; }
	};
};
