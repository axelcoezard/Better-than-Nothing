#pragma once

namespace BetterThanNothing
{
	struct DescriptorLayoutInfo
	{
		u32 binding;
		VkDescriptorType descriptorType;
		u32 descriptorCount;
		VkShaderStageFlags stageFlags;

		std::string pipelineId;

		bool operator==(const DescriptorLayoutInfo& other) const
		{
			return binding == other.binding
				&& descriptorType == other.descriptorType
				&& descriptorCount == other.descriptorCount
				&& stageFlags == other.stageFlags
				&& pipelineId == other.pipelineId;
		}
	};

	struct DescriptorLayout
	{
		u32 m_Id;
		DescriptorLayoutInfo m_LayoutInfo;
		VkDescriptorSetLayout m_Instance;

		bool operator==(const DescriptorLayout& other) const
		{
			return m_LayoutInfo == other.m_LayoutInfo;
		}
	};
};

