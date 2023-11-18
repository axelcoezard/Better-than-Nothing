#pragma once

namespace BetterThanNothing
{
	class Device;
	class SwapChain;
	class Entity;

	class DescriptorPool
	{
	private:
		Device*										m_pDevice;
		SwapChain*									m_pSwapChain;

		VkDescriptorSetLayout						m_DescriptorSetLayout;
		VkDescriptorPool							m_DescriptorPool = VK_NULL_HANDLE;
		std::vector<std::vector<VkDescriptorSet>>	m_DescriptorSets;

		u32											m_DescriptorPoolSize;
		u32											m_DescriptorPoolCapacity;

	public:
													DescriptorPool(Device* pDevice, SwapChain* pSwapChain);
													~DescriptorPool();

													DescriptorPool(const DescriptorPool&) = delete;
		DescriptorPool&								operator=(const DescriptorPool&) = delete;
													DescriptorPool(DescriptorPool&&) = delete;
		DescriptorPool&								operator=(DescriptorPool&&) = delete;

	private:
		void 										CreateDescriptorSetLayout();
		void										CreateDescriptorPool(VkDescriptorPool* newDescriptorPool, u32 capacity);
		void										ExtendDescriptorPool();
		void										DestroyDescriptorPool();

		void										TransferDescriptorSets(VkDescriptorPool* newDescriptorPool);

	public:
		void										CreateDescriptorSets(Entity* entity);

		VkDescriptorSetLayout&						GetVkDescriptorSetLayout()	{ return m_DescriptorSetLayout; }
		VkDescriptorPool&							GetVkDescriptorPool()		{ return m_DescriptorPool; }
		std::vector<std::vector<VkDescriptorSet>>&	GetVkDescriptorSets()		{ return m_DescriptorSets; }
	};
};
