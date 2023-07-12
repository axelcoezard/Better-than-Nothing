#pragma once

namespace BetterThanNothing
{
	class CDevice;

	class CSwapChain;

	class CDescriptorPool
	{
	private:
		CDevice*						m_pDevice;
		CSwapChain*						m_pSwapChain;

		VkDescriptorSetLayout			m_DescriptorSetLayout;
		VkDescriptorPool				m_DescriptorPool;
		std::vector<VkDescriptorSet>	m_DescriptorSets;

	public:
										CDescriptorPool(CDevice* pDevice, CSwapChain* pSwapChain);
										~CDescriptorPool();

										CDescriptorPool(const CDescriptorPool&) = delete;
		CDescriptorPool&				operator=(const CDescriptorPool&) = delete;
										CDescriptorPool(CDescriptorPool&&) = delete;
		CDescriptorPool&				operator=(CDescriptorPool&&) = delete;

	private:
		void 							CreateDescriptorSetLayout();
		void							CreateDescriptorPool();
		void							CreateDescriptorSets();

	public:
		VkDescriptorSetLayout&			GetVkDescriptorSetLayout() { return m_DescriptorSetLayout; }
		VkDescriptorPool&				GetVkDescriptorPool() { return m_DescriptorPool; }
		std::vector<VkDescriptorSet>&	GetVkDescriptorSets() { return m_DescriptorSets; }
	};
};
