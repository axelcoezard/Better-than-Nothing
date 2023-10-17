#pragma once

namespace BetterThanNothing
{
	class CDevice;
	class CSwapChain;
	class CModel;

	class CDescriptorPool
	{
	private:
		CDevice*						m_pDevice;
		CSwapChain*						m_pSwapChain;

		VkDescriptorSetLayout			m_DescriptorSetLayout;
		VkDescriptorPool				m_DescriptorPool;
		//std::vector<VkDescriptorSet>	m_DescriptorSets;
		std::vector<std::vector<VkDescriptorSet>> m_DescriptorSets;

	public:
										CDescriptorPool(CDevice* pDevice, CSwapChain* pSwapChain);
										~CDescriptorPool();

										CDescriptorPool(const CDescriptorPool&) = delete;
		CDescriptorPool&				operator=(const CDescriptorPool&) = delete;
										CDescriptorPool(CDescriptorPool&&) = delete;
		CDescriptorPool&				operator=(CDescriptorPool&&) = delete;

	private:
		void 							CreateDescriptorSetLayout();

	public:
		void							CreateDescriptorPool(std::vector<CModel*> pModels);
		void							CreateDescriptorSets(std::vector<CModel*> pModels);
		void							UpdateDescriptorSets(CModel* model, uint32_t modelIndex);

	public:
		VkDescriptorSetLayout&			GetVkDescriptorSetLayout() { return m_DescriptorSetLayout; }
		VkDescriptorPool&				GetVkDescriptorPool() { return m_DescriptorPool; }
		std::vector<std::vector<VkDescriptorSet>>&	GetVkDescriptorSets() { return m_DescriptorSets; }
	};
};
