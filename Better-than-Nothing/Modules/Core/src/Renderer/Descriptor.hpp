#pragma once

namespace BetterThanNothing
{
	class Device;

	class Descriptor
	{
	private:
		Device* m_Device;

		VkDescriptorSet m_DescriptorSets;

	public:
		Descriptor(Device* device, VkDescriptorSet descriptorSet);

		void Update(u32 binding, VkDescriptorType type, VkDescriptorBufferInfo* bufferInfo, VkDescriptorImageInfo* imageInfo);

		VkDescriptorSet& GetDescriptorSet();
	};
};
