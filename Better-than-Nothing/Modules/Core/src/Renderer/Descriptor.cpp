#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	Descriptor::Descriptor(Device* device, VkDescriptorSet descriptorSet)
	{
		m_Device = device;
		m_DescriptorSets = descriptorSet;
	}

	void Descriptor::Update(u32 binding, VkDescriptorType type, VkDescriptorBufferInfo* bufferInfo, VkDescriptorImageInfo* imageInfo)
	{
		VkWriteDescriptorSet descriptorWrite{};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = m_DescriptorSets;
		descriptorWrite.dstBinding = binding;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = type;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = bufferInfo;
		descriptorWrite.pImageInfo = imageInfo;

		vkUpdateDescriptorSets(m_Device->GetVkDevice(), 1, &descriptorWrite, 0, nullptr);
	}
};
