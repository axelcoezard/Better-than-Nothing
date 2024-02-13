#pragma once

#include "Resources/ResourcePool.hpp"
#include "Resources/Model.hpp"

namespace BetterThanNothing
{
	class Device;
	class Vertex;
	class Buffer;

	typedef std::pair<std::vector<Vertex>, std::vector<u32>>	ModelData;

	class ModelPool: public ResourcePool<Model>
	{
	private:
		Device*			m_Device;

	public:
						ModelPool(const std::string& basePath, Device* device);
						~ModelPool();

		Model*			GetResource(const std::string& filePath) override;

	private:

		ModelData		LoadModelData(const std::string& filePath);
		Buffer			CreateVertexBuffer(std::vector<Vertex>& vertices);
		Buffer			CreateIndexBuffer(std::vector<u32>& indices);
	};
};
