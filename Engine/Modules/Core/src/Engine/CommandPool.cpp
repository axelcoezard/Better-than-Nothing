#include "Engine/CommandPool.hpp"

namespace BetterThanNothing
{
	CommandPool::CommandPool(Device* pDevice): m_pDevice(pDevice) {
		CreateCommandPool();
	}

	CommandPool::~CommandPool() {
		vkDestroyCommandPool(m_pDevice->GetVkDevice(), m_CommandPool, nullptr);
	}

	void CommandPool::CreateCommandPool() {
		auto physicalDevice = m_pDevice->GetVkPhysicalDevice();
		auto queueFamilyIndices = m_pDevice->FindQueueFamilies(physicalDevice);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = queueFamilyIndices.m_GraphicsFamily.value();

		if (vkCreateCommandPool(m_pDevice->GetVkDevice(), &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create command pool!");
		}
	}
};
