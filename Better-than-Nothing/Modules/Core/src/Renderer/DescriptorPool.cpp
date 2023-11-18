#include "Renderer/Device.hpp"
#include "Renderer/SwapChain.hpp"
#include "Renderer/DescriptorPool.hpp"
#include "Renderer/UniformBufferObject.hpp"

#include "Ressources/Model.hpp"
#include "Ressources/Texture.hpp"

#include "Scene/Entity.hpp"

namespace BetterThanNothing
{
	DescriptorPool::DescriptorPool(Device* pDevice, SwapChain* pSwapChain)
		: m_pDevice(pDevice), m_pSwapChain(pSwapChain)
	{
		m_DescriptorPoolSize = 0;

		CreateDescriptorSetLayout();
		CreateDescriptorPool(&m_DescriptorPool, 1000);
	}

	DescriptorPool::~DescriptorPool()
	{
		DestroyDescriptorPool();
		vkDestroyDescriptorSetLayout(m_pDevice->GetVkDevice(), m_DescriptorSetLayout, nullptr);
	}

	void DescriptorPool::CreateDescriptorSetLayout()
	{
		VkDescriptorSetLayoutBinding uboLayoutBinding{};
		uboLayoutBinding.binding = 0;
		uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		uboLayoutBinding.descriptorCount = 1;
		uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
		uboLayoutBinding.pImmutableSamplers = nullptr;

		VkDescriptorSetLayoutBinding samplerLayoutBinding{};
		samplerLayoutBinding.binding = 1;
		samplerLayoutBinding.descriptorCount = 1;
		samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		samplerLayoutBinding.pImmutableSamplers = nullptr;
		samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

		std::array<VkDescriptorSetLayoutBinding, 2> bindings = {
			uboLayoutBinding, samplerLayoutBinding
		};

		VkDescriptorSetLayoutCreateInfo layoutInfo{};
		layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutInfo.bindingCount = static_cast<u32>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(m_pDevice->GetVkDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}
	}

	void DescriptorPool::CreateDescriptorPool(VkDescriptorPool* newDescriptorPool, u32 newCapacity)
	{
		m_DescriptorPoolCapacity = newCapacity;

		// Create the descriptor pool
		std::array<VkDescriptorPoolSize, 2> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = static_cast<u32>(m_DescriptorPoolCapacity * MAX_FRAMES_IN_FLIGHT);
		poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[1].descriptorCount = static_cast<u32>(m_DescriptorPoolCapacity * MAX_FRAMES_IN_FLIGHT);

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
		poolInfo.poolSizeCount = static_cast<u32>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<u32>(m_DescriptorPoolCapacity * MAX_FRAMES_IN_FLIGHT);

		if (vkCreateDescriptorPool(m_pDevice->GetVkDevice(), &poolInfo, nullptr, newDescriptorPool) != VK_SUCCESS) {
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
		vkDestroyDescriptorPool(m_pDevice->GetVkDevice(), m_DescriptorPool, nullptr);

		// Set the new descriptor pool
		m_DescriptorPool = newDescriptorPool;
	}

	void DescriptorPool::DestroyDescriptorPool()
	{
		if (m_DescriptorPool != VK_NULL_HANDLE) {
			vkDestroyDescriptorPool(m_pDevice->GetVkDevice(), m_DescriptorPool, nullptr);
		}
		m_DescriptorPool = VK_NULL_HANDLE;
		m_DescriptorPoolSize = 0;
		m_DescriptorPoolCapacity = 0;
	}

	void DescriptorPool::CreateDescriptorSets(Entity* entity)
	{
		VkDevice device = m_pDevice->GetVkDevice();

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

			VkDescriptorBufferInfo bufferInfo{};
			bufferInfo.buffer = m_pSwapChain->GetUniformBuffers()[i][m_DescriptorPoolSize];
			bufferInfo.offset = 0;
			bufferInfo.range = sizeof(UniformBufferObject);

			VkDescriptorImageInfo imageInfo{};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			imageInfo.imageView = entity->GetTexture()->imageView;
			imageInfo.sampler = entity->GetTexture()->sampler;

			std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

			descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[0].dstSet = m_DescriptorSets[i][m_DescriptorPoolSize];
			descriptorWrites[0].dstBinding = 0;
			descriptorWrites[0].dstArrayElement = 0;
			descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptorWrites[0].descriptorCount = 1;
			descriptorWrites[0].pBufferInfo = &bufferInfo;

			descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptorWrites[1].dstSet = m_DescriptorSets[i][m_DescriptorPoolSize];
			descriptorWrites[1].dstBinding = 1;
			descriptorWrites[1].dstArrayElement = 0;
			descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			descriptorWrites[1].descriptorCount = 1;
			descriptorWrites[1].pImageInfo = &imageInfo;

			vkUpdateDescriptorSets(device, static_cast<u32>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
		}

		m_DescriptorPoolSize += 1;
	}

	void DescriptorPool::TransferDescriptorSets(VkDescriptorPool* newDescriptorPool)
	{
		VkDevice device = m_pDevice->GetVkDevice();

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
