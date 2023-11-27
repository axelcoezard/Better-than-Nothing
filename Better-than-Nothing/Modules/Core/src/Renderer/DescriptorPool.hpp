#pragma once

namespace BetterThanNothing
{
	class Device;
	class Entity;
	class Buffer;
	class UniformsPool;

	/**
	 * @brief A wrapper class for VkDescriptorPool
	 * @note It stores a VkDescriptorSetLayout and a VkDescriptorPool
	 * @note It also stores a MAX_FRAME_INFLIGHT vectors of VkDescriptorSet
	 */
	class DescriptorPool
	{
	private:
		/**
		 * @brief The device that owns this descriptor pool
		 */
		Device* m_Device;

		/**
		 * @brief The uniforms pool
		 */
		UniformsPool* m_UniformsPool;

		/**
		 * @brief The VkDescriptorSetLayout
		 */
		VkDescriptorSetLayout m_DescriptorSetLayout;

		/**
		 * @brief The VkDescriptorPool
		 */
		VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;

		/**
		 * @brief All the VkDescriptorSet
		 */
		std::vector<std::vector<VkDescriptorSet>> m_DescriptorSets;

		/**
		 * @brief The number of descriptor sets in the pool
		 */
		u32 m_DescriptorPoolSize;

		/**
		 * @brief The capacity of the descriptor pool
		 */
		u32 m_DescriptorPoolCapacity;

	public:
		/**
		 * @brief Construct a new Descriptor Pool object
		 * @param device The device that owns this descriptor pool
		 * @param uniformsPool The uniforms pool
		 */
		DescriptorPool(Device* device, UniformsPool* uniformsPool);

		/**
		 * @brief Destroy the Descriptor Pool object
		 */
		~DescriptorPool();

		DescriptorPool(const DescriptorPool&) = delete;
		DescriptorPool& operator=(const DescriptorPool&) = delete;
		DescriptorPool(DescriptorPool&&) = delete;
		DescriptorPool& operator=(DescriptorPool&&) = delete;

	private:
		/**
		 * @brief Create the VkDescriptorSetLayout
		 */
		void CreateDescriptorSetLayout();

		/**
		 * @brief Create the VkDescriptorPool
		 * @param newDescriptorPool A pointer to the VkDescriptorPool to create
		 * @param capacity The capacity of the new descriptor pool
		 */
		void CreateDescriptorPool(VkDescriptorPool* newDescriptorPool, u32 capacity);

		/**
		 * @brief Extend the VkDescriptorPool
		 * @note It doubles the capacity of the descriptor pool and transfers the descriptor sets to the new descriptor pool
		 */
		void ExtendDescriptorPool();

		/**
		 * @brief Destroy the VkDescriptorPool
		 */
		void DestroyDescriptorPool();

		/**
		 * @brief Transfer the descriptor sets to a new descriptor pool
		 * @param newDescriptorPool A pointer to the new descriptor pool
		 */
		void TransferDescriptorSets(VkDescriptorPool* newDescriptorPool);

	public:
		/**
		 * @brief Create a VkDescriptorSet and store it in the pool
		 *
		 * @param entity The entity that needs a descriptor set
		 * @param uniformBuffers All the uniform buffers
		 */
		void CreateDescriptorSets(Entity* entity, std::vector<Buffer*>& globalUniforms, std::vector<Buffer*>& dynamicUniforms);

		/**
		 * @brief Get the VkDescriptorSetLayout object
		 * @return VkDescriptorSetLayout& The VkDescriptorSetLayout object
		 */
		VkDescriptorSetLayout& GetVkDescriptorSetLayout() { return m_DescriptorSetLayout; }

		/**
		 * @brief Get the VkDescriptorPool object
		 * @return VkDescriptorPool& The VkDescriptorPool object
		 */
		VkDescriptorPool& GetVkDescriptorPool() { return m_DescriptorPool; }

		/**
		 * @brief Get the VkDescriptorSets object
		 * @return std::vector<std::vector<VkDescriptorSet>>& All the VkDescriptorSet objects
		 */
		std::vector<std::vector<VkDescriptorSet>>& GetVkDescriptorSets() { return m_DescriptorSets; }
	};
};
