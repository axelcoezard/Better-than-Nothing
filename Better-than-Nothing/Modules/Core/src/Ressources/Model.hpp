#pragma once

namespace BetterThanNothing
{
	struct Model
	{
		std::string			filePath;

		VkBuffer			vertexBuffer;
		VkDeviceMemory		vertexBufferMemory;
		VkBuffer			indexBuffer;
		VkDeviceMemory		indexBufferMemory;

		u32					indexCount;
	};
};
