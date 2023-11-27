#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	DescriptorPool::DescriptorPool(Device* device, UniformsPool* uniformsPool)
		: m_Device(device), m_UniformsPool(uniformsPool)
	{
		m_DescriptorPoolSize = 0;

		CreateDescriptorSetLayout();
		CreateDescriptorPool(&m_DescriptorPool, 1000);
	}

	DescriptorPool::~DescriptorPool()
	{
		DestroyDescriptorPool();
		vkDestroyDescriptorSetLayout(m_Device->GetVkDevice(), m_DescriptorSetLayout, nullptr);
	}

	void DescriptorPool::CreateDescriptorSetLayout()
	{
		VkDescriptorSetLayoutBinding globalUniformsLayoutBinding{};
		globalUniformsLayoutBinding.binding = 0;
		globalUniformsLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		globalUniformsLayoutBinding.descriptorCount = 1;
		globalUniformsLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		globalUniformsLayoutBinding.pImmutableSamplers = nullptr;

		VkDescriptorSetLayoutBinding dynamicUniformsLayoutBinding{};
		dynamicUniformsLayoutBinding.binding = 1;
		dynamicUniformsLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		dynamicUniformsLayoutBinding.descriptorCount = 1;
		dynamicUniformsLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		dynamicUniformsLayoutBinding.pImmutableSamplers = nullptr;

		VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 2;
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.descriptorCount = 1;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
		samplerLayoutBinding.pImmutableSamplers = nullptr;

		std::array<VkDescriptorSetLayoutBinding, 3> bindings = {
			globalUniformsLayoutBinding, dynamicUniformsLayoutBinding, samplerLayoutBinding
		};

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<u32>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(m_Device->GetVkDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}
	}

	void DescriptorPool::CreateDescriptorPool(VkDescriptorPool* newDescriptorPool, u32 newCapacity)
	{
		m_DescriptorPoolCapacity = newCapacity;

		// Create the descriptor pool
		std::array<VkDescriptorPoolSize, 3> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = static_cast<u32>(m_DescriptorPoolCapacity * MAX_FRAMES_IN_FLIGHT);

		poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[1].descriptorCount = static_cast<u32>(m_DescriptorPoolCapacity * MAX_FRAMES_IN_FLIGHT);

		poolSizes[2].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[2].descriptorCount = static_cast<u32>(m_DescriptorPoolCapacity * MAX_FRAMES_IN_FLIGHT);

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		poolInfo.poolSizeCount = static_cast<u32>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<u32>(m_DescriptorPoolCapacity * MAX_FRAMES_IN_FLIGHT);

		if (vkCreateDescriptorPool(m_Device->GetVkDevice(), &poolInfo, nullptr, newDescriptorPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor pool!");
		}

		// Allocate the descriptor sets
		m_DescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			m_DescriptorSets[i].resize(m_DescriptorPoolCapacity);
		}
	}

	void DescriptorPool::ExtendDescriptorPool()
	{
		// Set new capacity to twice the old one
		m_DescriptorPoolCapacity *= 2;

		// Create a new descriptor pool with the new capacity
		VkDescriptorPool newDescriptorPool;
		CreateDescriptorPool(&newDescriptorPool, m_DescriptorPoolCapacity);

		// Transfer the old descriptor sets to the new descriptor pool
		TransferDescriptorSets(&newDescriptorPool);

		// Destroy the old descriptor pool
		vkDestroyDescriptorPool(m_Device->GetVkDevice(), m_DescriptorPool, nullptr);

		// Set the new descriptor pool
		m_DescriptorPool = newDescriptorPool;
	}

	void DescriptorPool::DestroyDescriptorPool()
	{
		if (m_DescriptorPool != VK_NULL_HANDLE) {
			vkDestroyDescriptorPool(m_Device->GetVkDevice(), m_DescriptorPool, nullptr);
		}
		m_DescriptorPool = VK_NULL_HANDLE;
		m_DescriptorPoolSize = 0;
		m_DescriptorPoolCapacity = 0;
	}

	void DescriptorPool::CreateDescriptorSets(Entity* entity, std::vector<Buffer*>& globalUniforms, std::vector<Buffer*>& dynamicUniforms)
	{
		VkDevice device = m_Device->GetVkDevice();

		if (m_DescriptorPoolSize >= m_DescriptorPoolCapacity) {
			ExtendDescriptorPool();
		}

		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			VkDescriptorSetAllocateInfo allocInfo{};
			allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocInfo.descriptorPool = m_DescriptorPool;
			allocInfo.descriptorSetCount = 1;
			allocInfo.pSetLayouts = &m_DescriptorSetLayout;

			if (vkAllocateDescriptorSets(device, &allocInfo, &(m_DescriptorSets[i][m_DescriptorPoolSize])) != VK_SUCCESS) {
				throw std::runtime_error("failed to allocate descriptor sets!");
			}

			VkDescriptorBufferInfo globalUniformsInfo{};
			globalUniformsInfo.buffer = globalUniforms[i]->m_Buffer;
			globalUniformsInfo.offset = 0;
			globalUniformsInfo.range = sizeof(GlobalUniforms);

			VkDescriptorBufferInfo dynamicUniformsInfo{};
			dynamicUniformsInfo.buffer = dynamicUniforms[i]->m_Buffer;
			dynamicUniformsInfo.offset = 0;
			dynamicUniformsInfo.range = sizeof(DynamicUniforms);

			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = entity->GetTexture()->imageView;
			imageInfo.sampler = entity->GetTexture()->sampler;

			std::array<VkWriteDescriptorSet, 3> descriptorWrites{};

			descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[0].dstSet = m_DescriptorSets[i][m_DescriptorPoolSize];
			descriptorWrites[0].dstBinding = 0;
			descriptorWrites[0].dstArrayElement = 0;
			descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[0].descriptorCount = 1;
			descriptorWrites[0].pBufferInfo = &globalUniformsInfo;

			descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[1].dstSet = m_DescriptorSets[i][m_DescriptorPoolSize];
			descriptorWrites[1].dstBinding = 1;
			descriptorWrites[1].dstArrayElement = 0;
			descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[1].descriptorCount = 1;
			descriptorWrites[1].pBufferInfo = &dynamicUniformsInfo;

			descriptorWrites[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[2].dstSet = m_DescriptorSets[i][m_DescriptorPoolSize];
			descriptorWrites[2].dstBinding = 2;
			descriptorWrites[2].dstArrayElement = 0;
			descriptorWrites[2].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[2].descriptorCount = 1;
			descriptorWrites[2].pImageInfo = &imageInfo;

			vkUpdateDescriptorSets(device, static_cast<u32>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
		}

		m_DescriptorPoolSize += 1;
	}

	void DescriptorPool::TransferDescriptorSets(VkDescriptorPool* newDescriptorPool)
	{
		VkDevice device = m_Device->GetVkDevice();

		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			for (u32 j = 0; j < m_DescriptorPoolSize; j++) {
				VkDescriptorSet oldDescriptorSet = m_DescriptorSets[i][j];

				VkDescriptorSetAllocateInfo allocInfo{};
				allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				allocInfo.descriptorPool = *newDescriptorPool;
				allocInfo.descriptorSetCount = 1;
				allocInfo.pSetLayouts = &m_DescriptorSetLayout;

				if (vkAllocateDescriptorSets(device, &allocInfo, &(m_DescriptorSets[i][j])) != VK_SUCCESS) {
					throw std::runtime_error("failed to allocate descriptor sets!");
				}

				VkCopyDescriptorSet copyDescriptorSet{};
				copyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
				copyDescriptorSet.srcSet = oldDescriptorSet;
				copyDescriptorSet.dstSet = m_DescriptorSets[i][j];
				copyDescriptorSet.descriptorCount = 1;

				vkUpdateDescriptorSets(device, 0, nullptr, 1, &copyDescriptorSet);

				if (vkFreeDescriptorSets(device, m_DescriptorPool, 1, &oldDescriptorSet) != VK_SUCCESS) {
					throw std::runtime_error("failed to free descriptor sets!");
				}
			}
		}

		LOG_SUCCESS("DescriptorPool: Transfered descriptor sets to new descriptor pool");
	}
};
