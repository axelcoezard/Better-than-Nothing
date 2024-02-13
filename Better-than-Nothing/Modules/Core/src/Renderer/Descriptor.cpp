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

		std::cout << "descriptorWrite.dstBinding: " << descriptorWrite.dstBinding << std::endl;
		std::cout << "descriptorWrite.descriptorType: " << descriptorWrite.descriptorType << std::endl;

		vkUpdateDescriptorSets(m_Device->GetVkDevice(), 1, &descriptorWrite, 0, nullptr);
	}

	VkDescriptorSet& Descriptor::GetDescriptorSet()
	{
		return m_DescriptorSets;
	}
};
