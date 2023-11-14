#include "Renderer/Device.hpp"
#include "Renderer/SwapChain.hpp"
#include "Renderer/Vertex.hpp"

#include "Ressources/RessourcePool.hpp"

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#endif

namespace BetterThanNothing
{
	ModelPool::ModelPool(const std::string& basePath, Device* device, SwapChain* swapChain)
		: RessourcePool(basePath)
	{
		m_Device = device;
		m_SwapChain = swapChain;
	}

	ModelPool::~ModelPool()
	{
		auto device = m_Device->GetVkDevice();

		for (auto& [path, model] : m_Ressources)
		{
			vkDestroyBuffer(device, model->indexBuffer, nullptr);
			vkFreeMemory(device, model->indexBufferMemory, nullptr);

			vkDestroyBuffer(device, model->vertexBuffer, nullptr);
			vkFreeMemory(device, model->vertexBufferMemory, nullptr);

			delete model;
		}
	}

	Model* ModelPool::GetRessource(const std::string& filePath)
	{
		auto it = m_Ressources.find(filePath);
		if (it != m_Ressources.end())
			return it->second;

		Model* model = new Model();

		auto [vertices, indices] = LoadModelData(m_BasePath + filePath);
		auto [vertexBuffer, vertexBufferMemory] = CreateVertexBuffer(vertices);
		auto [indexBuffer, indexBufferMemory] = CreateIndexBuffer(indices);

		model->filePath = filePath;
		model->vertexBuffer = vertexBuffer;
		model->vertexBufferMemory = vertexBufferMemory;
		model->indexBuffer = indexBuffer;
		model->indexBufferMemory = indexBufferMemory;
		model->indexCount = static_cast<u32>(indices.size());

		LOG_SUCCESS("ModelPool: " + filePath);

		m_Ressources[filePath] = model;
		return model;
	}

	ModelData ModelPool::LoadModelData(const std::string& filePath)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str())) {
			throw std::runtime_error(warn + err);
		}

		std::unordered_map<Vertex, u32> uniqueVertices{};
		std::vector<Vertex> vertices;
		std::vector<u32> indices;

		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex{};

				vertex.m_Position = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				vertex.m_TextureCoordinates = {
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
				};

				vertex.m_Color = {1.0f, 1.0f, 1.0f};

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<u32>(vertices.size());
					vertices.push_back(vertex);
				}

				indices.push_back(uniqueVertices[vertex]);
			}
		}
		return {vertices, indices};
	}

	BufferData ModelPool::CreateVertexBuffer(std::vector<Vertex>& vertices)
	{
		VkDevice device = m_Device->GetVkDevice();
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		m_SwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory);

		void* data;
		vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), (size_t) bufferSize);
		vkUnmapMemory(device, stagingBufferMemory);

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;

		m_SwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			vertexBuffer,
			vertexBufferMemory);

		m_SwapChain->CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);

		return {vertexBuffer, vertexBufferMemory};
	}

	BufferData ModelPool::CreateIndexBuffer(std::vector<u32>& indices)
	{
		VkDevice device = m_Device->GetVkDevice();
		VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		m_SwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory);

		void* data;
		vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), (size_t) bufferSize);
		vkUnmapMemory(device, stagingBufferMemory);

		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;

		m_SwapChain->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			indexBuffer,
			indexBufferMemory);

		m_SwapChain->CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

		vkDestroyBuffer(device, stagingBuffer, nullptr);
		vkFreeMemory(device, stagingBufferMemory, nullptr);

		return {indexBuffer, indexBufferMemory};
	}
};
