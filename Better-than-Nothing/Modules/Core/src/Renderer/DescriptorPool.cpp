#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	DescriptorPool::DescriptorPool(Device* device)
		: m_Device(device)
	{
		CreateDescriptorPool(10000);
	}

	DescriptorPool::~DescriptorPool()
	{
		DestroyDescriptorPool();
	}

	void DescriptorPool::CreateDescriptorPool(u32 maxSize)
	{
		std::array<VkDescriptorPoolSize, 3> poolSizes{};
		poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[0].descriptorCount = static_cast<u32>(maxSize * MAX_FRAMES_IN_FLIGHT);

		poolSizes[1].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		poolSizes[1].descriptorCount = static_cast<u32>(maxSize * MAX_FRAMES_IN_FLIGHT);

		poolSizes[2].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		poolSizes[2].descriptorCount = static_cast<u32>(maxSize * MAX_FRAMES_IN_FLIGHT);

		VkDescriptorPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		poolInfo.poolSizeCount = static_cast<u32>(poolSizes.size());
		poolInfo.pPoolSizes = poolSizes.data();
		poolInfo.maxSets = static_cast<u32>(maxSize * MAX_FRAMES_IN_FLIGHT);

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
		layoutBinding.descriptorCount = 1;
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

	u32 DescriptorPool::CreateDescriptor(u32 descriptorLayoutId)
	{
		if (descriptorLayoutId >= m_DescriptorLayouts.size())
			throw std::runtime_error("Descriptor layout id out of range!");

		DescriptorLayout& layout = m_DescriptorLayouts[descriptorLayoutId];

		VkDescriptorSetAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool = m_DescriptorPool;
		allocInfo.descriptorSetCount = 1;
		allocInfo.pSetLayouts = &layout.m_Instance;

		u32 descriptorId = m_Descriptors[0].size();
		for (u32 i = 0; i < MAX_FRAMES_IN_FLIGHT; i++)
		{
			VkDescriptorSet descriptorSet;
			if (vkAllocateDescriptorSets(m_Device->GetVkDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS)
				throw std::runtime_error("failed to allocate descriptor set!");

			m_Descriptors[i].push_back({ m_Device, descriptorSet });
		}
		return descriptorId;
	}

	DescriptorLayout DescriptorPool::FindDescriptorLayoutByName(const std::string& name)
	{
		for (u32 i = 0; i < m_DescriptorLayouts.size(); i++)
		{
			if (m_DescriptorLayouts[i].m_LayoutInfo.name == name)
				return m_DescriptorLayouts[i];
		}
		return {};
	}

	std::vector<DescriptorLayout>& DescriptorPool::GetAllDescriptorLayouts()
	{
		return m_DescriptorLayouts;
	}

	std::vector<Descriptor>& DescriptorPool::GetDescriptors(u32 frameIndex)
	{
		return m_Descriptors[frameIndex];
	}
};
