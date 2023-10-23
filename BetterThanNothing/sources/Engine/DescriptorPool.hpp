#pragma once

namespace BetterThanNothing
{
	class Device;
	class SwapChain;
	class Model;

	class DescriptorPool
	{
	private:
		Device*									m_pDevice;
		SwapChain*									m_pSwapChain;

		VkDescriptorSetLayout						m_DescriptorSetLayout;
		VkDescriptorPool							m_DescriptorPool;
		std::vector<std::vector<VkDescriptorSet>>	m_DescriptorSets;

	public:
													DescriptorPool(Device* pDevice, SwapChain* pSwapChain);
													~DescriptorPool();

													DescriptorPool(const DescriptorPool&) = delete;
		DescriptorPool&							operator=(const DescriptorPool&) = delete;
													DescriptorPool(DescriptorPool&&) = delete;
		DescriptorPool&							operator=(DescriptorPool&&) = delete;

	private:
		void 										CreateDescriptorSetLayout();

	public:
		void										CreateDescriptorPool(std::vector<Model*> pModels);
		void										CreateDescriptorSets(std::vector<Model*> pModels);

	public:
		VkDescriptorSetLayout&						GetVkDescriptorSetLayout()	{ return m_DescriptorSetLayout; }
		VkDescriptorPool&							GetVkDescriptorPool()		{ return m_DescriptorPool; }
		std::vector<std::vector<VkDescriptorSet>>&	GetVkDescriptorSets()		{ return m_DescriptorSets; }
	};
};
