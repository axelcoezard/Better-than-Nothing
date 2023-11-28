#pragma once

namespace BetterThanNothing
{
	class Device;

	class ImGuiDescriptorPool
	{
	private:
		Device* m_Device;

		VkDescriptorPool m_DescriptorPool;

	public:
		ImGuiDescriptorPool(Device* device);
		~ImGuiDescriptorPool();

		VkDescriptorPool& GetVkDescriptorPool();
	};
};
