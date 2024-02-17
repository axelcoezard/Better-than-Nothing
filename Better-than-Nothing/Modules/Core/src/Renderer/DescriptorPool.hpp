#pragma once

namespace BetterThanNothing
{
	class Device;

	class DescriptorLayout;
	class DescriptorLayoutInfo;

	class Descriptor;

	class DescriptorPool
	{
	private:
		Device* m_Device;

		VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;

		std::vector<DescriptorLayout> m_DescriptorLayouts;
		std::vector<Descriptor> m_Descriptors[MAX_FRAMES_IN_FLIGHT];

	public:
		DescriptorPool(Device* device);
		~DescriptorPool();

	private:
		void CreateDescriptorPool(u32 maxSize);
		void DestroyDescriptorPool();
		bool FindDescriptorLayout(DescriptorLayoutInfo layoutInfo, u32* layoutId);

	public:
		u32 CreateDescriptorLayout(DescriptorLayoutInfo layoutInfo);

		u32 CreateDescriptor(DescriptorLayout& descriptorLayout);
		u32 CreateDescriptor(u32 descriptorLayoutId);

		DescriptorLayout FindDescriptorLayoutByName(const std::string& name);

		std::vector<DescriptorLayout>& GetAllDescriptorLayouts();
		std::vector<Descriptor>& GetDescriptors(u32 frameIndex);

	};
};
