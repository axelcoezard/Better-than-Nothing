#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	DescriptorPool::DescriptorPool(Device* device)
		: m_Device(device)
	{
		CreateDescriptorPool(10000);

		CreateDescriptorLayout({
			.binding = 0,
			.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.descriptorCount = 1,
			.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT
		});
	}

	DescriptorPool::~DescriptorPool()
	{
		DestroyDescriptorPool();
	}

	void DescriptorPool::CreateDescriptorPool(u32 maxSize)
	{
		VkDescriptorPoolSize poolSize{};
		poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSize.descriptorCount = maxSize * MAX_FRAMES_IN_FLIGHT;

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = 1;
		poolInfo.pPoolSizes = &poolSize;
		poolInfo.maxSets = maxSize * MAX_FRAMES_IN_FLIGHT;

		if (vkCreateDescriptorPool(m_Device->GetVkDevice(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create descriptor pool!");
		}
	}

	void DescriptorPool::DestroyDescriptorPool()
	{
		if (m_DescriptorPool != VK_NULL_HANDLE)
		{
			vkDestroyDescriptorPool(m_Device->GetVkDevice(), m_DescriptorPool, nullptr);
		}
	}

	bool DescriptorPool::FindDescriptorLayout(DescriptorLayoutInfo layoutInfo, u32* layoutId)
	{
		for (DescriptorLayout& layout : m_DescriptorLayouts)
		{
			if (layout.m_LayoutInfo == layoutInfo)
			{
				*layoutId = layout.m_Id;
				return true;
			}
		}
		return false;
	}

	u32 DescriptorPool::CreateDescriptorLayout(DescriptorLayoutInfo descriptorLayoutInfo)
	{
		u32 layoutId = m_DescriptorLayouts.size();
		if (FindDescriptorLayout(descriptorLayoutInfo, &layoutId))
			return layoutId;

		VkDescriptorSetLayoutBinding layoutBinding{};
		layoutBinding.binding = descriptorLayoutInfo.binding;
		layoutBinding.descriptorType = descriptorLayoutInfo.descriptorType;
		layoutBinding.descriptorCount = descriptorLayoutInfo.descriptorCount;
		layoutBinding.stageFlags = descriptorLayoutInfo.stageFlags;
		layoutBinding.pImmutableSamplers = nullptr;

		VkDescriptorSetLayoutCreateInfo layoutCreateInfo{};
		layoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutCreateInfo.bindingCount = 1;
		layoutCreateInfo.pBindings = &layoutBinding;

		VkDescriptorSetLayout descriptorLayout;
		if (vkCreateDescriptorSetLayout(m_Device->GetVkDevice(), &layoutCreateInfo, nullptr, &descriptorLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create descriptor set layout!");

		m_DescriptorLayouts.push_back({ layoutId, descriptorLayoutInfo, descriptorLayout });
		return layoutId;
	}

	void DescriptorPool::CreateDescriptor(u32 descriptorLayoutId)
	{
		if (descriptorLayoutId >= m_DescriptorLayouts.size())
			throw std::runtime_error("Descriptor layout id out of range!");

		DescriptorLayout& layout = m_DescriptorLayouts[descriptorLayoutId];

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_DescriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &layout.m_Instance;

		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			VkDescriptorSet descriptorSet;
			if (vkAllocateDescriptorSets(m_Device->GetVkDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS)
				throw std::runtime_error("failed to allocate descriptor set!");

			m_Descriptors[i].push_back({ m_Device, descriptorSet });
		}
	}

	std::vector<DescriptorLayout> DescriptorPool::GetAllDescriptorLayouts()
	{
		return m_DescriptorLayouts;
	}
};
