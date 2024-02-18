#pragma once

namespace BetterThanNothing
{
	class Device;
	class CommandPool;

	/**
	 * @brief The CommandBuffer class is a wrapper around VkCommandBuffer.
	 */
	class CommandBuffer
	{
	private:
		/**
		 * @brief A pointer to the Device object.
		 */
		Device* m_Device;

		/**
		 * @brief A pointer to the CommandPool object.
		 */
		CommandPool* m_CommandPool;

		/**
		 * @brief The VkCommandBuffer object.
		 */
		VkCommandBuffer m_CommandBuffer { VK_NULL_HANDLE };

	public:
		/**
		 * @brief Construct a new CommandBuffer object.
		 * @param device A pointer to the Device object.
		 * @param commandPool A pointer to the CommandPool object.
		 */
		CommandBuffer(Device* device);

		/**
		 * @brief Destroy the CommandBuffer object.
		 */
		~CommandBuffer();

							CommandBuffer(const CommandBuffer&) = delete;
		CommandBuffer&		operator=(const CommandBuffer&) = delete;
							CommandBuffer(CommandBuffer&&) = delete;
		CommandBuffer&		operator=(CommandBuffer&&) = delete;

		/**
		 * @brief Begin recording commands.
		 */
		void Begin();

		/**
		 * @brief End recording commands.
		 */
		void End();

		/**
		 * @brief Begin a render pass.
		 * @param renderPassBeginInfo The render pass begin info.
		 */
		void BeginRenderPass(VkRenderPassBeginInfo& renderPassBeginInfo);

		/**
		 * @brief Set the viewport.
		 * @param viewport The viewport.
		 */
		void SetViewport(VkViewport& viewport);

		/**
		 * @brief Set the scissor.
		 * @param scissor The scissor.
		 */
		void SetScissor(VkRect2D& scissor);

		/**
		 * @brief End a render pass.
		 */
		void EndRenderPass();

		/**
		 * @brief Bind a pipeline.
		 * @param pipeline The pipeline.
		 */
		void BindPipeline(VkPipeline& pipeline);

		/**
		 * @brief Bind a vertex buffer.
		 * @param vertexBuffer The vertex buffer.
		 */
		void BindVertexBuffer(VkBuffer& vertexBuffer);

		/**
		 * @brief Bind vertex buffers.
		 * @param firstBinding The first binding.
		 * @param bindingCount The binding count.
		 * @param vertexBuffers The vertex buffers.
		 * @param offsets The offsets.
		 */
		void BindVertexBuffers(u32 firstBinding, u32 bindingCount, VkBuffer* vertexBuffers, VkDeviceSize* offsets);

		/**
		 * @brief Bind an index buffer.
		 * @param indexBuffer The index buffer.
		 */
		void BindIndexBuffer(VkBuffer& indexBuffer);

		void BindIndexBuffer(VkBuffer& indexBuffer, VkDeviceSize offset);

		/**
		 * @brief Bind descriptor sets.
		 * @param descriptorSet The descriptor set.
		 * @param pipelineLayout The pipeline layout.
		 */
		void BindDescriptorSets(VkDescriptorSet& descriptorSet, VkPipelineLayout& pipelineLayout);

		/**
		 * @brief Draw vertices.
		 * @param indexCount The index count.
		 */
		void DrawIndexed(u32 indexCount);

		void DrawIndexed(u32 indexCount, u32 instanceCount, u32 firstIndex, u32 vertexOffset, u32 firstInstance);

		/**
		 * @brief A wrapper around vkCmdPipelineBarrier.
		 *
		 * @param srcStageMask The source stage mask.
		 * @param dstStageMask The destination stage mask.
		 * @param imageMemoryBarriers The image memory barriers.
		 */
		void CmdPipelineBarrier(VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkImageMemoryBarrier& imageMemoryBarriers);

		/**
		 * @brief A wrapper around vkCmdBlitImage.
		 *
		 * @param srcImage The source image.
		 * @param dstImage The destination image.
		 * @param blit The image blit.
		 */
		void CmdBlitImage(VkImage& srcImage, VkImage& dstImage, VkImageBlit& blit);

		/**
		 * @brief A wrapper around vkCmdCopyBufferToImage.
		 *
		 * @param buffer The buffer.
		 * @param dstImage The destination image.
		 * @param dstImageLayout The destination image layout.
		 * @param regionCount The region count.
		 * @param regions The regions.
		 */
		void CmdCopyBufferToImage(VkBuffer& buffer, VkImage& dstImage, VkImageLayout dstImageLayout, u32 regionCount, VkBufferImageCopy& regions);

		/**
		 * @brief A wrapper around vkCmdCopyBuffer.
		 *
		 * @param srcBuffer The source buffer.
		 * @param dstBuffer The destination buffer.
		 * @param regionCount The region count.
		 * @param regions The regions.
		 */
		void CmdCopyBuffer(VkBuffer& srcBuffer, VkBuffer& dstBuffer, u32 regionCount, VkBufferCopy& regions);

		/**
		 * @brief Provide a callback to record commands using a single time command buffer.
		 *
		 * @param callback The callback.
		 * @param device A pointer to the Device object.
		 */
		static void SingleTimeCommands(const std::function<void(CommandBuffer*)>& callback, Device* device);

		/**
		 * @brief Get the Vk Command Buffer object
		 *
		 * @return A reference to the VkCommandBuffer object.
		 */
		VkCommandBuffer& GetVkCommandBuffer() { return m_CommandBuffer; }
	};
};
