#include "Renderer/CommandPool.hpp"

namespace BetterThanNothing
{
	CommandPool::CommandPool(Device* device): m_Device(device) {
		VkPhysicalDevice physicalDevice = m_Device->GetVkPhysicalDevice();
		QueueFamilyIndices queueFamilyIndices = m_Device->FindQueueFamilies(physicalDevice);

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		if (vkCreateCommandPool(m_Device->GetVkDevice(), &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS) {
			throw std::runtime_error("failed to create command pool!");
		}
	}

	CommandPool::~CommandPool() {
		vkDestroyCommandPool(m_Device->GetVkDevice(), m_CommandPool, nullptr);
	}
};
