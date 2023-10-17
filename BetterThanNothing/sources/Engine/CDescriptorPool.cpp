#include "CDevice.hpp"
#include "CSwapChain.hpp"
#include "CTexture.hpp"
#include "CDescriptorPool.hpp"
#include "CUniformBufferObject.hpp"
#include "CModel.hpp"

namespace BetterThanNothing
{
	CDescriptorPool::CDescriptorPool(CDevice* pDevice, CSwapChain* pSwapChain)
		: m_pDevice(pDevice), m_pSwapChain(pSwapChain)
	{
		CreateDescriptorSetLayout();
	}

	CDescriptorPool::~CDescriptorPool()
	{
		auto device = m_pDevice->GetVkDevice();
		vkDestroyDescriptorPool(device, m_DescriptorPool, nullptr);
		vkDestroyDescriptorSetLayout(m_pDevice->GetVkDevice(), m_DescriptorSetLayout, nullptr);
	}

	void CDescriptorPool::CreateDescriptorSetLayout()
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
		layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
		layoutInfo.pBindings = bindings.data();

		if (vkCreateDescriptorSetLayout(m_pDevice->GetVkDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor set layout!");
		}
	}

	void CDescriptorPool::CreateDescriptorPool(std::vector<CModel*> pModels)
	{
		std::array<VkDescriptorPoolSize, 2> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * pModels.size());
		poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * pModels.size());

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT * pModels.size());

		if (vkCreateDescriptorPool(m_pDevice->GetVkDevice(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create descriptor pool!");
		}
	}

	void CDescriptorPool::CreateDescriptorSets(std::vector<CModel*> pModels)
	{
		auto device = m_pDevice->GetVkDevice();
		auto modelCount = pModels.size();

		m_DescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
		for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			m_DescriptorSets[i].resize(modelCount);
			for (uint32_t j = 0; j < modelCount; j++)
			{
				VkDescriptorSetAllocateInfo allocInfo{};
				allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				allocInfo.descriptorPool = m_DescriptorPool;
				allocInfo.descriptorSetCount = 1;
				allocInfo.pSetLayouts = &m_DescriptorSetLayout;

				if (vkAllocateDescriptorSets(device, &allocInfo, &(m_DescriptorSets[i][j])) != VK_SUCCESS) {
					throw std::runtime_error("failed to allocate descriptor sets!");
				}

				VkDescriptorBufferInfo bufferInfo{};
				bufferInfo.buffer = m_pSwapChain->GetUniformBuffers()[i];
				bufferInfo.offset = 0;
				bufferInfo.range = sizeof(CUniformBufferObject);

				VkDescriptorImageInfo imageInfo{};
				imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				imageInfo.imageView = pModels[j]->GetTexture()->GetVkTextureImageView();
				imageInfo.sampler = pModels[j]->GetTexture()->GetVkTextureSampler();

				std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

				descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				descriptorWrites[0].dstSet = m_DescriptorSets[i][j];
				descriptorWrites[0].dstBinding = 0;
				descriptorWrites[0].dstArrayElement = 0;
				descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				descriptorWrites[0].descriptorCount = 1;
				descriptorWrites[0].pBufferInfo = &bufferInfo;

				descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
				descriptorWrites[1].dstSet = m_DescriptorSets[i][j];
				descriptorWrites[1].dstBinding = 1;
				descriptorWrites[1].dstArrayElement = 0;
				descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				descriptorWrites[1].descriptorCount = 1;
				descriptorWrites[1].pImageInfo = &imageInfo;

				vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
			}
		}
	}
};
